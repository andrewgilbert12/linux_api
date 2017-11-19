#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // file control
#include <stdio.h> // stdin, stdout
#include <stdlib.h> // exit
#include <unistd.h> // getopt, STDIN_FILENO, STDOUT_FILENO

// Simple implementation of cp

void print_help(char *filename)
{
  printf("%s src dest\n", filename);
}

int main (int argc, char ** argv) {
  if(argc != 3) { // TODO change after adding options
    print_help(argv[0]);
    exit(EXIT_FAILURE);
  }

  int opt;

  /* no options */
  while((opt = getopt(argc, argv, "a")) != -1) {
    switch(opt) {
    default:
      print_help(argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  int src, dest;

  if((src = open(argv[optind], O_RDONLY)) == -1) {
    printf("Couldn't open %s\n", argv[optind]);
    exit(EXIT_FAILURE);
  }

  struct stat *srcstats;
  if(fstat(src, srcstats) == -1) {
    perror("Couldn't stat source file.");
    exit(EXIT_FAILURE);
  }

  if((dest = open(argv[optind + 1], O_WRONLY | O_CREAT | O_TRUNC, srcstats->st_mode)) == -1) { // TODO won't reset permissions for an already existing file?
    printf("Couldn't open %s\n", argv[optind]);
    exit(EXIT_FAILURE);
  }

  #ifndef BUFFER_SIZE
  #define BUFFER_SIZE 1024
  #endif 

  char buffer[BUFFER_SIZE];

  ssize_t readsize, writesize;
  while((readsize = read(src, buffer, BUFFER_SIZE))) {
    // write to stdout
    if((writesize = write(dest, buffer, readsize)) == -1) {
      perror("Copy to dest error"); 
      exit(EXIT_FAILURE);
    }
  }

  if(readsize == -1) {
    perror("Read error");
    exit(EXIT_FAILURE); 
  }

  if(close(src) == -1) {
    perror("Close src error");
    exit(EXIT_FAILURE);
  }

  if(close(dest) == -1) {
    perror("Close dest error");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
