/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolkova <tbolkova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:13:09 by tbolkova          #+#    #+#             */
/*   Updated: 2023/10/28 15:13:09 by tbolkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cgiRequest.hpp"

bool cgiRequest::_errorSignal = false;


cgiRequest::cgiRequest(std::vector<uint8_t> &requestContainer) : request(requestContainer) {
	_cgiPath = "";
	_query = "";
	_errorCode = 200;		// set to 200 for no error. or 201
	_isError = false;
	fileIsReady = false;
	_cgiFilePath = "";
	_alarmSignal = false;
	_fileDescriptor = 0;
	_execPath = "";
	_execExtension = "";
}

cgiRequest::cgiRequest() {}

cgiRequest::~cgiRequest() {}

bool cgiRequest::cgiCheckLanguage() const {

	if (std::system((_execExtension +  " --version").c_str()))
		return true;
	return false;
}

bool cgiRequest::inputCheck() {
	//if (!cgiCheckLanguage())
	//	return false; // error 500
	if (access(_cgiPath.c_str(), F_OK) != 0) {
		std::cerr << "Status 2: Not Found\n" << std::endl;
		return false;
	}
	return true;
}

void cgiRequest::getErrorHtmlContent(int _errorCode) {
	_cgiFilePath = "./html_files/errorPages/error" + std::to_string(_errorCode) + ".html";
	_isError = true;
	}

bool cgiRequest::createTemporaryFile(){
	_fileDescriptor= open(_tempFile.c_str(), O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (_fileDescriptor != -1)
		return true;
	return false;
}

bool cgiRequest::cgiValidExtension(std::string url) {

	size_t pos = url.find("?");
	if (pos != std::string::npos) {
		_cgiPath = "html_files" + url.substr(0, pos);
		_query = "QUERY_STRING=" + url.substr(pos + 1);
	}
	else
		_cgiPath = "html_files" + url;
	std::cout << "cgiPath: " << _cgiPath << std::endl;
	_tempFile = "html_files/tmp_cgi.txt";
	if (_cgiPath.find(".php") != std::string::npos)
		_execExtension = "php";
	if (_cgiPath.find(".py") != std::string::npos)
		_execExtension = "python3";
	_execPath = "/usr/bin/" + _execExtension;
	std::cout << "execPath: " << _execPath << std::endl;
	_skriptName = _cgiPath.substr(_cgiPath.find_last_of("/") + 1);
	_workingDirectory = _cgiPath.substr(0, _cgiPath.find(_skriptName) - 1);
	std::cout << "workingDirectory: " << _workingDirectory << std::endl;
	std::cout << "skirptName: " << _skriptName << std::endl;
	if (!createTemporaryFile()) {
		std::cout << "file didnt got created\n";
		getErrorHtmlContent(500);
		return false;
	}
	return true;
}

void cgiRequest::handleAlarmSignal(int signal) {
	if (signal == SIGALRM)
		cgiRequest::_errorSignal = true;
	std::cerr << "ERROR: CGI script execution timed out (504 Gateway Timeout)" << std::endl;
}

bool cgiRequest::executeCgi() {
	std::cout << "cgi request incoming\n";

	if (!cgiValidExtension(getStringURL()))
		return false;

	int status;
	char *query = (char*)_query.c_str();
	char *cmd = (char*)_cgiPath.c_str();
	char *env[] = {query, NULL};
	char *argv[] = {const_cast<char *>(_execPath.c_str()), const_cast<char *>(_skriptName.c_str()), NULL};

	signal(SIGALRM, handleAlarmSignal);
	//alarm(5);
	// cgi timeout here
	pid_t childId = fork();
	if (childId == -1) {
		std::cout << "chile didnt ot created\n";
		getErrorHtmlContent(500);
		close(_fileDescriptor);
		return 0;
	}
	else if (childId == 0) {
		if (dup2(_fileDescriptor, STDOUT_FILENO) == -1)
			exit(69);		//setting the timeout for the script
		if (chdir(_workingDirectory.c_str()) != 0){
			exit(69);
		}
		execve(_execPath.c_str(), argv, env);
		std::cout << "execve didnt work\n";
		exit(69);
	}
	else {
		std::cout << "waiting for the process to  join\n";
		waitpid(childId, &status, 0);
		std::cout << "process jioined\n";
		close(_fileDescriptor);
		if (_alarmSignal) {
			getErrorHtmlContent(408);
			close(_fileDescriptor);
//			remove(_tempFile.c_str());
			return false;
		}
		if (cgiRequest::_errorSignal) {
			getErrorHtmlContent(504);
			close(_fileDescriptor);
//			remove(_tempFile.c_str());
			return false;
		}
		//alarm(0);
	}

	int exitStatus = WEXITSTATUS(status);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM) || (exitStatus != 0)) {
		getErrorHtmlContent(504);
		close(_fileDescriptor);
//		remove(_tempFile.c_str());
		return false;
	}
	return true;
}

std::string cgiRequest::getFilePath() {
	return _tempFile;
}
