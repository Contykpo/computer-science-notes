#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"


static int run(char ***progs, size_t count)
{	
	int r;
	int status;

	//Reservo memoria para el arreglo de pids
	pid_t *children = malloc(sizeof(*children) * count);

	// [read_fd, write_fd].
	int (*pipes)[2] = malloc(sizeof(*pipes) * (count -1));

	// Creamos los pipes necesarios.
	for (int i = 0; i < count - 1; i++)
	{
		if (pipe(pipes[i]) < 0)
		{
			perror("pipe");
			return -1;
		}
	}

	for (int i = 0; i < count; i++)
	{
		children[i] = fork();
	
		if (children[i] < 0)
		{
			perror("fork");
			return -1;
		}

		if (children[i] == 0)
		{
			// Se redirecciona la entrada excepto por el primer proceso.
			if (i > 0)
			{
				close(pipes[i-1][PIPE_WRITE]);
				
				if (dup2(pipes[i - 1][PIPE_READ], STD_INPUT) < 0)
				{
					perror("dup2 read");
					exit(EXIT_FAILURE);
				}
			}

			// Se redirecciona la salida excepto por el ultimo proceso.
			if (i < count - 1)
			{
				if (dup2(pipes[i][PIPE_WRITE], STD_OUTPUT) < 0)
				{
					perror("dup2 write");
					exit(EXIT_FAILURE);
				}
			}

			// Se cierran todos los pipes en el hijo.
			for (int j = 0; j < count - 1; j++)
			{
				close(pipes[j][PIPE_READ]);
				close(pipes[j][PIPE_WRITE]);
			}

			// Se ejecuta el comando.

			printf("%s, %S", progs[i][0], progs[i]); 

			execvp(progs[i][0], progs[i]);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}

	// Se cirran todos los pipes en el padre.
	for (int i = 0; i < count - 1; i++)
	{
		close(pipes[i][PIPE_READ]);
		close(pipes[i][PIPE_WRITE]);
	}
		
	// Se espera a los hijos y verifica el estado en que terminaron.
	for (int i = 0; i < count; i++)
	{
		waitpid(children[i], &status, 0);

		if (!WIFEXITED(status))
		{
			fprintf(stderr, "proceso %d no terminó correctamente [%d]: ", (int)children[i], WIFSIGNALED(status));
			perror("");
	
			return -1;
		}
	}
	
	r = 0;
	free(children);
	free(pipes);

	return r;
}


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("El programa recibe como parametro de entrada un string con la linea de comandos a ejecutar. \n"); 
		printf("Por ejemplo ./mini-shell 'ls -a | grep anillo'\n");
	
		return 0;
	}
	
	int programs_count;
	char*** programs_with_parameters = parse_input(argv, &programs_count);

	if (programs_count < 1) { return 0; }

	printf("status: %d\n", run(programs_with_parameters, programs_count));

	fflush(stdout);
	fflush(stderr);

	return 0;
}
