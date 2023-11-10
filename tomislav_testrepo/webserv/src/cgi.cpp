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

#include "../includes/cgi.hpp"

// ERROR MESSAGES TO USE: 403, 404, 500, 501, 504.

cgi::cgi() {}

cgi::~cgi() {}

bool cgi::cgiCheckLanguage() const {

	int result = false;

	if (_fileExtension == ".py")
		result = std::system("python3 --version");
	else if (_fileExtension == ".php")
		result = std::system("php --version");
//	else if (_fileExtension == ".js")
//		return true;

	if (result == 0)
		return true;
	return false;
}

bool cgi::inputCheck() {
	//if (!cgiCheckLanguage())
	//	return false; // error 500
	if (access(_cgiPath.c_str(), F_OK) != 0) {
		std::cerr << "Status 2: Not Found\n" << std::endl;
		return false;
	}
	return true;
}

int cgi::cgiValidExtension(std::string url) {
	std::vector<std::string> allowed_ending;
	allowed_ending.push_back(".py");
	allowed_ending.push_back(".php");
	allowed_ending.push_back(".js");

	size_t pos = url.find("?");
	if (pos != std::string::npos) {
		_cgiPath = "html_files" + url.substr(0, pos);
		_query = "QUERY_STRING=" + url.substr(pos + 1);
	}
	else
	{
		_cgiPath = "html_files" + url;
	}
//	std::cout << "cgiPath in cgiValidExtension: " << _cgiPath << std::endl;
//	std::cout << "query in cgiValidExtension: " << _query << std::endl;
	size_t dot = _cgiPath.find_last_of(".");
	if (dot != std::string::npos) {
		std::string temp = _cgiPath.substr(dot);
		for (size_t i = 0; i < allowed_ending.size(); i++) {
			if (_cgiPath.size() >= allowed_ending[i].size() && temp == allowed_ending[i]) {
				_fileExtension = temp;
				if (!inputCheck()) {
					std::cout << "Status 500: Internal Server Error\n" << std::endl;
					return (0);
				}
				return true;
			}
		}
	}
	std::cerr << "Status 400: Bad Request\n" << std::endl;
	return false;
}

void cgi::handleAlarmSignal(int signal) {
	std::cerr << "ERROR: CGI script execution timed out (504 Gateway Timeout)" << std::endl;
	remove("src/tmp_cgi.txt");
	return ;
}

int cgi::executeCgi() {

	int status;
	std::string exec;

	if (_fileExtension == ".py") {
		exec = "python3";
	} else if (_fileExtension == ".php") {
		exec = "php";
	} else if (_fileExtension == ".js") {
		exec = "node";
	} else {
		std::cerr << "Status 501: Not Implemented\n" << std::endl;
		return (0);
	}
	char *query = (char*)_query.c_str();
	char *cmd = (char*)_cgiPath.c_str();
	char *env[] = {query, 0};
	char *argv[] = {const_cast<char *>(exec.c_str()), cmd, 0};


	signal(SIGALRM, handleAlarmSignal);
	alarm(5);

	FILE *fileDescriptor = fopen("src/tmp_cgi.txt", "w+");

	//if (fileDescriptor < 3)
	if (!fileDescriptor) {
		std::cerr << "Status 500: Internal Server Error\n" << std::endl;
		exit(1);
	}

	int fd = fileno(fileDescriptor);

	if (fd < 3) {
		std::cerr << "Status 500: Internal Server Error\n" << std::endl;
		fclose(fileDescriptor);
		exit(1);
	}

	pid_t childId = fork();
	if (childId == -1) {
		std::cerr << "Status 500: Internal Server Error\n" << std::endl;
		fclose(fileDescriptor);
		return(1);

	} else if (childId == 0) {
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
		std::cerr << "FAILED to execute script" << std::endl;
		exit(1);

	} else {
		waitpid(childId, &status, 0);
		fclose(fileDescriptor);
		alarm(0);	// cancel alarm
 	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM) {
		std::cerr << "Status 504: Gateway Timeout\n" << std::endl;
		remove("src/tmp_cgi.txt");
		return 1;		// error 504
	}
	if (WIFEXITED(status)) {
		int exitStatus = WEXITSTATUS(status);
		if (exitStatus != 0) {
			std::cerr << "Status 500: Internal Server Error\n" << std::endl;
			remove("src/tmp_cgi.txt");
			return 1;		// error 500
		}
	}
	return 0;
}
