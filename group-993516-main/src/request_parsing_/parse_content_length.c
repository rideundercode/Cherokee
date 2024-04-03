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

char* parse_content_length_field(char** headers) {
  char* accept = NULL;

  for (int i = 0; headers[i] != NULL; i++) {
    if (strncmp(headers[i], "Content-Length: ", 16) == 0) {
      accept = headers[i] + 16;
      break;
    } else if (strncmp(headers[i], "Content-Length:", 15) == 0) {
      accept = headers[i] + 15;
      break;
    }
  }

  return accept;
}
