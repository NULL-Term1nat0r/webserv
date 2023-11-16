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


cgiRequest::cgiRequest(std::vector<uint8_t> &requestContainer) : request(requestContainer) {
	_cgiPath = "";
	_query = "";
	_fileExtension = "";
	_errorCode = 200;		// set to 200 for no error. or 201
	_isError = false;
	fileIsReady = false;
	_cgiFilePath = "";
	_alarmSignal = false;
}

cgiRequest::cgiRequest() {}

cgiRequest::~cgiRequest() {}

bool cgiRequest::cgiCheckLanguage() const {

	int result = false;

	if (_fileExtension == ".py")
		result = std::system("python3 --version");
	else if (_fileExtension == ".php")
		result = std::system("php --version");

	if (result == 0)
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

int cgiRequest::cgiValidExtension(std::string url) {

	_isError = false;
	_alarmSignal = false;

	std::vector<std::string> allowed_ending;
	allowed_ending.push_back(".py");
	allowed_ending.push_back(".php");

	size_t pos = url.find("?");
	if (pos != std::string::npos) {
		_cgiPath = "html_files" + url.substr(0, pos);
		_query = "QUERY_STRING=" + url.substr(pos + 1);
	}
	else
	{
		_cgiPath = "html_files" + url;
	}
	size_t dot = _cgiPath.find_last_of(".");
	if (dot != std::string::npos) {
		std::string temp = _cgiPath.substr(dot);
		for (size_t i = 0; i < allowed_ending.size(); i++) {
			if (_cgiPath.size() >= allowed_ending[i].size() && temp == allowed_ending[i]) {
				_fileExtension = temp;
				if (!inputCheck()) {
					_errorCode = 500;
					getErrorHtmlContent(_errorCode);
					return false;
				}
				return true;
			}
		}
	}
	_errorCode = 400;
	getErrorHtmlContent(_errorCode);
	return false;
}

void cgiRequest::handleAlarmSignal(int signal) {
	std::cerr << "ERROR: CGI script execution timed out (504 Gateway Timeout)" << std::endl;
	remove("src/tmp_cgi.html");
	return ;
}

int cgiRequest::executeCgi() {
	if (_isError)
		return 0;


	if (cgiValidExtension(getStringURL()) == false)
		return 0;
	//_readingStarted = true;
	int status;
	std::string exec;

	if (_fileExtension == ".py") {
		exec = "python3";
	} else if (_fileExtension == ".php") {
		exec = "php";
	} else {
		_errorCode = 501;
		getErrorHtmlContent(_errorCode);
		return 0;
	}
	char *query = (char*)_query.c_str();
	char *cmd = (char*)_cgiPath.c_str();
	char *env[] = {query, 0};
	char *argv[] = {const_cast<char *>(exec.c_str()), cmd, 0};


	signal(SIGALRM, handleAlarmSignal);
	alarm(5);
	// cgi timeout here

	FILE *fileDescriptor = fopen("src/tmp_cgi.html", "w+");

	if (!fileDescriptor) {
		_errorCode = 500;
		getErrorHtmlContent(_errorCode);
		exit(1);
	}

	int fd = fileno(fileDescriptor);

	if (fd < 3) {
		_errorCode = 500;
		getErrorHtmlContent(_errorCode);
		fclose(fileDescriptor);
		exit(1);
	}

	pid_t childId = fork();
	if (childId == -1) {
		_errorCode = 500;
		getErrorHtmlContent(_errorCode);
		fclose(fileDescriptor);
		return 0;

	} else if (childId == 0) {
		//set a boolean flag that reading from the process has started
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit(0);		//setting the timeout for the script
		if (_fileExtension == ".py") {
			execve("/usr/bin/python3", argv, env);
		} else if (_fileExtension == ".php") {
			execve("/usr/bin/php", argv, env);
		} else {
			execve("/usr/bin/node", argv, env);
		}
		fclose(fileDescriptor);
		_errorCode = 500;
		getErrorHtmlContent(_errorCode);
		exit(1);

	} else {
		waitpid(childId, &status, 0);
		fclose(fileDescriptor);
		if (_alarmSignal) {
			_errorCode = 408;
			getErrorHtmlContent(_errorCode);
			remove("src/tmp_cgi.html");
			return 0;
		}
		alarm(0);	// cancel alarm
 	}

	int exitStatus = WEXITSTATUS(status);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM) || (exitStatus != 0)) {
		_errorCode = 504;
		getErrorHtmlContent(_errorCode);
		remove("src/tmp_cgi.html");
		return 0;
	}
	_cgiFilePath = "src/tmp_cgi.html";
	return (1);
}

std::string cgiRequest::getFilePath() {
	return _cgiFilePath;
}
