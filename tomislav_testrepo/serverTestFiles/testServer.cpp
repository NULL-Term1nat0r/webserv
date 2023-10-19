#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <vector>

#define SERVER_PORT 8080
#define MAX_CLIENTS 10  // Adjust as needed

int main() {
	int server_socket;
	struct sockaddr_in server_addr;

	// Create a socket
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket < 0) {
		std::cerr << "Error creating socket" << std::endl;
		return 1;
	}

	// Set the SO_REUSEADDR option
	int reuse = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		std::cerr << "Error setting SO_REUSEADDR" << std::endl;
		return 1;
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
	if (listen(server_socket, 5) < 0) {
		std::cerr << "Error listening" << std::endl;
		return 1;
	}

	std::cout << "Server listening on port " << SERVER_PORT << std::endl;

	// Create a vector to store client sockets
	std::vector<int> client_sockets;

	// Create and initialize pollfd structures
	std::vector<pollfd> poll_fds;
	pollfd server_pollfd;
	server_pollfd.fd = server_socket;
	server_pollfd.events = POLLIN;
	poll_fds.push_back(server_pollfd);

	while (true) {
		// Call poll() to wait for events on all file descriptors
		if( poll(poll_fds.data(), poll_fds.size(), -1) < 0)
		{
			std::cerr << "Error in poll" << std::endl;
			return 1;
		}

		// Check if the server socket has an event (incoming connection)
		if (poll_fds[0].revents & POLLIN) {
			int client_socket = accept(server_socket, nullptr, nullptr);
			if (client_socket < 0) {
				std::cerr << "Error accepting connection" << std::endl;
			} else {
				std::cout << "Accepted new connection" << std::endl;
				client_sockets.push_back(client_socket);

				// Add the new client socket to the pollfds
				pollfd client_pollfd;
				client_pollfd.fd = client_socket;
				client_pollfd.events = POLLIN;
				poll_fds.push_back(client_pollfd);
			}
		}

		// Check events for each client socket
		for (size_t i = 1; i < poll_fds.size(); ++i) {
			std::cout << "i: " << i << std::endl;
			if (poll_fds[i].revents & POLLIN) {
				int client_socket = poll_fds[i].fd;
				// Handle data from the client here
				// ...

				// Example: Echo data back to the client
				char buffer[1024];
				ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
//				std::cout << "string recieved: " << buffer << std::endl;
//				buffer[bytes_received] = '\0'; // Add null terminator
				if (bytes_received <= 0) {
					// Client disconnected or error occurred
					std::cout << "Client with socket " << client_socket << " disconnected" << std::endl;
					close(client_socket);
					client_sockets.erase(client_sockets.begin() + i - 1);
					poll_fds.erase(poll_fds.begin() + i);
				} else {
					const char *message = "SERVER RECIEVED: ";

					// Echo the received data back to the client
					send(client_socket, buffer, strlen(buffer), 0);
				}
			}
		}
	}

	// Close the server socket (never reached in this example)
	close(server_socket);

	return 0;
}
