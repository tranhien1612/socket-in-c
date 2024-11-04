#include <stdio.h>      // for printf()
#include <string.h>     // for memset(), strcpy(), strlen()
#include <sys/socket.h> // for socket(), bind(), listen(), accept(), recv(), send()
#include <arpa/inet.h>  // for sockaddr_in, inet_addr(), htons(), ntohs(), inet_ntoa()
#include <unistd.h>     // for close()

#define PORT 8888
#define IP_ADDRESS "127.0.0.1"
#define BUFFER_SIZE 1024

int main(void)
{
    int socket_desc;
    int client_sock;
    int client_size;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char server_message[BUFFER_SIZE];
    char client_message[BUFFER_SIZE];

    // Clean buffers:
    memset(server_message, 0, sizeof(server_message));
    memset(client_message, 0, sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0)
    {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    // Bind to the set port and IP:
    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");

    // Listen for clients:
    if (listen(socket_desc, 1) < 0)
    {
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections.....\n");

    // Accept an incoming connection:
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);

    if (client_sock < 0)
    {
        printf("Can't accept\n");
        return -1;
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Receive client's message:
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
    {
        printf("Couldn't receive\n");
        return -1;
    }
    printf("Msg from client: %s\n", client_message);

    // Respond to client:
    strcpy(server_message, "This is the server's message.");

    if (send(client_sock, server_message, strlen(server_message), 0) < 0)
    {
        printf("Can't send\n");
        return -1;
    }

    // Closing the socket:
    close(client_sock);
    close(socket_desc);

    return 0;
}