//
// Created by Eike Maximilian Struckmeier on 9/29/23.
//
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <fstream>
#include <ctype.h>

#define SERVER_PORT 8080
#define MAX_REQUEST_SIZE 2048

void handle_client(int client_socket);

int main() {
	int server_socket, client_socket;
	struct sockaddr_in server_addr;

	// Create a socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		std::cerr << "Error creating socket" << std::endl;
		return 1;
	}

	int reuse = 1;

	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
		perror("setsockopt");
		close(server_socket);
		exit(EXIT_FAILURE);
	}

	// Configure server address
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to the server address
	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Error binding socket" << std::endl;
		return 1;
	}

	// Listen for incoming connections
	if (listen(server_socket, 5) < 0) { // Allow only one client connection
		std::cerr << "Error listening" << std::endl;
		return 1;
	}

	std::cout << "Server listening on port " << SERVER_PORT << std::endl;

	while (true) {
		// Accept a single client connection
		client_socket = accept(server_socket, nullptr, nullptr);
		if (client_socket < 0) {
			std::cerr << "Error accepting connection" << std::endl;
			return 1;
		}

		// Handle the client in a new process
		if (fork() == 0) {
			close(server_socket);  // Child process doesn't need the listening socket
			handle_client(client_socket);
			close(client_socket);
			return 0;  // Child process exits
		} else {
			close(client_socket);  // Parent process doesn't need the client socket
		}
	}

	// Close the server socket (never reached in this example)
	close(server_socket);

	return 0;
}

void handle_client(int client_socket) {
	char request[MAX_REQUEST_SIZE];
	ssize_t bytes_received = recv(client_socket, request, sizeof(request), 0);
	if (bytes_received <= 0) {
		// Client disconnected or error occurred
		std::cout << "Client disconnected" << std::endl;
		return;
	}

	// Extract the requested URL from the HTTP request (simplified)
	std::string request_str(request, bytes_received);
	size_t start = request_str.find("GET ") + 4;
	size_t end = request_str.find(" HTTP/");
	std::cout << request << std::endl;
	if (start != std::string::npos && end != std::string::npos) {
		std::string requested_url = request_str.substr(start, end - start);

		// Serve the requested file (simplified)
		std::string file_path = "." + requested_url; // Assuming files are in the current directory
		int file_fd = open(file_path.c_str(), O_RDONLY);
		if (file_fd < 0) {
			// File not found
			std::string response = "HTTP/1.1 404 Not Found\r\n\r\nFile Not Found";
			send(client_socket, response.c_str(), response.size(), 0);
		} else {
			// File found, read and send its content
			char buffer[1024];
			ssize_t bytes_read;
			std::string response = "HTTP/1.1 200 OK\r\n\r\n";
			send(client_socket, response.c_str(), response.size(), 0);

			while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) {
				send(client_socket, buffer, bytes_read, 0);
			}
			close(file_fd);
		}
	}

	// Close the client socket
	close(client_socket);
}
