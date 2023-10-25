// boundary string for the start is in the header
//example: Content-Type: multipart/form-data; boundary=---------------------------BOUNDARY_STRING
//start string starts with -- in the body
//end boundary string nearly the same only difference it has -- at the end

//parse file type and file name in binary data
// POST /upload HTTP/1.1
// Host: example.com
// Content-Type: multipart/form-data; boundary=BOUNDARY_STRING

// --BOUNDARY_STRING
// Content-Disposition: form-data; name="file"; filename="example.jpg"
// Content-Type: image/jpeg

// (Binary data of the image goes here...)
// --BOUNDARY_STRING--



#include "../includes/clientRequest.hpp"

clientRequest::clientRequest(std::string protocol)
{
	this->_request = protocol;
	parseProtocol();
}

// first
void parseBinaryDataBoundary(){
	std::string _request;
	std::string _binaryDataBoundary;

	std::string boundary = parsing::getValue(_request, "Content-Type:", 3);
	boundary = boundary.substr(boundary.find('=') + 1);
	boundary.erase(0, boundary.find_first_not_of(" \t\n\r\f\v"));
	_binaryDataBoundary = boundary;
}

//second
void parseBinaryData(){
	std::string _request;
	std::string _binaryDataBoundary;
	// Find the start of the binary data
	size_t first = _request.find(_binaryDataBoundary);
	size_t second = _request.find(_binaryDataBoundary, first + _binaryDataBoundary.length());
	size_t third = _request.find(_binaryDataBoundary + "--", second + _binaryDataBoundary.length());

	if (second != std::string::npos && third != std::string::npos) {
		std::string content = _request.substr(second + _binaryDataBoundary.length(), third - second - _binaryDataBoundary.length());
		std::ofstream outputFile("binary_Data", std::ios::binary | std::ios::trunc);
		if (outputFile.is_open()) {
			outputFile << content;
			outputFile.close();
		}
	}
}
