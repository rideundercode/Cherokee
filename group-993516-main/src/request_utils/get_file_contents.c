#include <stdio.h>
#include <stdlib.h>

char *get_file_contents(const char *url) {
  FILE *fp;
  char *contents;
  int file_size, bytes_read;

  // Open the file
  fp = fopen(url, "rb");
  if (!fp) {
    return NULL;
  }

  // Get the size of the file
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  // Allocate memory for the contents of the file
  contents = (char *)malloc(file_size + 1);
  if (!contents) {
    fclose(fp);
    return NULL;
  }

  // Read the contents of the file into the allocated memory
  bytes_read = fread(contents, 1, file_size, fp);
  if (bytes_read != file_size) {
    free(contents);
    fclose(fp);
    return NULL;
  }

  // Null-terminate the string
  contents[file_size] = '\0';

  fclose(fp);
  return contents;
}
