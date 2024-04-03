#include <stdio.h>
#include <string.h>
#include "request_utils.h"

char* build_200_response(char* message) {
  if (message == NULL || strlen(message) == 0) {
    char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
    sprintf(response, "HTTP/1.1 200 OK\r\n");
    strcat(response, "Connection: close\r\n");
    strcat(response, "Content-Type: text/plain\r\n");
    strcat(response, "Content-Length: 6\r\n");
    strcat(response, "\r\n");
    strcat(response, "200 OK\r\n");
    return response;
  } else {
    int content_length = 6;
    int message_length = (int) strlen(message);
    content_length += message_length;
    content_length += 2;
    char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
    sprintf(response, "HTTP/1.1 200 OK\r\n");
    strcat(response, "Connection: close\r\n");
    strcat(response, "Content-Type: text/plain\r\n");
    strcat(response, "Content-Length: ");
    char* content_length_string = (char*) malloc(MAX_FIELD_LENGTH * sizeof(char));
    sprintf(content_length_string, "%d", content_length);
    strcat(response, content_length_string);
    strcat(response, "\r\n\r\n");
    strcat(response, "200 OK\r\n");
    strcat(response, message);
    strcat(response, "\r\n");
    return response;
  }
}