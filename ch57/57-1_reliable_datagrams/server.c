#include "reliable_datagrams.h"

int main(int argc, char *argv[]) {
    /* create socket */
    struct sockaddr_un svaddr, claddr;
    int sfd;
    socklen_t len;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
        exit(1); // Failed to create the socket

    if (remove(SOCKET_PATH) == -1 && errno != ENOENT)
        exit(1); // Couldn't unlink the socket address filepath

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCKET_PATH, sizeof(svaddr.sun_path) - 1);

    if (bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1)
        exit(1); // Couldn't bind

    for (int i = 1; ; ++i) {
        // Just eat up the datagram but wait a long time
        recvfrom(sfd, buf, BUF_SIZE, 0,
                (struct sockaddr *) &claddr, &len);
        printf("Received %dth datagram: %s\n", i, buf);
        sleep(2);
    }
}
