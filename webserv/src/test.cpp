//#include <unistd.h>
//#include "../includes/Header.h"
//
//int main() {
//	// Path to the PHP interpreter
//	const char* phpInterpreter = "/usr/bin/php";
//
//	// Path to the PHP script you want to execute
//	const char* phpScript = "../html_files/upload/getImages.php";
//
//	// Arguments for execve
//	const char* argv[] = {phpInterpreter, phpScript, NULL};
//
//	// Environment variables (can be nullptr for default environment)
//	const char* envp[] = {NULL};
//
//	// Execute the PHP script using execve
//	if (execve(phpInterpreter, const_cast<char* const*>(argv), const_cast<char* const*>(envp)) == -1) {
//		// Handle error if execve fails
//		perror("execve");
//		return 1;
//	}
//
//	return 0;
//}


#include <unistd.h>
#include "../includes/Header.h"

int main() {
	// Path to the PHP interpreter
	const char* phpInterpreter = "/usr/bin/php";

	// Path to the PHP script you want to execute
	const char* phpScript = "getImages.php";

	// Working directory
	const char* workingDir = "../html_files/upload"; // Change this to the directory path you want to set

	// Set the working directory
	if (chdir(workingDir) != 0) {
		perror("chdir");
		return 1;
	}

	// Arguments for execve
	const char* argv[] = {phpInterpreter, phpScript, NULL};

	// Environment variables (can be nullptr for default environment)
	const char* envp[] = {NULL};

	// Execute the PHP script using execve
	if (execve(phpInterpreter, const_cast<char* const*>(argv), const_cast<char* const*>(envp)) == -1) {
		// Handle error if execve fails
		perror("execve");
		return 1;
	}

	return 0;
}
