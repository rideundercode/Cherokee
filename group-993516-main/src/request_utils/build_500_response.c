#include <stdio.h>
#include <string.h>
#include "request_utils.h"

char* build_500_response() {
  char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
  sprintf(response, "HTTP/1.1 500 Internal Server Error\r\n");
  strcat(response, "Content-Type: text/plain\r\n");
  strcat(response, "Content-Length: 25\r\n");
  strcat(response, "\r\n");
  strcat(response, "500 Internal Server Error\r\n");
  return response;
}