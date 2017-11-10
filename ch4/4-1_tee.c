#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // file control
#include <stdio.h> // stdin, stdout
#include <stdlib.h> // exit
#include <unistd.h> // getopt, STDIN_FILENO, STDOUT_FILENO

// Simple implementation of tee

int
main (int argc, char ** argv){

  if(argc < 2 || argc > 3){
    printf("%s [-a] file", argv[0]);
    exit(EXIT_FAILURE);
  }

  int append, opt;

  append = 0;
  while((opt = getopt(argc, argv, "a")) != -1){
    switch(opt) {
    case 'a':
      append = 1;
      break;
    default:
      printf("%s [-a] file", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  int file;

  file = open(argv[optind],
              O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC),
              S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
  if(file == -1){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  #ifndef BUFFER_SIZE
  #define BUFFER_SIZE 1024
  #endif 

  char buffer[BUFFER_SIZE];

  ssize_t readsize, writesize;
  while((readsize = read(STDIN_FILENO, buffer, BUFFER_SIZE))){
    // write to stdout
    if((writesize = write(STDOUT_FILENO, buffer, readsize)) == -1){
      perror("Write to STDOUT error");
      exit(EXIT_FAILURE);
    }

    // write to file 
    if((writesize = write(file, buffer, readsize)) == -1){
      perror("Write to file error");
      exit(EXIT_FAILURE);
    }
  }

  if(readsize == -1){
    perror("Read error");
    exit(EXIT_FAILURE); 
  }

  if(close(file) == -1){
    perror("Close file error");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
