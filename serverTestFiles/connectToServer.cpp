//
// Created by Eike Maximilian Struckmeier on 9/28/23.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
	int clientSocket;
	struct sockaddr_in serverAddr;

	// Create a socket
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Server information setup
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080); // Server's port
	serverAddr.sin_addr.s_addr = inet_addr("10.12.11.52"); // Server's IP address

	// Connect to the server
//	int i = 0;
//	while (i < 11)
//	{
//
//		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
//		if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
//			perror("Connect failed");
//			return 1;
//		}
//		i++;
//	}
	if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("Connect failed");
		return 1;
	}
	const char *message = "Hello, Server!";
	send(clientSocket, message, strlen(message), 0);

	// Use the clientSocket for communication with the server

	// Close the socket when done
	close(clientSocket);

	return 0;
}