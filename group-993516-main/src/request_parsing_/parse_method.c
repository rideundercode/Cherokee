#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse_method :
 *     Given the first line of an HTTP 1.1 message's header , this
 *     function extracts and returns the header's fields in a 2D 
 *     table
*/
char* parse_method(char* first_line) {
  char* method = (char*) malloc(10 * sizeof(char));
  sscanf(first_line, "%s", method);
  return method;
}

static int main() {
  char first_line[] = "DELETE /index.html HTTP/1.1";
  char* method = parse_method(first_line);
  printf("Method: %s\n", method);
  return 0;
}
