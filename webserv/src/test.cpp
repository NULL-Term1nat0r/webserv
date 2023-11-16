#include <iostream>
#include <unistd.h>

int main() {
	// The path to your C++ executable
	char* path = (char*)"program";

	// Arguments for your executable (program name is the first argument by convention)
	char* args[] = {(char*)"your_executable", nullptr};

	// Environment variables (can be set to nullptr)
	char* env[] = {nullptr};

	// Execute the program
	if (execve(path, args, env) == -1) {
		perror("execve");  // Print an error message if execve fails
		return 1;
	}

	// This part of the code will only be reached if execve fails
	std::cerr << "Error: execve failed." << std::endl;
	return 1;
}

