#include <stdio.h>
#include <unistd.h>

int main() {
    // Using setbuf to set full buffering
    char buffer[BUFSIZ];
    setbuf(stdout, buffer);

    // Writing some data to the file
    fprintf(stdout, "Hello, World!\n");

    // Writing more data to the file
    fprintf(stdout, "Line buffering example\n");

    sleep(5);


    setlinebuf(stdout);

    // Writing some data to the file
    fprintf(stdout, "I'm in linebuf mode\n");

    // Writing some data to the file
    fprintf(stdout, "Hello, World! in linebuf\n");

    // Writing more data to the file
    fprintf(stdout, "Line buffering example in linebuf \n");


    sleep(10);

    return 0;
}

