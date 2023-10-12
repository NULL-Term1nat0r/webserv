
#include "../inc/Header.h"
#include "../inc/response.hpp"

// Implement class methods here

response::response()
{
	std::cout << "response default constructor called" << std::endl;
}

//response::response(std::string type)
//{
//	std::cout << "response constructor with type called" << std::endl;
//}

response::response(const response &other)
{
	*this = other;
	std::cout << "response copy constructor called" << std::endl;
}

response::~response()
{
	std::cout << "response destructor called" << std::endl;
}

response &response::operator=(const response &other)
{
	if (this == &other)
		return *this;
	std::cout << "response copy assignment constructor called" << std::endl;
	return *this;
}

std::string response::getResponse(){
	// Read the HTML file
	std::ifstream htmlFile("./html_files/testHtmlFiles/mainPage1.html");
	if (!htmlFile) {
		return "HTTP/1.1 404 Not Found\r\n\r\n<h1>404 Not Found</h1>";
	}

	std::string htmlContent((std::istreambuf_iterator<char>(htmlFile)), std::istreambuf_iterator<char>());

	// Create an HTTP response with the HTML content
	std::string response = "HTTP/1.1 200 OK\r\n";
	response += "Content-Type: text/html\r\n";
	response += "Content-Length: " + std::to_string(htmlContent.length()) + "\r\n";
	response += "\r\n" + htmlContent;

	return response;
}
