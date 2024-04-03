#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "request_utils.h"
#include "../request_parsing_/request_parsing.h"

void print_strings(char** strings) {
  int i = 0;
  while (strings[i] != NULL) {
    printf("Field %d: %s\n", i, strings[i]);
    i++;
  }
}

char* build_http_get_response(char* url, char* msg) {
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
    return build_400_response("Unknown file type...");
  }
  char* accept_field = parse_accept_field(header);
  if (accept_field == NULL) {
    return build_400_response("No accept field was passed...");
  }

  char** accept_type = check_accept_field(accept_field);
  bool flag = false;
  for (int i = 0; i < MAX_ACCEPTS; i++) {
    if (accept_type[i] && strcmp(accept_type[i], file_type) == 0) {
      flag = true;
    }
  }
  if (!flag) {
    return build_406_response();
  }

  const int file_size = get_file_size(url);
  if (file_size > MAX_BODY_LENGTH * sizeof(char)) {
    printf("Max body length exceeded...\n");
    return build_400_response("Max body length exceeded...");
  }
  char* response = (char*) malloc(MAX_RESPONSE_LENGTH * sizeof(char));
  strcpy(response, "HTTP/1.1 200 OK\r\n");
  char* found_content_type = map_file_type_content_type(file_type);
  strcat(response, found_content_type);
  strcat(response, "\r\n");
  strcat(response, "Content-Length: ");
  char found_file_size[MAX_BODY_LENGTH];
  sprintf(found_file_size, "%d", file_size);
  strcat(response, found_file_size);
  strcat(response, "\r\n");
  strcat(response, "Connection: close");
  strcat(response, "\r\n");
  strcat(response, "Content-Encoding: identity\r\n");
  strcat(response, "\r\n");
  const char* response_body = get_file_contents(url);
  strcat(response, response_body);
  strcat(response, "\r\n");
  return response;
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
  response = build_http_get_response(url, message);

  printf("Response: \n%s\n", response);

  return 0;
}
