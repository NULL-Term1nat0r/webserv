#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "10.12.11.52"   // Replace with the actual server IP address
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
	int client_socket;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];

	// Create a socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0) {
		std::cerr << "Error creating socket" << std::endl;
		return 1;
	}

	// Configure server address
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	if (inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr)) <= 0) {
		std::cerr << "Invalid server address" << std::endl;
		return 1;
	}

	// Connect to the server
	if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Error connecting to server" << std::endl;
		return 1;
	}

	while (true) {
		// Prompt user for input
		std::cout << "Enter a message (or type 'exit' to quit): ";
		std::cin.getline(buffer, sizeof(buffer));

		if (std::cin.fail()) {
			std::cerr << "Input error" << std::endl;
			break;
		}

		// Send data to the server
		ssize_t bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
		if (bytes_sent < 0) {
			std::cerr << "Error sending data" << std::endl;
			break;
		}

		// Receive and display the server's response
		memset(buffer, 0, sizeof(buffer));
		ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
		if (bytes_received < 0) {
			std::cerr << "Error receiving data" << std::endl;
			break;
		}

		std::cout << "Received from server: " << buffer << std::endl;

		// Check if the user wants to exit
		if (strcmp(buffer, "exit") == 0) {
			break;
		}
	}

	// Close the client socket
	close(client_socket);

	return 0;
}
