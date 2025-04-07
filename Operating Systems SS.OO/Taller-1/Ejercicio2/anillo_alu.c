#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"

// La idea:
// Se crean n pipes, uno por proceso hijo, ya que cada hijo recibe de su antecesor y escribe a su sucesor.
// Se crean n procesos hijos, conectando correctamente los pipes.
// Cada hijo espera su turno leyendo del pipe de entrada, e incrementa el valor y lo envia al siguiente usando su pipe de salida.
// El hijo start compara el valor recibido con p, si es >= p, rompe el ciclo y envia el resultado final al padre.
// El padre inicia el mensaje escribiendolo al hijo start, y espera la respuesta final a traves de otro pipe.

int generate_random_number(int min)
{
	int r;	
	do
	{
		r = min + 1 + (rand() % 20);
	} while (r <= min);
	
	return r;
}

// Crea n pipes para los procesos hijos.
void create_pipes(int n, int pipes[][2])
{
	for (int i = 0; i < n; i++)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
}

// Cierra todos los extremos de pipes que no se usan dentro del hijo iterado "i".
void close_child_pipes(int n, int i, int pipes[][2], int result_pipe[2])
{
	for (int j = 0; j < n; j++)
	{
		if (j != i)
			close(pipes[j][PIPE_WRITE]);
		if (j != (i + n - 1) % n)
			close(pipes[j][PIPE_READ]);
	}
	// Hijo no lee el resultado.
	close(result_pipe[PIPE_READ]);
}

// Logica del proceso hijo siguiendo el protocolo anillo.
void child_process(int i, int start, int buffer, int read_fd, int write_fd, int result_pipe_write)
{
	int secret = -1;

	if (i == start)
	{
		secret = generate_random_number(buffer);
		printf("[Hijo %d] Numero secreto generado: %d\n", i, secret);
	}

	while (1)
	{
		int value;
		if (read(read_fd, &value, sizeof(int)) <= 0)
		{
			perror("read");
			exit(1);
		}

		if (i == start && value >= secret)
		{
			printf("[Hijo %d] Valor %d >= secreto %d. Fin de ciclo.\n", i, value, secret);
			write(result_pipe_write, &value, sizeof(int));
			break;
		}

		value++;
		write(write_fd, &value, sizeof(int));
	}

	close(read_fd);
	close(write_fd);
	close(result_pipe_write);
	exit(0);
}

// Crea los procesos hijos y define su comportamiento de lectura o escritura en el anillo.
void create_children(int n, int start, int buffer, int pipes[][2], int result_pipe[2])
{
	for (int i = 0; i < n; i++)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}

		if (pid == 0)
		{
			int read_fd = pipes[(i + n - 1) % n][PIPE_READ];
			int write_fd = pipes[i][PIPE_WRITE];
		
			close_child_pipes(n, i, pipes, result_pipe);
			child_process(i, start, buffer, read_fd, write_fd, result_pipe[PIPE_WRITE]);
		}
	}
}

// Cierra todos los pipes que el padre no usara.
void close_parent_pipes(int n, int pipes[][2], int result_pipe[2])
{
	for (int i = 0; i < n; i++)
	{
		close(pipes[i][PIPE_READ]);
		close(pipes[i][PIPE_WRITE]);
	}
	
	close(result_pipe[PIPE_WRITE]);
}

// Envia el mensaje inicial al proceso start.
void start_ring(int start, int buffer, int pipes[][2])
{
	write(pipes[start][PIPE_WRITE], &buffer, sizeof(int));
}

int wait_for_result(int result_pipe_read)
{
	// Resultado final del pipe.
	int result;
	if (read(result_pipe_read, &result, sizeof(int)) <= 0)
	{
		perror("read resultado");
		exit(1);
	}

	return result;
}

int main(int argc, char **argv)
{	
	// Funcion para cargar nueva semilla para el numero aleatorio.
	srand(time(NULL));

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}

	int n = atoi(argv[1]);
	int buffer = atoi(argv[2]);
	int start = atoi(argv[3]);
    
	if (start < 0 || start >= n)
	{
		fprintf(stderr, "Error: el proceso de inicio debe estar entre 0 y n-1\n");
		exit(1);
	}

    printf("Se crearan %i procesos, se enviara el caracter %i desde proceso %i \n", n, buffer, start);
    
	int pipes[n][2];
	int result_pipe[2];

	create_pipes(n, pipes);

	if (pipe(result_pipe) == -1)
	{
		perror("pipe resultado");
		exit(1);
	}

	create_children(n, start, buffer, pipes, result_pipe);

	close_parent_pipes(n, pipes, result_pipe);

	start_ring(start, buffer, pipes);

	int final = esperar_resultado(result_pipe[PIPE_READ]);
	
	printf("[Padre] Valor final recibido: %d\n", final);

	close(result_pipe[PIPE_READ]);

	for (int i = 0; i < n; i++)
		wait(NULL);

	return 0;
}
