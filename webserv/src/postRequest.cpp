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
	std::cout << "postRequest constructor called\n";
	this->_binaryData = postRequest;
	this->_firstChunkSent = true;
	std::cout << "string test: " << getRequestString() << std::endl;
	parseBoundary(getRequestString());
	parseContentLength(getRequestString());
	parseDataType(getRequestString());
	parseFileName(getRequestString());
	parseFileType(getRequestString());
	this->_filePath = "../html_files/upload/" + this->_fileName;
	this->_dataRecieved = 0;
}
postRequest::postRequest(){}

postRequest::~postRequest() {}

void postRequest::parseBoundary(std::string &data) {
	this->_boundary = parsing::getValue(data, "boundary:", 1);
}

void postRequest::parseContentLength(std::string &data) {
	this->_contentLength = std::stoi(parsing::getValue(data, "Content-Length:", 2));
}

void postRequest::parseDataType(std::string &data) {
	if (data.find("Content-Type: multipart/form-data") != std::string::npos)
		this->_multiFormData = true;
	else if (data.find("Content-Type: text/plain") != std::string::npos)
		this->_textData = true;
}

void postRequest::parseFileName(std::string &data){
//	std::cout << "printout data: " << data << std::endl;
	std::string line = parsing::getLineOfKey(data, "Content-Disposition:");
	std::cout << "line postReqeust: " << line << std::endl;
	size_t filenamePos = line.find("filename=\"");
	if (filenamePos != std::string::npos) {
		// Move the start position to the beginning of the filename
		filenamePos += 10; // Skip "filename=\""
		size_t filenameEnd = line.find("\"", filenamePos);
		if (filenameEnd != std::string::npos) {
			this->_fileName = line.substr(filenamePos, filenameEnd - filenamePos);
		}
	}
	std::cout << "filename postReqeust: " << this->_fileName << std::endl;
}

void postRequest::parseFileType(std::string &data) {
	std::string value = parsing::getValue(data, "Content-Type:", 2);
	this->_fileType = value;
}

void postRequest::writeBinaryToFile(std::vector<uint8_t> &data){
	if (_firstChunkSent) {

		size_t boundaryPos = getRequestString().find(this->_boundary);
		if (boundaryPos != std::string::npos) {
			boundaryPos += this->_boundary.length();
		} else
			throw postException();
		std::ofstream file(this->_filePath, std::ios::out | std::ios::binary);

		if (file.is_open()) {
			std::vector<uint8_t> binaryData(data.begin() + boundaryPos, data.end());
			file.write(reinterpret_cast<char *>(&binaryData[0]), binaryData.size());
			file.close();
			_dataRecieved += binaryData.size();
			std::cout << "File created with binary data." << std::endl;
		} else
			throw postException();
		_firstChunkSent = false;
	}
	if (!_firstChunkSent) {
		std::ofstream file(this->_filePath, std::ios::app | std::ios::binary);
		file.write(reinterpret_cast<char *>(&data[0]), data.size());
		file.close();
	}
	else
		throw postException();



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

const char	*postRequest::postException::what() const throw() {
	return "postException has accured\n";
}

