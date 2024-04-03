#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "request_utils.h"
#include "../request_parsing_/request_parsing.h"

char* build_http_delete_response(char* url, char* msg) {
  if (!url) {
    return build_400_response();
  }
  if (!check_file_exists(url)) {
    return build_404_response();
  }
  char** header = parse_header(msg);
  if (header == NULL) {
    return build_400_response();
  }
  char* file_type = check_file_type(url);
  if (strcmp(file_type, "UNKNOWN") == 0) {
    printf("Unknown file type...\n");
    return build_400_response("This type of file is not handled on this server...");
  }

  int delete_status = delete_file(url);

  if (delete_status == 0) {
    return build_400_response("The file to delete does not exist...");
  } else if (delete_status == -1) {
    return build_500_response();
  }

  return build_200_response("File deleted !");
}
