#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request_parsing.h"

/**
 * parse_content_type_field :
 *     Given a 2D table containing the fields of an HTTP 1.1 
 *     message, this function extracts and returns the 
 *     Accept field's value
*/

char* parse_content_type_field(char** headers) {
  char* accept = NULL;

  for (int i = 0; headers[i] != NULL; i++) {
    printf("FIELD %d : %s\n", i, headers[i]);
    if (strncmp(headers[i], "Content-Type: ", 14) == 0) {
      accept = headers[i] + 14;
      break;
    } else if (strncmp(headers[i], "Content-Type:", 13) == 0) {
      accept = headers[i] + 13;
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
