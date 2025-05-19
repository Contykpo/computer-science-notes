#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <stdio.h>
#include <arpa/inet.h>

#define WRITE 1
#define READ 0
#define MAX_CONEXIONES 5

typedef struct {
    __pid_t pid;
    int socket;
} Conexion;

typedef struct{
    char mensaje[512];
    __pid_t pid_handler;
} MensajeDifundido;

Conexion conexiones[MAX_CONEXIONES] = {{.pid=0, .socket=0}};
int pipe_difusion[2];

void handler_conexion(Conexion conexion){

    char mensaje[512];

    while(1){
        //Si leemos 0 bytes u ocurre algun error terminamos la conexion con el cliente
        if(recv(conexion.socket, &mensaje, sizeof(mensaje), 0) <= 0){
            exit(0);
        }

        MensajeDifundido mensaje_dif = {.pid_handler = getpid()};

        strcpy(mensaje_dif.mensaje, mensaje);

        write(pipe_difusion[WRITE], &mensaje_dif, sizeof(mensaje_dif));

        kill(getppid(), SIGUSR1);

        printf("Mensaje recibido: %s\n", mensaje_dif.mensaje);
    }
    
}

void aceptar_conexion(int socket){
    Conexion new_conn = {.socket = socket};

    new_conn.pid = fork();

    if(new_conn.pid == 0){
        handler_conexion(new_conn);
        exit(0);
    }

    for(int i = 0; i < MAX_CONEXIONES; ++i){
        if(conexiones[i].pid <= 0){
            conexiones[i] = new_conn;
            break;
        }
    }
}

void eliminar_conexion(__pid_t handler_pid){

    for(int i = 0; i < MAX_CONEXIONES; ++i){
        if(conexiones[i].pid == handler_pid){
            close(conexiones[i].socket);
            conexiones[i].pid = 0;
        }
    }
}

void sigchld_handler(int sig){
    
    __pid_t terminated_handler = wait(NULL);

    eliminar_conexion(terminated_handler);

    printf("Conexion con cliente finalizada\n");
}

void sigusr_handler(int sig){

    MensajeDifundido mensaje_recibido;

    read(pipe_difusion[READ], &mensaje_recibido, sizeof(mensaje_recibido));

    printf("Difundiendo mensaje: %s\n", mensaje_recibido.mensaje);

    for(int i = 0; i < MAX_CONEXIONES; ++i){
        if(conexiones[i].pid > 0 && mensaje_recibido.pid_handler != conexiones[i].pid){       
            printf("%d\n", conexiones[i].pid);   
            send(conexiones[i].socket, &mensaje_recibido.mensaje, sizeof(mensaje_recibido.mensaje), 0);
        }
    }
}

int main(int argc, char* argv[]){

    int cant_conexiones = 0;

    int sockfd;
    fd_set read_fds;
    struct sockaddr_in server_addr;

    // Crear el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error al crear el socket");
        exit(1);
    }

    // Configurar la dirección del servidor
    server_addr.sin_family = AF_INET;
    // Puerto donde escuchar
    server_addr.sin_port = htons(8082);
    // Escuchar en todas las interfaces (también podrías usar inet_addr("127.0.0.1") para solo escuchar en localhost)
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Enlazar el socket a la dirección
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al hacer bind");
        close(sockfd);
        exit(1);
    }

    // Escuchar por conexiones entrantes
    if (listen(sockfd, MAX_CONEXIONES) < 0) {
        perror("Error al escuchar");
        close(sockfd);
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    if(pipe(pipe_difusion) < 0){
        perror("Error al crear pipe de difusion");
        exit(-1);
    }

    signal(SIGCHLD, sigchld_handler);

    signal(SIGUSR1, sigusr_handler);
    
    printf("Escuchando en el 127.0.0.1:%d ...\n", server_addr.sin_port);

    struct timeval timeout;

    while(1){
        if(cant_conexiones == MAX_CONEXIONES){
            pause();
            continue;
        }

        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);

        timeout.tv_sec = 5;  // Timeout de 5 segundos
        timeout.tv_usec = 0;

        int activity = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);

        if (FD_ISSET(sockfd, &read_fds)) {
            int new_conn = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
            if (new_conn < 0) {
                perror("Error al aceptar la conexión");
                close(sockfd);
                continue;
            }

            aceptar_conexion(new_conn);

            cant_conexiones++;
        }
    }
}