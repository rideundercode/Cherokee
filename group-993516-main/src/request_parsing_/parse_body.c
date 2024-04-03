#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parse_body(char* http_message) {
  char* body_start = strstr(http_message, "\r\n\r\n");
  if (body_start == NULL) {
    return NULL;
  }
  body_start += 4;
  int body_length = strlen(body_start);
  if (body_length == 0) {
    return NULL;
  }
  char* body = (char*) malloc((body_length + 1) * sizeof(char));
  strcpy(body, body_start);
  return body;
}