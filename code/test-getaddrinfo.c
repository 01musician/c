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
    char ip_str[INET_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Use IPv4
    hints.ai_socktype = SOCK_DGRAM;

    if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IPv4 addresses for host %s:\n", hostname);

    for (p = res; p != NULL; p = p->ai_next) {
        if (p->ai_family == AF_INET) { // Filter only IPv4 addresses
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            inet_aton(ip_str, &(ipv4->sin_addr));
            printf("%s\n", ip_str);
        }
    }

    freeaddrinfo(res);

    return 0;
}
