#include "request_utils.h"

char* build_404_response() {
  char* response = (char*) malloc(MAX_HEADER_LENGTH * sizeof(char));
  strcpy(response, "HTTP/1.1 404 Not Found\r\n");
  strcat(response, "Connection: close\r\n");
  strcat(response, "Content-Type: text/plain\r\n");
  strcat(response, "Content-Length: 15\r\n");
  strcat(response, "\r\n");
  strcat(response, "404 Not Found\r\n");
  return response;
}
