/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:17:08 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/24 19:16:35 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/postRequest.hpp"

postRequest::postRequest(std::vector<uint8_t> &postRequest) : request(postRequest){
	this->_fileName = parsing::returnValue("filename=\"", getRequestString(), "\"\r\n");
	parseDataType(getRequestString());
	parseFileType(getRequestString());
	this->_binaryData = postRequest;
	this->_firstChunkSent = false;
	this->_allChunksSent = false;
	this->_boundary = parsing::returnValue("boundary=", getRequestString(), "\r");
	this->_contentLength = std::stoi(parsing::returnValue("Content-Length: ", getRequestString(), "\r"));
	this->_filePath = "./html_files/upload/" + this->_fileName;
	this->_dataRecieved = 0;
}
postRequest::postRequest(){}

postRequest::~postRequest() {}

void postRequest::printPostRequest() {
	std::cout << "boundary: " << this->_boundary << std::endl;
	std::cout << "contentLength: " << this->_contentLength << std::endl;
	std::cout << "fileName: " << this->_fileName << std::endl;
	std::cout << "fileType: " << this->_fileType << std::endl;
	std::cout << "filePath: " << this->_filePath << std::endl;
	std::cout << "dataRecieved: " << this->_dataRecieved << std::endl;
}

void postRequest::parseDataType(std::string &data) {
	if (data.find("Content-Type: multipart/form-data") != std::string::npos)
		this->_multiFormData = true;
	else if (data.find("Content-Type: text/plain") != std::string::npos)
		this->_textData = true;
}

void postRequest::parseFileType(std::string &data) {
	size_t start = data.find("Content-Type: ");
	start = data.find("Content-Type: ", start + 1);
	size_t end = data.find("\r", start + 14);
	this->_fileType = data.substr(start + 14, end - start - 14);
}

void postRequest::writeBinaryToFile(std::vector<uint8_t> &data){
	if (!_firstChunkSent) {
		size_t boundaryPos = getRequestString().find(this->_boundary);
		if (boundaryPos != std::string::npos) {
			boundaryPos += this->_boundary.length();
		} else {
			std::cout << "boundary not found" << std::endl;
			throw postException();
		}
//		std::ofstream file(this->_filePath, std::ios::out | std::ios::binary);
		std::ofstream file(this->_filePath, std::ios::out | std::ios::binary);

		if (file.is_open()) {
			std::vector<uint8_t> binaryData(data.begin() + boundaryPos, data.end());
			file.write(reinterpret_cast<char *>(&binaryData[0]), binaryData.size());
			file.close();
			std::cout << "File created with binary data." << std::endl;
		} else {
			std::cout << "Failed to create file with binary data." << std::endl;
			throw postException();
		}
	}
	if (_firstChunkSent) {
		std::ofstream file(this->_filePath, std::ios::app | std::ios::binary);
		if (file.is_open()){
			file.write(reinterpret_cast<char *>(&data[0]), data.size());
			file.close();
		}
		else {
			std::cout << "File not open" << std::endl;
			throw postException();
		}
	}
	_firstChunkSent = true;
	static int i = 0;
	std::cout << "chunk gets written to file: " << i << std::endl;
	i++;
	_dataRecieved += data.size();
	std::cout << "dataRecieved: " << _dataRecieved << " ContentLength: " << _contentLength << std::endl;
	if (_dataRecieved >= _contentLength){
		std::cout << "all chunks sent" << std::endl;
		_allChunksSent = true;
	}
}

std::string postRequest::getBoundary() {
	return this->_boundary;
}

int postRequest::getContentLength() {
	return this->_contentLength;
}

bool postRequest::getMultiFormData() {
	return this->_multiFormData;
}

bool postRequest::getTextData() {
	return this->_textData;
}

bool postRequest::getAllChunksSent() {
	return this->_allChunksSent;
}

const char	*postRequest::postException::what() const throw() {
	return "postException has accured\n";
}

