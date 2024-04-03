#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include<sys/select.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include<fcntl.h>
// #include "./src/request_parsing/request_parser.h"
#include "./src/request_utils/request_utils.h"
#include "./src/request_parsing_/request_parsing.h"

#define SERVER_PORT 9001
#define LISTEN_BACKLOG 5
#define MAX_NAME_SZE 20
#define NO_OF_CLIENTS 1000
#define MAX_BUFFER_SIZE 1024
#define CONNECT_CLIENT_TO_CHAT "Please connect to the client to chat"
#define CONNECTED "Connected ....."

static int listen_fd = 0;

//Data structure
struct client {
    char cname[MAX_NAME_SZE];
    char chatwith[MAX_NAME_SZE];
    int chatwith_fd;
    int file_des;
    int port;
    char ip[INET_ADDRSTRLEN];
};
struct server_data {
    int total_client;
    struct client client_list[NO_OF_CLIENTS];
};

struct server_data server;


char *directory_listing(int client_socket, char *msg);
int server_new_client_handle(int listen_fd, int *new_socket_fd);
void handle_request(int client_socket, char *msg, char *method);
int server_create_socket(int *listen_fd);
int process_recv_data(int client_socket,char*recv_msg);
int server_build_fdsets(int listenfd, fd_set *readfds, fd_set *writefds, fd_set *exceptfds);
int server_recv_from_client(int socket_client, char *recv_msg);
void server_delete_client(int socket_fd_del);
void cleanup(int sig);

int main(void) {
  signal(SIGINT, cleanup);
    int new_socket = 0;
    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;
    int max_fd= 0;

    memset(&server,0,sizeof(struct server_data));
    printf("Server Started !!!\n");

    if(server_create_socket(&listen_fd) != 0) {
        perror("ERROR : creation socket failed");
        exit(0);
    }
    max_fd = listen_fd;

  int client_socket;

  while (1 == 1) {
    max_fd = server_build_fdsets(listen_fd, &readfds, &writefds, &exceptfds);
    server_select(max_fd,listen_fd, &readfds, &writefds);

    
  }
  return 0;
}

int server_build_fdsets(int listenfd, fd_set *readfds, fd_set *writefds, fd_set *exceptfds) {
    int max_fd = listenfd;

    FD_ZERO(readfds);
    FD_SET(listenfd, readfds);
    FD_SET(STDIN_FILENO,readfds);
    fcntl(STDIN_FILENO,F_SETFL,O_NONBLOCK);

    for(int i = 0; i<server.total_client; i++) {
        FD_SET(server.client_list[i].file_des,readfds);
        max_fd++;
    }
    return max_fd;
}

