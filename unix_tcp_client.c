#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 255

int main(int argc, char* argv[])
{
    // Declaration
    int client_socket;
    struct sockaddr_in client_addr;
    char buffer[BUFFER_SIZE];
    int bytes_received;
    
    // Client socket creation
    client_socket = socket(
        AF_INET, /* IPv4 */
        SOCK_STREAM, /* TCP */
        0
    );
    
    // Defining IP:PORT
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(atoi(argv[1]));
    client_addr.sin_addr.s_addr = INADDR_ANY; /* 127.0.0.1 */
    
    // Create connection
    connect(client_socket, (const struct sockaddr*)&client_addr, sizeof(client_addr));
    
    // Data exchange with client
    for(;;){
        // Sending data to client
        printf("Send to server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(client_socket, buffer, strlen(buffer), 0);
        
        memset(buffer, 0, BUFFER_SIZE);
        // Receiving data from client
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE-1, 0);
        printf("Server: %s\n", buffer);
    }
    
    // Closing communication
    close(client_socket);
    
    return 0;
}