#include "../inc/clientRequest.hpp"

clientRequest::clientRequest(std::string protocol)
{
	this->_request = protocol;
	parseProtocol();
}

clientRequest::clientRequest()
{
	this->_URL = false;
	this->_validRequest = false;
	this->_httpProtocol = true;
	this->_stringHttpProtocol = "HTTP/1.1";
	this->_portNumber = 80;
	this->_aliveConnection = false;
	this->_closeConnection = false;
	this->_get = false;
	this->_post = false;
	this->_delete = false;
}

clientRequest::~clientRequest(){
}

void clientRequest::parseProtocol() {
	std::string methodType[3] = {"GET", "POST", "DELETE"};

	std::istringstream iss(_request);
	std::string line;
	std::string value;
	std::getline(iss, line);
	value = parsing::findValue(line, 1);
	//find method
	if (parsing::checkIfFound(methodType, value) == 0)
		parseGetRequest();
	else if (parsing::checkIfFound(methodType, value) == 1)
		parsePostRequest();
	else if (parsing::checkIfFound(methodType, value) == 2)
		parseDeleteRequest();
}

void clientRequest::parseGetRequest(){

	std::istringstream iss(_request);
	std::string line;
	std::string value;
	std::getline(iss, line);
	//find method
	this->_get = true;
	//find protocol
	parseURL(line);
	parseHttpProtocol(line);
	//find address
	std::getline(iss, line);
	parseAddress(line);
	//find connection
	std::getline(iss, line);
	parseConnectionType(line);
	//find referer
	parseReferer();
	//set valid request
	validateRequest();
}

void clientRequest::validateRequest(){
	int valid = 0;
	if (this->_get || this->_post || this->_delete)
		valid++;
	if (this->_URL)
		valid++;
	if (this->_stringHttpProtocol == "HTTP/1.1" || this->_stringHttpProtocol == "HTTP/1.0")
		valid++;
	if (this->_ip != "")
		valid++;
	if (this->_aliveConnection || this->_closeConnection)
		valid++;
	if (this->_referer != "")
		valid++;
	if (valid == 6)
		this->_validRequest = true;
	else
		this->_validRequest = false;
}

void clientRequest::parsePostRequest(){
	this->_post = true;
	std::istringstream iss(_request);
	std::string line;
	std::string value;
	std::getline(iss, line);
	//find method
	//find protocol
	parseURL(line);
	parseHttpProtocol(line);
	//find address
	std::getline(iss, line);
	parseAddress(line);
	//find connection
	std::getline(iss, line);
	parseConnectionType(line);
	//find referer
	parseReferer();
	parseContentLength();
	parseBinaryDataBoundary();// must not be binary in post
	parseBinaryData();
	//set valid request
	validateRequest();

}

void clientRequest::parseDeleteRequest(){
}
void clientRequest::parseURL(std::string line){
	std::string value;
	value = parsing::findValue(line, 2);
	if (value != "")
		this->_URL = true;
	this->_stringURL = value;
}

void clientRequest::parseHttpProtocol(std::string line){
	std::string protocolType[2] = {"HTTP/1.1", "HTTP/1.0"};
	std::string value;
	value = parsing::findValue(line, 3);
	if (parsing::checkIfFound(protocolType, value) == 0)
		this->_stringHttpProtocol = "HTTP/1.1";
	else if (parsing::checkIfFound(protocolType, value) == 1)
		this->_stringHttpProtocol = "HTTP/1.0";
	else if (parsing::checkIfFound(protocolType, value) == -1)
		this->_httpProtocol = false;
}

void clientRequest::parseAddress(std::string line){
	std::string value;
	value = parsing::findValue(line, 2);
	if (value.find(':') != std::string::npos)
	{
		this->_ip = value.substr(0, value.find(':'));
		this->_portNumber = std::stoi(value.substr(value.find(':') + 1));
	}
	else
		this->_ip = value;
}

void clientRequest::parseConnectionType(std::string line){
	std::string connectionType[2] = {"keep-alive", "close"};
	std::string value;
	value = parsing::findValue(line, 2);
	if (parsing::checkIfFound(connectionType, value) == 0)
		this->_aliveConnection = true;
	else if (parsing::checkIfFound(connectionType, value) == 1)
		this->_closeConnection = true;
}

