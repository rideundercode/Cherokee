#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "request_utils.h"

char* map_file_type_content_type(char* content_format) {
  char* content_type = (char*) malloc(MAX_LENGTH * sizeof(char));
  if (strstr(content_format, "TXT")) {
    strcpy(content_type, "Content-Type: text/plain");
  } else if (strstr(content_format, "HTML")) {
    strcpy(content_type, "Content-Type: text/html; charset=utf-8");
  } else if (strstr(content_format, "JSON")) {
    strcpy(content_type, "Content-Type: application/json");
  } else if (strstr(content_format, "JPEG")) {
    strcpy(content_type, "Content-Type: image/jpeg");
  } else if (strstr(content_format, "PNG")) {
    strcpy(content_type, "Content-Type: image/png");
  } else {
    strcpy(content_type, "Content-Type: text/plain");
  }
  return content_type;
}

static int main() {
  char* txt_content_type = map_file_type_content_type("TXT");
  printf("TXT content type: %s\n", txt_content_type);

  char* html_content_type = map_file_type_content_type("HTML");
  printf("HTML content type: %s\n", html_content_type);

  char* json_content_type = map_file_type_content_type("JSON");
  printf("JSON content type: %s\n", json_content_type);

  char* jpeg_content_type = map_file_type_content_type("JPEG");
  printf("JPEG content type: %s\n", jpeg_content_type);

  char* png_content_type = map_file_type_content_type("PNG");
  printf("PNG content type: %s\n", png_content_type);

  return 0;
}