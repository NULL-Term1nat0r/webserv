//
// Created by Eike Maximilian Struckmeier on 9/29/23.
//
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 8080

int main() {
	int server_socket, client_socket;
	struct sockaddr_in server_addr;

	// Create a socket
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

		std::cout << "Accepted new connection" << std::endl;

		// Handle data from the client here
		char buffer[1024];
		ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
		if (bytes_received <= 0) {
			// Client disconnected or error occurred
			std::cout << "Client disconnected" << std::endl;
		} else {
			// Echo the received data back to the client
//			std::cout << "send string by client " << client_socket << " : " << buffer << std::endl;
			const char* html_code =
					"<!DOCTYPE html>\n"
					"<html>\n"
					"<head>\n"
					"    <title>My Simple Web Page</title>\n"
					"</head>\n"
					"<body>\n"
					"    <h1>Welcome to My Web Page</h1>\n"
					"    <p>This is a simple HTML webpage.</p>\n"
					"    <ul>\n"
					"        <li>Item 1</li>\n"
					"        <li>Item 2</li>\n"
					"        <li>Item 3</li>\n"
					"    </ul>\n"
					"    <p>Thanks for visiting!</p>\n"
					"</body>\n"
					"</html>";
//			send(client_socket, buffer, bytes_received, 0);
			send(client_socket, html_code, strlen(html_code), 0);

		}

		// Close the client socket
		close(client_socket);
	}

	// Close the server socket (never reached in this example)
	close(server_socket);

	return 0;
}


<!DOCTYPE html>
<html>
<head>
<title>Text Box with Scrollbar</title>
</head>
<body>
<h2>Enter your text:</h2>
<textarea id="myTextarea" rows="4" cols="50" placeholder="Type your message here..."></textarea>
<br>
<button onclick="postMessage()">Post</button>

				<script>
				function postMessage() {
	// Get the text from the textarea
	var text = document.getElementById("myTextarea").value;

	// You can perform actions with the text, such as sending it to a server

	// For this example, we'll just display an alert
	alert("Posted Message:\n" + text);
}
</script>
</body>
</html>