//create the server socket
int server_create_socket(int *listen_fd) {
    struct sockaddr_in server_addr;

    if((*listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("ERROR : socket creation failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT); 
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if( 0!=bind(*listen_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))){
         perror("ERROR : socket bind failed");
         return -1;
    }

    if(0!=listen(*listen_fd, LISTEN_BACKLOG)) {
         perror("ERROR : socket listen failed");
         return -1;
    }
    return 0;

}

//Accept the connection to server
int server_new_client_handle(int listen_fd, int *new_socket_fd) {
        struct sockaddr_in client_addr;
        int len = sizeof(struct sockaddr);
        bzero(&client_addr,sizeof(client_addr));
        if((*new_socket_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len)) < 0) {
            perror("ERROR :accept failed");
            return -1;
        }
        server_add_new_client(client_addr ,*new_socket_fd);

    return 0;
}

//Adding a new client to the server
void server_add_new_client(struct sockaddr_in client_info, int new_socket_fd) {
    char ip[INET_ADDRSTRLEN] = {0};
    char recv_msg[MAX_BUFFER_SIZE] = {0};
//get extra server details
    server_recv_from_client(new_socket_fd,recv_msg);
   
//get the IP and Port client details
    int port = ntohs(client_info.sin_port);
    inet_ntop(AF_INET, &(client_info.sin_addr), ip, INET_ADDRSTRLEN);
    printf("[CLIENT-INFO] : [port = %d , ip = %s]\n",port, ip);
   
    if(server.total_client >=NO_OF_CLIENTS) {
        perror("ERROR : no more space for client to save");
    }
//populate the new client data 
    strncpy(server.client_list[server.total_client].cname ,recv_msg,strlen(recv_msg));
    server.client_list[server.total_client].port = port;
    strcpy(server.client_list[server.total_client].ip, ip);
    server.client_list[server.total_client].file_des=new_socket_fd;
    
    server.total_client++;
    
}

//select based processing 
int server_select(int max_fd,int listen_fd, fd_set *readfds, fd_set *writefds) {
    int new_socket_fd = 0;
    char recv_msgg[MAX_BUFFER_SIZE] ;
    char send_buff[MAX_BUFFER_SIZE] ;
    memset(recv_msgg, 0 ,sizeof(recv_msgg));
    memset(send_buff, 0 ,sizeof(send_buff));

    int action = select(max_fd+1,readfds,writefds,NULL,NULL);

    if(action == -1 || action == 0) {
        perror("ERROR: select");
        exit(0);
    }

    //check the server listenfd
     if(FD_ISSET(listen_fd,readfds)) {
        server_new_client_handle(listen_fd,&new_socket_fd);
        printf("New socket created = %d\n",new_socket_fd);              
    }

    //check the data from stdin and send message to all connected clients
    // if(FD_ISSET(STDIN_FILENO,readfds)) {
    //      if(read(0,send_buff,sizeof(send_buff))>0) {
    //         for(int i = 0;i<server.total_client;i++)
    //             server_send_to_client(server.client_list[i].file_des,send_buff);
    //     }             
    // }

    // handle all the client connexion
    for(int i = 0; i<server.total_client; i++) {    
           if(FD_ISSET(server.client_list[i].file_des,readfds)) {
               server_recv_from_client(server.client_list[i].file_des, recv_msgg); 
    } 
    } 
    return 0;
}

//Receiving socket data from clients
int server_recv_from_client(int client_socket, char *recv_msg) {
    int read_bytes = 0;
    memset(recv_msg,0,strlen(recv_msg));
    
    if((read_bytes = recv(client_socket, recv_msg, MAX_BUFFER_SIZE, 0)) > 0) {
            process_recv_data(client_socket, recv_msg);
    }
    else if(read_bytes == 0) {
           printf("Client Disconnected\n");
           server_delete_client(client_socket);  
    }
    else {
            printf("ERROR: recv failed\n");
        }
    return 0;
}

//Detete the client data on client exit
void server_delete_client(int socket_fd_del) {
    int i = 0;
    int index = 0;

    for(i=0;i<NO_OF_CLIENTS;i++) {
        if(server.client_list[i].file_des == socket_fd_del) {
            for(index = i; index<NO_OF_CLIENTS;index++ ) {
                server.client_list[index] = server.client_list[index+1];
            }
        }
    }

    server.total_client--;
    printf("Socket deleted  = [%d]\n",socket_fd_del);
    close(socket_fd_del);
}


//processing the received data from clients
int process_recv_data(int client_socket,char*recv_msg) {
    char** header = parse_header(recv_msg);
    char* method = parse_method(header[0]);
    char* url = parse_url(header[0]);

    print_strings(header);
    printf("Method : %s\n", method);
    printf("Url : %s\n", url);

    if (strcmp(method, "GET") == 0 && strcmp(url, "/") == 0) {
      directory_listing(client_socket, recv_msg);
    } else {
      handle_request(client_socket, recv_msg, method);
    }
    free(header);
    free(method);
    free(url);
    printf("Request DONE !\n");
    return 0;
}


void cleanup(int sig) {

    close(listen_fd);
    for(int i = 0; i<server.total_client; i++) {
           close(server.client_list[i].file_des);
    }
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}





void handle_request(int client_socket, char *msg, char *method) {
  if (strcmp(method, "GET") == 0) {
    printf("Inside GET !\n");
    char url[MAX_URL_LEN] = "./src/directory";
    char** header = parse_header(msg);
    char* found_url = parse_url(header[0]);
    strcat(url, found_url);
    printf("URL : %s\n", url);
    char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
    response = build_http_get_response(url, msg);
    printf("REPONSE : %s\n", response);
    send(client_socket, response, strlen(response), 0);
    free(header);
    free(found_url);
    free(response);
  } else if (strcmp(method, "HEAD") == 0) {
    printf("Inside HEAD !\n");
    char url[MAX_URL_LEN] = "./src/directory";
    char** header = parse_header(msg);
    char* found_url = parse_url(header[0]);
    strcat(url, found_url);
    printf("URL : %s\n", url);
    char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
    response = build_http_head_response(url, msg);
    printf("REPONSE : %s\n", response);
    send(client_socket, response, strlen(response), 0);
    free(header);
    free(found_url);
    free(response);
  } else if (strcmp(method, "POST") == 0) {
    printf("Inside POST !\n");
    char url[MAX_URL_LEN] = "./src/directory";
    char** header = parse_header(msg);
    char* found_url = parse_url(header[0]);
    strcat(url, found_url);
    printf("URL : %s\n", url);
    char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
    response = build_http_post_response(url, msg);
    printf("REPONSE : %s\n", response);
    if (response) {
      send(client_socket, response, strlen(response), 0);
    } else {
      printf("EMPTY RESPONSE\n");
    }
    free(header);
    free(found_url);
    free(response);
  } else if (strcmp(method, "PUT") == 0) {
    printf("Inside PUT !\n");
    char url[MAX_URL_LEN] = "./src/directory";
    char** header = parse_header(msg);
    char* found_url = parse_url(header[0]);
    strcat(url, found_url);
    printf("URL : %s\n", url);
    char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
    response = build_http_put_response(url, msg);
    printf("REPONSE : %s\n", response);
    if (response) {
      send(client_socket, response, strlen(response), 0);
    } else {
      printf("EMPTY RESPONSE\n");
    }
    free(header);
    free(found_url);
    free(response);
  } else if (strcmp(method, "DELETE") == 0) {
    printf("Inside DELETE !\n");
    char url[MAX_URL_LEN] = "./src/directory";
    char** header = parse_header(msg);
    char* found_url = parse_url(header[0]);
    strcat(url, found_url);
    printf("URL : %s\n", url);
    char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
    response = build_http_delete_response(url, msg);
    printf("REPONSE : %s\n", response);
    if (response) {
      send(client_socket, response, strlen(response), 0);
    } else {
      printf("EMPTY RESPONSE\n");
    }
    free(header);
    free(found_url);
    free(response);
  } else {
    printf("Inside NOTHING !\n");
  }
}

char *directory_listing(int client_socket, char *msg) {
  char* response_body = (char*) malloc(MAX_BODY_LENGTH * sizeof(char));
  strcpy(response_body, "<!DOCTYPE html>\n");
  strcat(response_body, "<html><head><title>MP2</title>\n");
  strcat(response_body, "<style> body {background-color: #FCBA03} </style></head>\n");
  strcat(response_body, "<body><ul>");


  DIR *d;
  struct dirent *dir;
  d = opendir("src/directory");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      char link[50] = "<li><a href=\"/\">";
      char *linkFinish = "</a></li>";
      strcat(link, dir->d_name);
      strcat(link, linkFinish);
      strcat(response_body, link);
    }
    closedir(d);
  }
  strcat(response_body, "</ul></body></html>\n");

  int body_length = strlen(response_body) - 1;
  char body_length_char[MAX_BODY_LENGTH];
  sprintf(body_length_char, "%d", body_length);

  char* response_ = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
  strcpy(response_, "HTTP/1.1 200 OK\n");
  char* content_length = (char*) malloc(MAX_HEADER_LENGTH * sizeof(char));
  strcpy(content_length, "Content-Length: ");
  strcat(content_length, body_length_char);
  strcat(content_length, "\n");
  strcat(response_, content_length);
  strcat(response_, "Content-Type: text/html\n");
  strcat(response_, "Connection: close\n\n");
  strcat(response_, response_body);

  printf("\n\nMessage : %s\n", response_);
  send(client_socket, response_, strlen(response_), 0);
  /*if (send_status == -1) {
      printf("Cannot send message\n");
      return -1;
  }*/
  free(response_);
  return response_;
}