#include <stdio.h>
#include <stdbool.h>

bool check_file_exists(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file) {
    fclose(file);
    return true;
  }
  return false;
}

static int main() {
  const char* filename = "example.txt";
  bool fileExists = check_file_exists(filename);
  if (fileExists) {
    printf("File %s exists.\n", filename);
  } else {
    printf("File %s does not exist.\n", filename);
  }
  return 0;
}