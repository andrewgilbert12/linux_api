#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/reliable_datagram_socket_test"
#define BUF_SIZE 10
