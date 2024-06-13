#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>

#define URL "ipc:///tmp/pubsub.ipc"

void fatal(const char *func, int rv) {
    fprintf(stderr, "%s: %s\n", func, nng_strerror(rv));
    exit(1);
}

int main() {
    nng_socket sock;
    int rv;

    if ((rv = nng_pub0_open(&sock)) != 0) {
        fatal("nng_pub0_open", rv);
    }

    if ((rv = nng_listen(sock, URL, NULL, 0)) != 0) {
        fatal("nng_listen", rv);
    }

    while (1) {
        char *msg = "Hello, NNG!";
        printf("Publishing: %s\n", msg);
        if ((rv = nng_send(sock, msg, strlen(msg) + 1, 0)) != 0) {
            fatal("nng_send", rv);
        }
        nng_msleep(1000); // Sleep for 1 second
    }

    nng_close(sock);
    return 0;
}

