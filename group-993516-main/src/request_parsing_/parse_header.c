#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request_parsing.h"
#include "../request_utils/request_utils.h"

/**
 * parse_header :
 *     Given an HTTP 1.1 message, this function extracts and 
 *     returns the header's fields in a 2D table
*/

char** parse_header(char* message) {
  char* temp_message = (char*) malloc (MAX_RESPONSE_LENGTH * sizeof(char*));
  strcpy(temp_message, message);
  char** fields = (char**) malloc((MAX_FIELDS + 1) * sizeof(char*));
  for (int i = 0; i < MAX_FIELDS; i++) {
    fields[i] = (char*) malloc(MAX_FIELD_LENGTH * sizeof(char));
  }

  int field_count = 0;
  char* field = strtok(temp_message, "\r\n");
  while (field != NULL && field_count < MAX_FIELDS) {
    strcpy(fields[field_count++], field);
    field = strtok(NULL, "\r\n");
  }

  free(temp_message);
  fields[field_count] = NULL;
  return fields;
}

static int main() {
  // char message[] = "GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nUser-Agent: MyClient\r\nAccept-Encoding: gzip\r\n\n";
  char message[] = "GET /test.html HTTP/1.1\nHost: www.example.com\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:61.0) Gecko/20100101 Firefox/61.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate\nConnection: keep-alive\n\n";

  // char message[] = "GET /test.html HTTP/1.1\n"
  //   "Host: www.example.com\n"
  //   "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:61.0) Gecko/20100101 Firefox/61.0\n"
  //   "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\n"
  //   "Accept-Language: en-US,en;q=0.5\n"
  //   "Accept-Encoding: gzip, deflate\n"
  //   "Connection: keep-alive\n\n";

  char** fields = parse_header(message);
  printf("MESSAGE : \n");
  printf("%s\n", message);

  int i = 0;
  while (fields[i] != NULL) {
    if (strlen(fields[i]) == 0) break;
    printf("Field %d : %s\n", i,  fields[i]);
    i++;
  }

  return 0;
}
