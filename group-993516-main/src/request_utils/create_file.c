#include <stdio.h>
#include <string.h>
#include "request_utils.h"

int create_file(char* file_name, char* extension) {
  char* file_ext = (char*) malloc(10 * sizeof(char));
  file_ext = map_file_type_file_extension(extension);

  if (strcmp(file_ext, "UNKNOWN") == 0) {
    return 0;
  }

  char file_path[100];
  strcpy(file_path, file_name);
  strcat(file_path, file_ext);

  FILE* f;
  f = fopen(file_path, "w");

  if (f == NULL) {
    printf("Error creating file.\n");
    return -1;
  }

  fclose(f);
  return 1;
}