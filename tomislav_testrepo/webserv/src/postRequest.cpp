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
/*	std::cout << "boundary: " << this->_boundary << std::endl;
	std::cout << "contentLength: " << this->_contentLength << std::endl;
	std::cout << "fileName: " << this->_fileName << std::endl;
	std::cout << "fileType: " << this->_fileType << std::endl;
	std::cout << "filePath: " << this->_filePath << std::endl;*/
	std::cout << "allChunksSent: " << this->_allChunksSent << std::endl;
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
	if (!_firstChunkSent) { //first chunk is revieced
		handleFirstChunk(data);
	}
	if (_firstChunkSent && (_contentLength - _dataRecieved) > data.size()) { //chunks after first chunk
		handleMiddleChunk(data);
	}
	if (_firstChunkSent && (_contentLength - _dataRecieved) <= data.size() && !_allChunksSent){ //last chunk recieved
		handleLastChunk(data);
	}
	_firstChunkSent = true;
//	static int i = 0;
//	std::cout << "chunk gets written to file: " << i << std::endl;
//	i++;
	_dataRecieved += data.size();
//	std::cout << "dataRecieved: " << _dataRecieved << " ContentLength: " << _contentLength << std::endl;
}

void postRequest::handleFirstChunk(std::vector<uint8_t> &data){
	if (this->_contentLength <= data.size()){
		//handle end and start boundary
		std::cout << " everything is in one chunk\n";
	}
	else {
		size_t boundaryPos = getRequestString().find(this->_fileType + "\r\n\r\n");
		if (boundaryPos != std::string::npos) {
			boundaryPos += this->_fileType.length() + 4;
		} else {
			std::cout << "boundary not found" << std::endl;
			throw postException();
		}
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
}


void postRequest::handleMiddleChunk(std::vector<uint8_t> &data){
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

void postRequest::handleLastChunk(std::vector<uint8_t> &data){
	this->_allChunksSent = true;
	checkLastChunk(data, this->_boundary);
	std::ofstream file(this->_filePath, std::ios::app | std::ios::binary);
	if (file.is_open()){
		file.write(reinterpret_cast<char *>(&data[0]), data.size());
		file.close();
	}
	else {
		std::cout << "File not open" << std::endl;
		throw postException();
	}
	std::cout << "recieved last chunk in if statement\n";
	std::cout << "boolean allchunksSent = " << this->_allChunksSent << std::endl;
}

std::vector<uint8_t>::iterator postRequest::findEndBoundary(std::vector<uint8_t>& lastChunk, const std::vector<uint8_t>& boundary) {
	for (std::vector<uint8_t>::iterator it = lastChunk.begin(); it != lastChunk.end(); ++it) {
		if (std::equal(boundary.begin(), boundary.end(), it))
			return it;
	}
	return lastChunk.end();
}

void	postRequest::checkLastChunk(std::vector<uint8_t> &lastChunk, std::string startBoundary) {
	std::string endBoundary = "\r\n--" + startBoundary;
	std::vector<uint8_t> boundary = std::vector<uint8_t>(endBoundary.begin(), endBoundary.end());
	std::vector<uint8_t>::iterator boundaryPos = findEndBoundary(lastChunk, boundary);
	if (boundaryPos != lastChunk.end())
		lastChunk.erase(boundaryPos, lastChunk.end());

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

