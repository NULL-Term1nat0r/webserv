
#include "../inc/Header.h"
#include "../inc/webServer.hpp"

// Implement class methods here

webServer::webServer()
{
	std::cout << "webServer default constructor called" << std::endl;
}

webServer::webServer(const webServer &other)
{
	*this = other;
	std::cout << "webServer copy constructor called" << std::endl;
}

webServer::~webServer()
{
	std::cout << "webServer destructor called" << std::endl;
}

webServer &webServer::operator=(const webServer &other)
{
	if (this == &other)
		return *this;
	std::cout << "webServer copy assignment constructor called" << std::endl;
	return *this;
}

int webServer::startServer(Server &serv, size_t z) {

		int server_socket;
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
		memset(&server_addr, 0, sizeof(server_addr)); //!!not needed
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(serv._server[z].port);
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

		std::cout << "Server listening on port " << serv._server[z].port << std::endl;

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
		int num_ready = poll(poll_fds.data(), poll_fds.size(), -1);
		if (num_ready < 0) {
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
			if (poll_fds[i].revents & POLLIN) {
				int client_socket = poll_fds[i].fd;
				char buffer[serv._buffSize];
				ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

				if (bytes_received <= 0) {
					// Client disconnected or error occurred
					std::cout << "Client with socket " << client_socket << " disconnected" << std::endl;
					close(client_socket);
					client_sockets.erase(client_sockets.begin() + i - 1);
					poll_fds.erase(poll_fds.begin() + i);
				} else {
					// Print the received request from the client
					std::string request(buffer, bytes_received);
					std::cout << "Received request from client with socket " << client_socket << ":" << std::endl;
					std::cout << request << std::endl;

					// Send an HTML response to the client
					std::string htmlResponse = response::getResponse();
					std::cout << "htmlResponse: " << htmlResponse << std::endl;
					send(client_socket, htmlResponse.c_str(), htmlResponse.length(), 0);

					// Close the client socket
					close(client_socket);
					client_sockets.erase(client_sockets.begin() + i - 1);
					poll_fds.erase(poll_fds.begin() + i);
				}
			}
		}
	}

		// Close the server socket (never reached in this example)
		close(server_socket);

		return 0;
}


std::string webServer::returnFileContent(std::string fileName){
	std::ifstream file(fileName.c_str());
	std::cout << "file name: " << file << std::endl;
	std::string str;
	std::string fileContent;
	if (file.is_open())
	{
		while (getline(file, str))
		{
			std::cout << str << std::endl;
			fileContent += str;
			fileContent += "\n";
		}
		file.close();
	}
	else
		return "";
	return fileContent;
}





// extract binary data from the request
// int main() {
//    // Define the boundary string from the "Content-Type" header
//    std::string boundary = "----WebKitFormBoundaryXn1EbJmGBQYg1tD4";
//
//    // Read the entire POST data as a string
//    std::string postData;
//    char c;
//    while (std::cin.get(c)) {
//        postData += c;
//    }
//
//    // Split the POST data into parts using the boundary
//    std::vector<std::string> parts;
//    size_t pos = postData.find(boundary);
//    while (pos != std::string::npos) {
//        // Extract a part and remove it from the postData
//        std::string part = postData.substr(0, pos);
//        postData.erase(0, pos + boundary.length());
//        parts.push_back(part);
//        pos = postData.find(boundary);
//    }
//
//    // Process each part (identify the JPEG file part)
//    for (const std::string& part : parts) {
//        if (part.find("Content-Type: image/jpeg") != std::string::npos) {
//            // This part contains the binary data of the uploaded JPEG file
//            std::cout << "Received JPEG file data with size: " << part.size() << " bytes" << std::endl;
//
//            // Example: Write the binary data to a JPEG file
//            std::ofstream outputFile("uploaded_image.jpeg", std::ios::binary);
//            if (outputFile) {
//                outputFile.write(part.c_str(), part.size());
//                outputFile.close();
//                std::cout << "JPEG file uploaded successfully." << std::endl;
//            } else {
//                std::cerr << "Failed to open the output file for writing." << std::endl;
//            }
//        }
//    }
//
//    return 0;
//}