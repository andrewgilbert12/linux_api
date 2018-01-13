#include "us_toupper.h"

/* Simple server that receives datagrams, responds to the
 * client with the datagram message converted to uppercase */

int main(int argc, char *arv[]) {
    struct sockaddr_un svaddr, claddr;
    int sfd, j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
        exit(1); // socket creation failure

    /* Construct well-known address, bind server socket to it */

    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
        exit(1); // socket path can't be unlinked...

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) -1);

    if (bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1)
        exit(1); // couldn't bind socket

    for (;;) {

        /* Accept a connection from client. The connection is returned on a new socket,
         * pointed to by cfd, leaving the listening socket (sfd) open to accept new connections. */

        len = sizeof(struct sockaddr_un);
        numBytes = recvfrom(sfd, buf, BUF_SIZE, 0,
                (struct sockaddr *) &claddr, &len);

        if (numBytes == -1)
            exit(1); // couldn't receive datagram

        printf("Server received %ld bytes from %s\n", (long) numBytes, claddr.sun_path);

        for (j = 0; j < numBytes; j++)
            buf[j] = toupper((unsigned char) buf[j]);

        if (sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, len) != numBytes)
            exit(1); // send to error
    }
}
