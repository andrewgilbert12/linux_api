#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if(argc != 3){
    printf("Usage: %s file bytes", argv[0]);
    exit(EXIT_FAILURE);
  }

  int file = open(argv[1], O_WRONLY | O_APPEND);
  if(file == -1)
    exit(EXIT_FAILURE);

  if(lseek(file, atoi(argv[2]), SEEK_SET) == -1)
    exit(EXIT_FAILURE);

  if(write(file, "x", 10) != 1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
