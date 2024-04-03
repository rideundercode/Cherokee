#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int delete_file(char *filename) {
  // Check if file exists
    if (access(filename, F_OK) != 0) {
      printf("File %s does not exist.\n", filename);
      return 0;
    }

    // Delete the file
    int status = remove(filename);

    if (status == 0) { // If file was deleted successfully
      printf("File %s deleted successfully.\n", filename);
      return 1;
    }
    else { // If file was not deleted successfully
      perror("Error deleting file");
      return -1;
    }
}