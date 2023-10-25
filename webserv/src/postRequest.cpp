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
	parseBoundary(getRequestString());
	parseContentLength(getRequestString());
	parseDataType(getRequestString());

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

