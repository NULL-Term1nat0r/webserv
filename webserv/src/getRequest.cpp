/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getRequest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:17:17 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/24 14:17:17 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/getRequest.hpp"

getRequest::getRequest(std::vector<uint8_t> &getRequest) : request(getRequest){
	std::cout << "ResponseUrl: " << getStringURL() << std::endl;
	this->filePath = createFilePath();
}
getRequest::getRequest(){}

getRequest::~getRequest() {}

const char	*getRequest::getRequestInvalidFileException::what() const throw() {
	return "Invalid File Exception";
}

std::string getRequest::createFilePath(){
	if (getStringURL() == "/"){				//if url is "/" return index.html
		return "./html_files/index.html";
	}
	else if (fileExists(("./html_files" + getStringURL()).c_str())){
		return "./html_files" + getStringURL();
	}
	else if (fileExists(("./html_files" + getStringURL() +  getStringURL() + ".html").c_str())){ // if url is a directory return file.html
		return "./html_files" + getStringURL() + getStringURL() +  ".html";
	}
	else{
		return getErrorPagePath(404); // if url is not found return 404 error page
	}
}

bool getRequest::fileExists(const char* filePath) {
	struct stat fileStat;

	std::cout << "filePath existing check: " << filePath << std::endl;

	if (stat(filePath, &fileStat) == 0) {
		return S_ISREG(fileStat.st_mode) != 0;
	}
	return false;
}

std::string getRequest::getErrorPagePath(int errorCode){
	std::string errorFilePath;
	switch (errorCode) {
		case 404:
			errorFilePath = "./html_files/errorPages/error404.html";
			break;
		case 403:
			errorFilePath = "./html_files/errorPages/error404.html";
			break;
		case 405:
			errorFilePath = "./html_files/errorPages/error404.html";;
			break;
		default:
			errorFilePath = "./html_files/errorPages/error404.html";
	}
	return errorFilePath;
}

std::string getRequest::getFilePath(){
	return this->filePath;
}
