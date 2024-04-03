#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LEN 256

char* check_file_type(char* url) {
  char* type = (char*) malloc(MAX_URL_LEN * sizeof(char));
  strcpy(type, "UNKNOWN");

  FILE* file = fopen(url, "r");
  if (file) {
    int len = strlen(url);
    if (len >= 5 && strcmp(url + len - 5, ".html") == 0) {
      strcpy(type, "HTML");
    } else if (len >= 4 && strcmp(url + len - 4, ".txt") == 0) {
      strcpy(type, "TXT");
    } else if (len >= 5 && strcmp(url + len - 5, ".json") == 0) {
      strcpy(type, "JSON");
    } else if (len >= 5 && strcmp(url + len - 5, ".jpeg") == 0) {
      strcpy(type, "JPEG");
    } else if (len >= 4 && strcmp(url + len - 4, ".png") == 0) {
      strcpy(type, "PNG");
    }
    fclose(file);
  }

  return type;
}

static int main() {
  char file_txt_url[] = "../directory/truc.txt";
  char* file_type = check_file_type(file_txt_url);
  printf("The type of the file : %s is: %s\n", file_txt_url, file_type);

  char file_html_url[] = "../directory/test.html";
  file_type = check_file_type(file_html_url);
  printf("The type of the file : %s is: %s\n", file_html_url, file_type);

  char file_json_url[] = "../directory/test.json";
  file_type = check_file_type(file_json_url);
  printf("The type of the file : %s is: %s\n", file_json_url, file_type);

  char file_jpeg_url[] = "../directory/image.jpeg";
  file_type = check_file_type(file_jpeg_url);
  printf("The type of the file : %s is: %s\n", file_jpeg_url, file_type);

  char file_png_url[] = "../directory/image.png";
  file_type = check_file_type(file_png_url);
  printf("The type of the file : %s is: %s\n", file_png_url, file_type);

  return 0;
}