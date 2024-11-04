#include <stdio.h>		// for printf(), gets()
#include <string.h>		// for memset(), strcpy(), strlen()
#include <sys/socket.h> // for socket(), recvfrom(), sendto()
#include <arpa/inet.h>	// for sockaddr_in, inet_addr(), htons()
#include <unistd.h>		// for close()

#define PORT 8888
#define IP_ADDRESS "127.0.0.1"
#define BUFFER_SIZE 1024

int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr;
	int server_struct_length = sizeof(server_addr);
	char server_message[BUFFER_SIZE];
	char client_message[BUFFER_SIZE];

	// Clean buffers:
	memset(server_message, 0, sizeof(server_message));
	memset(client_message, 0, sizeof(client_message));

	// Create socket:
	socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

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

	// Get input from the user:
	printf("Enter message: ");
	fgets(client_message, BUFFER_SIZE, stdin);

	// Send the message to server:
	if (sendto(socket_desc, client_message, strlen(client_message), 0,
			   (struct sockaddr *)&server_addr, server_struct_length) < 0)
	{
		printf("Unable to send message\n");
		return -1;
	}

	// Receive the server's response:
	if (recvfrom(socket_desc, server_message, sizeof(server_message), 0,
				 (struct sockaddr *)&server_addr, &server_struct_length) < 0)
	{
		printf("Error while receiving server's msg\n");
		return -1;
	}

	printf("Server's response: %s\n", server_message);

	// Close the socket:
	close(socket_desc);

	return 0;
}
