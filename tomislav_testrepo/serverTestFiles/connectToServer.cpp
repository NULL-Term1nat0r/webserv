#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring> // Added for memset

int main() {
	int clientSocket;
	struct sockaddr_in serverAddr;

	// Create a socket
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Server information setup
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080); // Server's port
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server's IP address

	// Connect to the server
	if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("Connect failed");
		return 1;
	}
	char message[254];
	std::cout << "message the server should recieve: "<<std::endl;
	if (fgets(message, 1024, stdin) == nullptr) {
		std::cerr << "Error reading input." << std::endl;
		return 1; // Exit with an error code
	}
	printf("message: %s\n", message);
	// Send data to the server
	int bytes_sent;
	bytes_sent = send(clientSocket, message, strlen(message), 0);
	if (bytes_sent == -1) {
		std::cerr << "Error sending data" << std::endl;
		return 1;
	}

	// Receive and print the response from the server
	char buffer[1024]; // Buffer to store received data
	int bytes_received = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (bytes_received == -1) {
		std::cerr << "Error receiving data" << std::endl;
		return 1;
	} else if (bytes_received == 0) {
		std::cerr << "Server closed the connection" << std::endl;
	} else {
		// Null-terminate the received data to treat it as a C string
		buffer[bytes_received] = '\0';
		std::cout << "Received from server: " << buffer << std::endl;
	}

	// Close the socket when done
	close(clientSocket);

	return 0;
}
