
#include "../includes/response.hpp"

response::response(std::string url){
	this->_response = createResponse(url);
}

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

std::string response::createResponse(std::string url){

	std::string filePath = "./html_files" + url + "/" + getFile("./html_files" + url);
	std::ifstream htmlFile(filePath);

	if (!htmlFile && !cgiCheckConditions(url)) {
		return "HTTP/1.1 404 Not Found\r\n\r\n<h1>404 Not Found</h1>";
	}

		// vv----cgi----vv
	else if (!htmlFile && cgiCheckConditions(url)) {  //std::ifstream("src/tmp_cgi")
		std::ifstream inputFile("src/tmp_cgi.txt");
		if (!inputFile.is_open())
			return "HTTP/1.1 500 Internal Server Error\r\n\r\n<h1>500 Internal Server Error</h1>";
		std::string cgiContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		std::string response = "HTTP/1.1 200 OK\r\n";
		response += "Content-Type: text/html\r\n";
		response += "Content-Length: " + std::to_string(cgiContent.length()) + "\r\n";
		//response += "Set-Cookie: session_token=""; SameSite=None; Secure; HttpOnly\r\n";
		response += "\r\n" + cgiContent;

		remove("src/tmp_cgi.txt");
		inputFile.close();
		return response;
	}
	// ^^----cgi----^^

	std::string htmlContent((std::istreambuf_iterator<char>(htmlFile)), std::istreambuf_iterator<char>());

	// Create an HTTP response with the HTML content
	std::string response = "HTTP/1.1 200 OK\r\n";
	response += "Content-Type: text/html\r\n";
	response += "Content-Length: " + std::to_string(htmlContent.length()) + "\r\n";
	//response += "Set-Cookie: session_token=""; SameSite=None; Secure; HttpOnly\r\n";
	response += "\r\n" + htmlContent;

	return response;
}


//----cgi
bool response::cgiCheckConditions(std::string url) const {

	cgi cgiHandler;

	if (cgiHandler.cgiValidExtension(url)) {
        cgiHandler.executeCgi();
        return true;
    }
	return false;
}
//----cgi

std::string response::getFile(std::string directoryPath){
// Open the directory
	DIR* dir = opendir(directoryPath.c_str());

	if (dir == nullptr) {
		return "";
	}

	// Read the contents of the directory
	struct dirent* entry;
	while ((entry = readdir(dir)) != nullptr) {
		if (entry->d_type == DT_REG && hasHtmlExtension(entry->d_name)) {
			closedir(dir);
			return  entry->d_name;
		}
	}
	closedir(dir);
	return "";
}

std::string response::getResponse(){
	return this->_response;
}

bool hasHtmlExtension(const char* filename) {
	const char* extension = strrchr(filename, '.');
	return (extension != nullptr && strcmp(extension, ".html") == 0);
}