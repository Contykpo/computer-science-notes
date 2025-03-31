#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include<time.h>
#include <sys/wait.h>

int process_count;
int round_count;
int cursed_number;
int current_id = 0;

__pid_t children_PIDs[10];
__pid_t terminated_children_PIDs[10];

void validate_argc(int argc)
{
    // First argument is the name of the binary (program).
    if(argc != 4)
    {
        printf("%d\n",argc);
        
	errno = EXIT_FAILURE;
        perror("Debe haber 3 argumentos unicamente.");

        exit(EXIT_FAILURE);
    }
}

void validate_and_parse_argv(char** argv)
{
    process_count    = atoi(argv[1]);
    round_count      = atoi(argv[2]);
    cursed_number    = atoi(argv[3]);

    if(process_count <= 0 || round_count <= 0 || cursed_number < 0 || cursed_number >= process_count)
    {
        errno = EXIT_FAILURE;
        perror("Entrada invalida, todos los argumentos deben ser no negativos y el numero maldito debe ser menor al numero de procesos.");

        exit(EXIT_FAILURE);
    }
}

void run_round()
{
    for(int i = 0; i < process_count; ++i)
    {
        kill(children_PIDs[i], SIGTERM);

        sleep(1);
    }
}

int get_random_number()
{
    int result = rand() % process_count; 
    
    return result;
}

void term_handler_child(int sig)
{
    if(get_random_number() == cursed_number)
    {
        printf("Puta carajo\n");

        kill(getppid(), SIGTERM);

        exit(0);
    }
}

void run_process()
{
    srand(getpid());

    signal(SIGTERM, term_handler_child);

    while(1)
    {
	pause();
    }
}

void create_child_processes()
{
    for(; current_id < process_count; ++current_id)
    {
        __pid_t new_child_PID = fork();

        if(new_child_PID == 0)
        {
            run_process();

            perror("Proceso hijo termino prematuramente");
            exit(EXIT_FAILURE);
        }
        else
        {
            children_PIDs[current_id] = new_child_PID;
        }
    }
}

void term_handler_parent(int sig)
{
    __pid_t terminated_child_PID = wait(NULL);

    for(int i = 0; i < process_count; ++i)
    {
        if(children_PIDs[i] == terminated_child_PID)
        {
            terminated_children_PIDs[i] = terminated_child_PID;
        }
    }
}

int main(int argc, char** argv)
{
    validate_argc(argc);
    validate_and_parse_argv(argv);

    signal(SIGTERM, term_handler_parent);

    create_child_processes();

    for(; round_count > 0; round_count--)
    {
	run_round(); 
    }

    for(int i = 0; i < process_count; ++i)
    {
        if(terminated_children_PIDs[i] == children_PIDs[i]) { continue; }

        if(kill(children_PIDs[i], SIGKILL) == 0)
        {
            wait(NULL);

            printf("Sobreviviente: Id: %d, PID: %d\n", i, children_PIDs[i]);
        }
    }
}
