#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "request_utils.h"
#include "../request_parsing_/request_parsing.h"

char* build_http_put_response(char* url, char* msg) {
  if (!url) {
    return build_400_response();
  }
  if (!check_file_exists(url)) {
    return build_404_response();
  }
  char* body = parse_body(msg);
  char** header = parse_header(msg);
  if (header == NULL) {
    return build_400_response();
  }
  char* content_length = parse_content_length_field(header);
  if (body == NULL) {
    printf("EMPTY BODY\n");
    printf("CONTENT_LENGTH : %s\n", content_length);
    if (content_length) {
      if ((int) strtol(content_length, (char **)NULL, 10) != 0) {
        return build_400_response("Body passed had different size than Content-Length specified...");
      }
    }
  } else {
    printf("BODY : %s\n", body);
    printf("STRLEN : %d\n", (int) strlen(body));
    printf("CONTENT_LENGTH : %d\n", (int) strtol(content_length, (char **)NULL, 10));
    if ((int) strlen(body) != (int) strtol(content_length, (char **)NULL, 10)) {
      return build_400_response("Body passed had different size than Content-Length specified...");
    }
  }

  char* content_type_field = parse_content_type_field(header);
  if (content_type_field == NULL) {
    return build_400_response("No Content-Type has been passed...");
  }
  char* file_type = get_content_type(content_type_field);

  if (strcmp(file_type, "UNKNOWN") == 0) {
    return build_400_response("The Content-Type is not handled for now...\r\nOnly texte, html, json, png and jpeg files are handled for now.");
  }

  printf("TYPE OF THE SENT FILE: %s\n", file_type);

  if (body != NULL) {
    char* file_name = (char*) malloc( MAX_FIELD_LENGTH * sizeof(char));
    strcpy(file_name, url);
    strcat(file_name, map_file_type_file_extension(file_type));
    int write_status = write_in_file(file_name, body);
    if (write_status == 0) {
      return build_400_response("The file to update does not exist...");
    } else if (write_status == -1) {
      return build_500_response();
    }
  }

  return build_200_response("File updated !");
}
