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
    int server_socket;
    struct sockaddr_in serv_addr;
    int client_socket;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Server socket creation
    server_socket = socket(
        AF_INET, /* IPv4 */
        SOCK_STREAM, /* TCP */
        0
    );

    // Defining IP:PORT
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = INADDR_ANY; /* 127.0.0.1 */

    // Binding our socket to IP:PORT
    bind(server_socket, (const struct sockaddr*) &serv_addr, sizeof(serv_addr));

    // Listening in the IP:PORT
    listen(server_socket, SOMAXCONN);

    // Accepting in the IP:PORT
    client_socket = accept(server_socket, NULL, NULL);

    // Data exchange with client
    for(;;){
        // Receiving data from client
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE-1, 0);
        printf("Client: %s\n", buffer);
        
        memset(buffer, 0, BUFFER_SIZE);
        // Sending data to client
        printf("Send to client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    // Closing connections
    close(client_socket);
    close(server_socket);

    return 0;
}