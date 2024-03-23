#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int 
main(char *argv[], int argc)
{
    printf("%%-5s  %%-10s.\n");
    printf("%-5s %-10s.\n", "linux", "linux");
    printf("%%5s  %%10s.\n");
    printf("%5s %10s.\n", "linux", "linux");
    printf("sizeof(int) %ld.\n", sizeof(int));
    printf("sizeof(long) %ld.\n", sizeof(long));
    printf("sizeof(long long) %ld.\n", sizeof(long long));
    
    return 0;
}

