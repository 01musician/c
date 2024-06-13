#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/sub.h>

#define URL "ipc:///tmp/pubsub.ipc"

void fatal(const char *func, int rv) {
    fprintf(stderr, "%s: %s\n", func, nng_strerror(rv));
    exit(1);
}

int main() {
    nng_socket sock;
    int rv;

    if ((rv = nng_sub0_open(&sock)) != 0) {
        fatal("nng_sub0_open", rv);
    }

    if ((rv = nng_dial(sock, URL, NULL, 0)) != 0) {
        fatal("nng_dial", rv);
    }

    if ((rv = nng_setopt(sock, NNG_OPT_SUB_SUBSCRIBE, "", 0)) != 0) {
        fatal("nng_setopt", rv);
    }

    while (1) {
        char *buf = NULL;
        size_t sz;

        if ((rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC)) != 0) {
            fatal("nng_recv", rv);
        }

        printf("Received: %s\n", buf);
        nng_free(buf, sz);
    }

    nng_close(sock);
    return 0;
}

