#include <iostream>
#include <cstring>
#include <unistd.h>

#define MAX_LINE_LENGTH 4096 // Maximum line length

void test(int *socket) {
	*socket = 2;
}
std::string readNextLine(int fileDescriptor) {
	static char buffer[MAX_LINE_LENGTH];
	static ssize_t bytesRead = 0;
	static char* currentPosition = buffer;

	std::string line;
	bool lineComplete = false;

	while (!lineComplete) {
		if (currentPosition >= buffer + bytesRead) {
			// Refill the buffer
			bytesRead = read(fileDescriptor, buffer, MAX_LINE_LENGTH);

			if (bytesRead <= 0) {
				// End of file or error
				break;
			}

			currentPosition = buffer;
		}

		// Find the end of the line
		char* lineEnd = strchr(currentPosition, '\n');
		if (lineEnd) {
			// Line found
			size_t lineLength = lineEnd - currentPosition;
			line.append(currentPosition, lineLength);
			currentPosition = lineEnd + 1; // Move past the '\n'
			lineComplete = true;
		} else {
			// Line not complete in this buffer, append all of it
			line.append(currentPosition, bytesRead - (currentPosition - buffer));
			currentPosition = buffer + bytesRead; // Indicate buffer is empty
		}
	}

	return line;
}

int main() {

	const char* filename = "clientRequest.cpp"; // Replace with your file's path
	int fileDescriptor = open(filename, O_RDONLY);

	if (fileDescriptor == -1) {
		std::cerr << "Error opening the file." << std::endl;
		return 1;
	}
	std::string line;
	while (true) {
		line = readNextLine(fileDescriptor);
		if (line.empty()) {
			break; // End of file or error
		}
		std::cout << "Line: " << line << std::endl;
	}

	// Close the file descriptor and perform cleanup
	close(fileDescriptor);

	return 0;
}



std::vector<uint8_t> buffer(serv._buffSize); // Allocate a vector for a chunk
ssize_t bytes_received = 0;
ssize_t total_bytes_received = 0;
std::vector<uint8_t> request; // This vector will store the accumulated data

while ((bytes_received = recv(clientSocket, buffer.data(), serv._buffSize, 0)) > 0) {
total_bytes_received += bytes_received;
request.insert(request.end(), buffer.begin(), buffer.begin() + bytes_received);
// You can also use request.insert(request.end(), buffer.begin(), buffer.begin() + bytes_received) to append the data.
std::fill(buffer.begin(), buffer.end(), 0); // Clear the buffer
}

// Now, 'request' contains the accumulated data as a vector of uint8_t.

