#include <string.h>

char* map_file_type_file_extension(char* file_type) {
  if (strcmp(file_type, "TXT") == 0) {
    return ".txt";
  } else if (strcmp(file_type, "HTML") == 0) {
    return ".html";
  } else if (strcmp(file_type, "JSON") == 0) {
    return ".json";
  } else if (strcmp(file_type, "PNG") == 0) {
    return ".png";
  } else if (strcmp(file_type, "JPEG") == 0) {
    return ".jpeg";
  } else {
    return "UNKNWON";
  }
}