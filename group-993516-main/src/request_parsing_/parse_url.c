#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse_url :
 *     Given an HTTP 1.1 message first line, this function 
 *     extracts and returns the url
*/

char* parse_url(char* first_line) {
  char* method = (char*) malloc(10 * sizeof(char));
  char* url = (char*) malloc(100 * sizeof(char));
  sscanf(first_line, "%s %s", method, url);
  free(method);
  return url;
}

static int main() {
  char first_line[] = "DELETE /coucou/yes?oui=3 HTTP/1.1";
  char* url = parse_url(first_line);
  printf("URL: %s\n", url);
  return 0;
}
