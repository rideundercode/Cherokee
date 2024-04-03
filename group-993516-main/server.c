#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


char *directory_listing(int client_socket) {
    char response[900] = "HTTP/1.1 200 OK\n"
        "Content-length: 300\n"
        "Content-Type: text/html\n"
        "Connection: close\n\n"
        "<!DOCTYPE html>\n"
        "<html><head><title>MP2</title>\n"
        "<style> body {background-color: #FCBA03} </style></head>\n"
        "<body><ul>";
    DIR *d;
    struct dirent *dir;
    d = opendir("src/directory");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            char link[50] = "<li><a href=\"/\">";
            char *linkFinish = "</a></li>";
            strcat(link, dir->d_name);
            strcat(link, linkFinish);
            strcat(response, link);
        }
        closedir(d);
    }
        strcat(response, "</ul></body></html>\n");
    printf("\n\nMessage : %s", response);

   send(client_socket, &response, sizeof(response), 0);
    /*if (send_status == -1) {
        printf("Cannot send message\n");
        return -1;
    }*/
    return response;
}
int main(void) {

    int server_socket  = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        printf("Cannot create socket\n");
        return -1;
    }
    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(9002);
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    int bind_status = bind(server_socket,
        (struct sockaddr*) &sockAddr,
        sizeof(sockAddr));
    if(bind_status == -1) {
        printf("Cannot bind\n");
        return -1;
    } else {
        printf("Could bind\n");
    }
    int listen_status = listen(server_socket, 3);
    if(listen_status == -1) {
        printf("Cannot listen\n");
    } else {
        printf("Can listen\n");
    }

    int client_socket;
        client_socket = accept(server_socket, NULL, NULL);


    char msg[999] = "HTTP/1.1 200 OK\r\n"
                    "Content-length: 178\r\n"
                    "Content-Type: text/html\r\n"
                    "Connection: close\r\n\r\n"
                    "<!DOCTYPE html>\r\n"
                    "<html><head><title>Cherokee</title>\r\n"
                    "<style> body {background-color: #FCBA03} </style></head>\r\n"
                    "<body><center><h1> Architecture : </h1><br>\r\n"
                    "</body></html>\r\n";


    char recv_msg[999];
    int recv_status = recv(client_socket, &recv_msg, sizeof(recv_msg), 0);
    printf("Client message : %s", recv_msg);
   // int send_status = send(client_socket, &msg, sizeof(msg), 0);
    directory_listing(client_socket);


    close(server_socket);

    return 0;
}
