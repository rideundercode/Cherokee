#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1) {
        printf("Cannot create a socket\n");
        return -1;
    }
    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(9000);
    sockAddr.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(client_socket,
        (struct sockaddr*) &sockAddr,
        sizeof(sockAddr));
    if(connection_status == -1) {
        printf("Cannot connect\n");
        return -1;
    }

    char msg[256];
    int receive_status = recv(client_socket, &msg, sizeof(msg), 0);

    if(receive_status == -1) {
        printf("Cannot receive\n");
        return -1;
    }
    printf("The message is : %s\n", msg);

    close(client_socket);
    return 0;
}