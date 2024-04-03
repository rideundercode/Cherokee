#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request_utils.h"

char** check_accept_field(char* accept_field) {
  printf("ACCEPT : %s\n", accept_field);
  char** formats = (char**) malloc(MAX_ACCEPTS * sizeof(char*));
  for (int i = 0; i < MAX_ACCEPTS; i++) {
    formats[i] = (char*) malloc(MAX_LENGTH * sizeof(char));
  }

  int format_count = 0;
  if (strncmp(accept_field, "*/*", 3) == 0) {
    strcpy(formats[format_count++], "TXT");
    strcpy(formats[format_count++], "HTML");
    strcpy(formats[format_count++], "JSON");
    strcpy(formats[format_count++], "JPEG");
    strcpy(formats[format_count++], "PNG");
    return formats;
  }

  char* format = strtok(accept_field, ",");
  while (format != NULL && format_count < MAX_ACCEPTS) {
    if (strstr(format, "text/plain")) {
      strcpy(formats[format_count++], "TXT");
    } else if (strstr(format, "text/html")) {
      strcpy(formats[format_count++], "HTML");
    } else if (strstr(format, "application/json")) {
      strcpy(formats[format_count++], "JSON");
    } else if (strstr(format, "image/jpeg")) {
      strcpy(formats[format_count++], "JPEG");
    } else if (strstr(format, "image/png")) {
      strcpy(formats[format_count++], "PNG");
    }
    format = strtok(NULL, ",");
  }

  return formats;
}

static int main() {
  char accept_field1[] = "text/plain,application/json";
  char accept_field2[] = "text/html,image/jpeg,image/png";
  char accept_field3[] = "application/json";
  char accept_field4[] = "";
  char accept_field5[] = "*/*";

  char** accepts1 = check_accept_field(accept_field1);
  char** accepts2 = check_accept_field(accept_field2);
  char** accepts3 = check_accept_field(accept_field3);
  char** accepts4 = check_accept_field(accept_field4);
  char** accepts5 = check_accept_field(accept_field5);

  printf("Accepts for accept field 1: \n");
  for (int i = 0; i < MAX_ACCEPTS && strlen(accepts1[i]) > 0; i++) {
    printf("%s\n", accepts1[i]);
  }
  printf("Accepts for accept field 2: \n");
  for (int i = 0; i < MAX_ACCEPTS && strlen(accepts2[i]) > 0; i++) {
    printf("%s\n", accepts2[i]);
  }
  printf("Accepts for accept field 3: \n");
  for (int i = 0; i < MAX_ACCEPTS && strlen(accepts3[i]) > 0; i++) {
    printf("%s\n", accepts3[i]);
  }
  printf("Accepts for accept field 4: \n");
  for (int i = 0; i < MAX_ACCEPTS && strlen(accepts4[i]) > 0; i++) {
    printf("%s\n", accepts4[i]);
  }
  printf("Accepts for accept field 5: \n");
  for (int i = 0; i < MAX_ACCEPTS && strlen(accepts5[i]) > 0; i++) {
    printf("%s\n", accepts5[i]);
  }

  return 0;
}
