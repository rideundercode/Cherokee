#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "request_utils.h"
#include "../request_parsing_/request_parsing.h"

char* build_http_post_response(char* url, char* msg) {
  if (!url) {
    return build_400_response();
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
        return build_400_response();
      }
    }
  } else {
    printf("BODY : %s\n", body);
    printf("STRLEN : %d\n", (int) strlen(body));
    printf("CONTENT_LENGTH : %d\n", (int) strtol(content_length, (char **)NULL, 10));
    if ((int) strlen(body) != (int) strtol(content_length, (char **)NULL, 10)) {
      return build_400_response();
    }
  }


  char* content_type_field = parse_content_type_field(header);
  if (content_type_field == NULL) {
    return build_400_response("No Content-Type was passed...");
  }
  char* file_type = get_content_type(content_type_field);

  if (strcmp(file_type, "UNKNOWN") == 0) {
    return build_400_response("Unhandled type");
  }

  printf("TYPE OF THE SENT FILE: %s\n", file_type);

  int creation_status = create_file(url, file_type);

  if (creation_status == 0 || creation_status == -1) {
    return build_500_response();
  }

  if (body != NULL) {
    char* file_name = (char*) malloc( MAX_FIELD_LENGTH * sizeof(char));
    strcpy(file_name, url);
    strcat(file_name, map_file_type_file_extension(file_type));
    int write_status = write_in_file(file_name, body);
    if (write_status == -1 || write_status == 0) {
      return build_500_response();
    }
  }

  return build_200_response("File created !");
}

static int main() {
  char message[MAX_RESPONSE_LENGTH] = "GET /test.html HTTP/1.1\r\n"
    "Host: www.example.com\r\n"
    "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:61.0) Gecko/20100101 Firefox/61.0\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: en-US,en;q=0.5\r\n"
    "Accept-Encoding: gzip, deflate\r\n"
    "Connection: keep-alive\r\n\r\n";

  // char message[] = "GET /test.html HTTP/1.1Host: www.example.comUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:61.0) Gecko/20100101 Firefox/61.0Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8Accept-Language: en-US,en;q=0.5Accept-Encoding: gzip, deflateConnection: keep-alive";

  char url[MAX_URL_LEN] = "../directory";
  char** header = parse_header(message);
  printf("MESSAGE : %s\n", message);
  print_strings(header);
  char* found_url = parse_url(header[0]);
  strcat(url, found_url);
  char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
  response = build_http_post_response(url, message);

  printf("Response: \n%s\n", response);

  return 0;
}
