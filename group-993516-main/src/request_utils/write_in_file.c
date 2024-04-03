#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_in_file(char* file_name, char* content) {
  FILE* f;
  f = fopen(file_name, "a");

  if (f == NULL) {
    return 0; // File does not exist
  }

  if (fputs(content, f) == EOF) {
    fclose(f);
    return -1; // Error writing to file
  }

  fclose(f);
  return 1; // Success
}