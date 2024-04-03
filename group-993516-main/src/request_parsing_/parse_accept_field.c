#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request_parsing.h"

/**
 * parse_accept_field :
 *     Given a 2D table containing the fields of an HTTP 1.1 
 *     message, this function extracts and returns the 
 *     Accept field's value
*/

char* parse_accept_field(char** headers) {
  char* accept = NULL;

  for (int i = 0; headers[i] != NULL; i++) {
    printf("FIELD %d : %s\n", i, headers[i]);
    if (strncmp(headers[i], "Accept: ", 8) == 0) {
      accept = headers[i] + 8;
      break;
    } else if (strncmp(headers[i], "Accept:", 7) == 0) {
      accept = headers[i] + 7;
      break;
    }
  }

  return accept;
}

static int main() {
  char* headers[4] = {
    "Host: www.example.com",
    "Accept: text/html",
    "Connection: keep-alive",
    NULL
  };
  char* accept = parse_accept_field(headers);
  if (accept != NULL) {
    printf("Accept: %s|||\n", accept);
  } else {
    printf("Accept field not specified.\n");
  }
  return 0;
}
