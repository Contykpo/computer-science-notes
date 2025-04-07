#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

__pid_t child_PID;

void child_urg_handler()
{

}

void child_process()
{
	signal(SIGURG, child_urg_handler);
}

void parent_int_handler(int sig)
{
	sigset_t sigset_block;
	sigset_t old;

	sigemptyset(&sigset_block);
	sigemptyset(&sigset_block);
	
	sigaddset(&sigset_block, SIGCHLD);
	
	sigprocmask(SIG_BLOCK, &sigset_block, &old);
	
	signal(SIGCHLD, NULL);
	
	sigprocmask(SIG_SETMASK, &old, NULL);
}

void parent_process()
{
	signal(SIGINT, parent_int_handler);
}

int main(int argc, char* argv[]) {
  	
	child_PID = fork();

	if(child_PID == 0)
	{
		child_process();
	}
	else
	{
		parent_process();
	}

	return EXIT_SUCCESS;
}
