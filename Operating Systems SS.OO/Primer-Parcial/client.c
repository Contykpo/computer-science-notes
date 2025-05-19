#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <string.h>

void handler_recibir_mensajes(int socket){

    char mensaje[512];

    while(recv(socket, &mensaje, sizeof(mensaje), 0) > 0){
        printf("\nMensaje recibido del servidor: %s\n", mensaje);
    }

    printf("Cerrando receptor");

    exit(0);
}

int main(int argc, char* argv[]){

    int sockfd;
    struct sockaddr_in server_addr;

    // Crear el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error al crear el socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8082);  
    server_addr.sin_addr.s_addr = INADDR_ANY;  

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al conectar al servidor");
        close(sockfd);
        exit(1);
    }

    __pid_t handler_recibir_mensajes_pid = fork();

    if(handler_recibir_mensajes_pid == 0)
        handler_recibir_mensajes(sockfd);
    
    printf("Conectado al servidor\n");

    char mensaje[512];

    while(1){

        printf("Ingrese un mensaje para enviar: ");
        scanf("%s", mensaje);
        printf("\n");
        
        if(send(sockfd, &mensaje, sizeof(mensaje), 0) <= 0){
            perror("Error al enviar mensaje al servidor");
            break;
        }
    }

    close(sockfd);

    kill(handler_recibir_mensajes_pid, SIGKILL);

    wait(NULL);

    exit(0);
}