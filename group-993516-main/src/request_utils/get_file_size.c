#include <stdio.h>
#include <stdlib.h>

int get_file_size(const char *url) {
  FILE *fp;
  int file_size;

  // Open the file
  fp = fopen(url, "rb");
  if (!fp) {
    return -1;
  }

  // Get the size of the file
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  fclose(fp);

  return file_size;
}

static int main() {
  const char *fake_url = "../directory/test.json";
  int file_size;

  file_size = get_file_size(fake_url);
  if (file_size < 0) {
    printf("Failed to get file size for URL %s\n", fake_url);
    return 1;
  }

  printf("The size of the file at URL %s is %d bytes\n", fake_url, file_size);
  return 0;
}