#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[MAX_BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
	    // Receive data from the server
	    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
	    if (bytesRead == -1) {
		    perror("Error receiving data");
		    break;
	    } else if (bytesRead == 0) {
		    printf("Server closed the connection.\n");
		    break;
	    } else {
		    buffer[bytesRead] = '\0';  // Null-terminate the received data
		    printf("Received data from server: %s\n", buffer);
		    clientSocket=100;
	    }
    }

    // Clean up
    close(clientSocket);

    return 0;
}

