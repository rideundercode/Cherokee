#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request_parsing.h"

/**
 * get_accept_encoding :
 *     Given a 2D table containing the fields of an HTTP 1.1 
 *     message, this function extracts and returns the 
 *     Accept-encoding field's value
*/

char* get_accept_encoding(char** headers) {
  char* accept_encoding = NULL;

  for (int i = 0; headers[i] != NULL; i++) {
    if (strncmp(headers[i], "Accept-Encoding: ", 17) == 0) {
      accept_encoding = headers[i] + 17;
      break;
    }
  }

  return accept_encoding;
}

static int main() {
  char* fields[5] = {
    "Accept-Encoding:     gzip ",
    "Accept-Language: en-US,en;q=0.9",
    "Cache-Control: no-cache",
    "Connection: keep-alive",
    "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.82 Safari/537.36"
  };

  char* accept_encoding = get_accept_encoding(fields);
  if (accept_encoding == NULL) {
    printf("No Accept-Encoding field found.\n");
  } else {
    printf("Accept-Encoding: %s\n", accept_encoding);
  }

  return 0;
}