void clientRequest::parseReferer(){
	this->_referer = parsing::getValue(_request, "Referer:", 2);
}

void clientRequest::parseContentLength(){
	std::cout << "conten_length parsing: " << std::stoi(parsing::getValue(_request, "Content-Length:", 2)) << std::endl;
	this->_contentLength = std::stoi(parsing::getValue(_request, "Content-Length:", 2));
}
void clientRequest::parseBinaryDataBoundary(){
	std::string boundary = parsing::getValue(_request, "Content-Type:", 3);
	boundary = boundary.substr(boundary.find('=') + 1);
	boundary.erase(0, boundary.find_first_not_of(" \t\n\r\f\v"));
	this->_binaryDataBoundary = boundary;
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

//std::string input = "[Your Content]";
//
//// Find the position of the first occurrence of the opening delimiter "[".
//size_t start_pos = input.find("[");
//
//// Find the position of the first occurrence of the closing delimiter "]" after the opening delimiter.
//size_t end_pos = input.find("]", start_pos);
//
//if (start_pos != std::string::npos && end_pos != std::string::npos) {
//// Extract the content between the delimiters.
//std::string content = input.substr(start_pos + 1, end_pos - start_pos - 1);
//
//// Print the extracted content.
//std::cout << content << std::endl;


void clientRequest::printRequest(){
	std::cout << "alive connection : " << getAliveConnection() << std::endl;
	std::cout << "close connection : " << getCloseConnection() << std::endl;
	std::cout << "get method : " << getGetMethod() << std::endl;
	std::cout << "post method : " << getPostMethod() << std::endl;
	std::cout << "delete method : " << getDeleteMethod() << std::endl;
	std::cout << "URL : " << getURL() << std::endl;
	std::cout << "valid request : " << getValidRequest() << std::endl;
	std::cout << "referer : " << getReferer() << std::endl;
	std::cout << "port number : " << getPortNumber() << std::endl;
	std::cout << "ip : " << getIp() << std::endl;
	std::cout << "Content-Length: " << getContentLength() << std::endl;
	std::cout << "binaryDataBoundary: " << getBinaryDataBoundary() << std::endl;
}

bool clientRequest::getValidRequest(){
	return this->_validRequest;
}
bool clientRequest::getGetMethod(){
	return this->_get;
}
bool clientRequest::getPostMethod(){
	return this->_post;
}
bool clientRequest::getDeleteMethod(){
	return this->_delete;
}
bool clientRequest::getAliveConnection(){
	return this->_aliveConnection;
}
bool clientRequest::getCloseConnection(){
	return this->_closeConnection;
}
bool clientRequest::getURL(){
	return this->_URL;
}
std::string clientRequest::getReferer(){
	return this->_referer;
}
int clientRequest::getPortNumber(){
	return this->_portNumber;
}
int clientRequest::getContentLength(){
	return this->_contentLength;
}
std::string clientRequest::getIp(){
	return this->_ip;
}
std::string clientRequest::getStringURL() {
	return this->_stringURL;
}
std::string clientRequest::getBinaryDataBoundary(){
	return this->_binaryDataBoundary;
}
std::string clientRequest::getBinaryData() {
	return this->_binaryData;
}



/*int main() {
	std::string input = "This is the first line\nThis is the second line\nThis is the third line";

	// Create an input string stream from the original string
	std::istringstream iss(input);

	// Read the first line into a separate string
	std::string firstLine;
	std::getline(iss, firstLine);

	// Print the first line
	std::cout << "First Line: " << firstLine << std::endl;

	return 0;
}*/


//GET /favicon.ico HTTP/1.1\n
//Host: localhost:8080\n
//Connection: keep-alive\n
//sec-ch-ua: Google Chrome;v="117", Not;A=Brand;v=8, Chromium;v=117\n
//sec-ch-ua-mobile: ?0\n
//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36\n
//sec-ch-ua-platform: macOS\n
//Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8\n
//Sec-Fetch-Site: same-origin\n
//Sec-Fetch-Mode: no-cors\n
//Sec-Fetch-Dest: image\n
//Referer: http:localhost:8080/\n
//Accept-Encoding: gzip, deflate, br\n
//Accept-Language: en-GB,en-US;q=0.9,en;q=0.8\n
