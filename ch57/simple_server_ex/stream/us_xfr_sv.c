#include "us_xfr.h"

#define BACKLOG 5

int main(int argc, char *arv[]) {
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        exit(1); // socket creation failure

    /* Construct server socket address, bind it to socket,
     * and make this a listening socket */

    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
        exit(1); // socket path can't be unlinked...

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) -1);

    if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
        exit(1); // couldn't bind socket

    if (listen(sfd, BACKLOG) == -1)
        exit(1); // couldn't listen

    for (;;) {

        /* Accept a connection from client. The connection is returned on a new socket,
         * pointed to by cfd, leaving the listening socket (sfd) open to accept new connections. */

        cfd = accept(sfd, NULL, NULL); // we don't care about the address of cfd so we specify NULL, NULL
        if (cfd == -1)
            exit(1); // couldn't accept

        /* Transfer data from socket to stdout until EOF */

        while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                exit(1); // partial write failure 

        if (numRead == -1)
            exit(1); // read error

        if (close(cfd) == -1)
            exit(1); // close error
    }
}
