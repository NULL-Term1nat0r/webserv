#include <iostream>
#include <cstring>
#include <cstdlib>
#include <dirent.h>

int main() {
	std::string test = "world eval points hello world eval points hello web serv is top g hello";
	int first = test.find("hello");
	int second = test.find("hello", first + 5);
	int third = test.find("hello", second + 5);


	std::string test2 = test.substr(second + 5, third - second - 5);
	std::cout << test2 << std::endl;
	return 0;
}

void clientRequest::parseBinaryData(){
	// Find the start of the binary data
	size_t first = _request.find(_binaryDataBoundary);
	size_t second = _request.find(_binaryDataBoundary, first + _binaryDataBoundary.length());
	size_t third = _request.find(_binaryDataBoundary, second + _binaryDataBoundary.length());

	if (second != std::string::npos && third != std::string::npos) {
		std::string content = _request.substr(second + _binaryDataBoundary.length(), third - second - _binaryDataBoundary.length());
		std::ofstream outputFile("binary_Data", std::ios::binary | std::ios::trunc);
		if (outputFile.is_open()) {
			outputFile << content;
			outputFile.close();
		}
	}
}
