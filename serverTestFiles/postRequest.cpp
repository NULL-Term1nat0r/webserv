#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int PORT = 8080;

const char* htmlResponse = "HTTP/1.1 200 OK\r\n"
						   "Content-Length: 27\r\n"
						   "Content-Type: text/html\r\n\r\n"
						   "<html><body>Hello, World!</body></html>";

std::string getBinary(char *buffer, int bytesRead){
	char* bodyStart = strstr(buffer, "\r\n\r\n");
	if (bodyStart != NULL) {
		bodyStart += 4; // Move past the empty line

		// Calculate the length of the request body
		int bodyLength = bytesRead - (bodyStart - buffer);

		// Assuming you have identified the content length, you can read the binary data
		// Here, we read all the binary data as an example
		char binaryData[bodyLength];
		memcpy(binaryData, bodyStart, bodyLength);
		return binaryData;
}

int main() {
	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[1024];

	// Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("Error opening socket");
		return 1;
	}

	struct sockaddr_in server_addr, client_addr;
	bzero((char *)&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to the server address
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("Error on binding");
		return 1;
	}

	listen(sockfd, 5);
	clilen = sizeof(client_addr);

	std::cout << "Listening on port " << PORT << "..." << std::endl;

	while (1) {
		newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &clilen);

		if (newsockfd < 0) {
			perror("Error on accept");
			return 1;
		}

		bzero(buffer, 1024);

		int n = read(newsockfd, buffer, 1023);
		if (n < 0) {
			perror("Error reading from socket");
			return 1;
		}

		// Send a static HTML response
		n = write(newsockfd, htmlResponse, strlen(htmlResponse));

		if (n < 0) {
			perror("Error writing to socket");
			return 1;
		}

		close(newsockfd);
	}

	close(sockfd);
	return 0;
}
