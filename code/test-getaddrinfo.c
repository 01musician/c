#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
        return 1;
    }

    struct addrinfo hints, *res, *p;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Use IPv4

    if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IPv4 addresses for host %s:\n", hostname);

    for (p = res; p != NULL; p = p->ai_next) {
        if (p->ai_family == AF_INET) { // Filter only IPv4 addresses
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(ipv4->sin_addr), ip_str, INET_ADDRSTRLEN);
            printf("%s\n", ip_str);
        }
    }

    freeaddrinfo(res);

    return 0;
}
