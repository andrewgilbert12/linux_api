#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SV_SOCK_PATH "us_xfr_sock"

#define BUF_SIZE 100