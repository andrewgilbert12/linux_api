#include "reliable_datagrams.h"

int main(int argc, char *argv[]) {
    /* create socket */
    struct sockaddr_un svaddr;
    int cfd;

    cfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (cfd == -1)
        exit(1); // Failed to create the socket

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCKET_PATH, sizeof(svaddr.sun_path) - 1);

    for (int i = 1; ; ++i) {
        // send a datagram
        sendto(cfd, "hello", 6, 0, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un));
        printf("Sent %d datagrams...\n", i);
    }

}
