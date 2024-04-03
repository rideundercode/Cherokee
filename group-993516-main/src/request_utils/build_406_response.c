#include "request_utils.h"

char* build_406_response() {
  char* response = (char*) malloc(MAX_HEADER_LENGTH * sizeof(char));
  strcpy(response, "HTTP/1.1 406 Not Acceptable\r\n");
  strcat(response, "Content-Type: text/plain\r\n");
  strcat(response, "Content-Length: 20\r\n");
  strcat(response, "\r\n");
  strcat(response, "406 Not Acceptable\r\n");
  return response;
}