#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *get_content_type(char *content_type_value) {
  if (strcmp(content_type_value, "text/plain") == 0) {
    return "TXT";
  } else if (strcmp(content_type_value, "text/html") == 0) {
    return "HTML";
  } else if (strcmp(content_type_value, "application/json") == 0) {
    return "JSON";
  } else if (strcmp(content_type_value, "image/jpeg") == 0) {
    return "JPEG";
  } else if (strcmp(content_type_value, "image/png") == 0) {
    return "PNG";
  } else {
    return "UNKNOWN";
  }
}

static int main() {
  printf("%s\n", get_content_type("text/plain"));
  printf("%s\n", get_content_type("text/html"));
  printf("%s\n", get_content_type("application/json"));
  printf("%s\n", get_content_type("image/jpeg"));
  printf("%s\n", get_content_type("image/png"));
  printf("%s\n", get_content_type("unknown"));
  return 0;
}