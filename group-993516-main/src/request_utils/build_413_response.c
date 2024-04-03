#include "request_utils.h"

char *build_413_response() {
  char* response = (char*) malloc(MAX_HEADER_LENGTH * sizeof(char));
  strcpy(response, "HTTP/1.1 413 Payload Too Large\r\n");
  strcat(response, "Content-Type: text/plain\r\n");
  strcat(response, "Content-Length: 21\r\n");
  strcat(response, "\r\n");
  strcat(response, "413 Payload Too Large\r\n");
  return response;
}