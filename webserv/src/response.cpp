
#include "../includes/response.hpp"

response::response(std::string filePath){
//	this->serverClass = serverClass;
	this->filePath = filePath;
	this->startPosition = 0;
	this->_dataSend = 0;
	this->firstChunkSent = false;
	this->_allChunkSent = false;
	this->bodySize = countFileSize(this->filePath);
}

response::~response(){}

response &response::operator=(const response &other)
{
	if (this == &other)
		return *this;
	std::cout << "response copy assignment constructor called" << std::endl;
	return *this;
}

const char	*response::responseInvalidFileException::what() const throw() {
	return "Invalid File Exception";
}

std::string response::getChunk(int chunkSize){
	if (!this->firstChunkSent){
		this->firstChunkSent = true;
//		std::cout << "chunk sent \n" << std::endl;
		return (createFirstChunk(chunkSize));
	}
	else{
//		std::cout << "chunk sent \n" << std::endl;
		return (readFileContent(chunkSize));
	}
}

std::string response::createFirstChunk(int chunkSize){
	std::ifstream file(this->filePath.c_str(), std::ios::binary);
	
	if (!file.is_open())
		throw responseInvalidFileException();
	std::string header;
	std::string body;
	std::string responseChunk;
	header += "HTTP/1.1 200 OK\r\n";
	header += "Content-Type: " + parsing::getFileType(this->filePath) + "\r\n";
	header += "Content-Length: " + std::to_string(countFileSize(this->filePath)) + "\r\n";
	header += "\r\n";
	body = readFileContent(chunkSize - header.length());
	_dataSend = body.length();
	this->startPosition = body.length();
	return responseChunk = header + body;
}

std::string response::readFileContent(int chunkSize){
	std::ifstream file(this->filePath.c_str(), std::ios::binary);
	if (!file.is_open()){
		throw responseInvalidFileException();
	}
	file.seekg(this->startPosition);
	this->startPosition += chunkSize;
	char *buffer = new char[chunkSize];
	file.read(buffer, chunkSize);
	std::string result(buffer, file.gcount());
	delete[] buffer;
	file.close();
	_dataSend += result.length();
	if (_dataSend >= bodySize){
//		std::cout << "compare _dataSend: " << _dataSend << " with bodySize: " << bodySize << std::endl;
		_allChunkSent = true;
	}
	return result;
}

long response::countFileSize(std::string filePath){
	std::ifstream file(filePath.c_str(), std::ios::binary);

	if (!file.is_open())
		throw responseInvalidFileException();
	file.seekg(0, std::ios::end);
	long fileSize = file.tellg();
	file.close();

	return fileSize;
}

bool response::removeFile(const char* filepath) {
	if (std::remove(filepath) == 0)
		return false;
	return true;
}
