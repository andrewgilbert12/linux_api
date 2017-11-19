#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if(argc < 3 || argc > 4){
    exit(EXIT_FAILURE);
  }

  int noapp = (argc == 4 && *argv[3] == 'x');
  if(noapp)
    printf("Noapp mode");

  int file = open(argv[1], noapp ? O_WRONLY : O_WRONLY | O_APPEND);
  if(file == -1)
    exit(EXIT_FAILURE);

  for(int i = 0; i < atoi(argv[2]); ++i){
    if(noapp){
      if(lseek(file, 0, SEEK_END) == -1)
	exit(EXIT_FAILURE);
      if(write(file, "x", 1) != 1)
	exit(EXIT_FAILURE);
    } else {
      if(write(file, "x", 1) != 1)
	exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
