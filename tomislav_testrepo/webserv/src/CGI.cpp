#include "../includes/clientRequest.hpp"

// add cgi timeout
// server object
// right index for server
// path to location
// check for which error occurs if no packet is installed
// think of the usecase for the script



// check if extension is valid


bool clientRequest::cgiIterate(std::string) {
	std::vector<std::string> allowed_ending;
	allowed_ending.push_back(".py");
	allowed_ending.push_back(".js");
	allowed_ending.push_back(".php");

	for (size_t i = 0; i < allowed_ending.size(); i++)
	{
		if (_fileExtension.size() < allowed_ending[i].size())
			continue;
		if (_fileExtension == allowed_ending[i])
			return true;
	}
	return false;
}


// check in request for "isCGI".


bool clientRequest::validCgiExtension() {
	std::vector<std::string> allowed_ending;
	allowed_ending.push_back(".py");
	allowed_ending.push_back(".js");
	allowed_ending.push_back(".php");

	size_t pos = _stringURL.find("?");
	if (pos != std::string::npos) {
		_cgiPath = _stringURL.substr(0, pos);
		_query = _stringURL.substr(pos + 1);
	} else {
		_cgiPath = _stringURL;
	}

	size_t dot = _cgiPath.find_last_of('.');
	if (dot != std::string::npos) {
		std::string temp = _cgiPath.substr(dot);
		for (size_t i = 0; i < allowed_ending.size(); i++) {
			if (_cgiPath.size() >= allowed_ending[i].size() && temp == allowed_ending[i]) {
				_fileExtension = temp;
				executeCgi();
				return true;
			}
		}
	}
	return false; // Return false if the file extension is not allowed or not found.
}

//int cgi::validCgiExtension() {
//	std::vector<std::string> allowed_ending;
//	allowed_ending.push_back(".py");
//	allowed_ending.push_back(".js");
//	allowed_ending.push_back(".php");
//
////	for (size_t i = 0; i < allowed_ending.size(); i++)
////	{
////		if (_fileExtension.size() < allowed_ending[i].size())
////			continue;
////		if (_fileExtension == allowed_ending[i])
////			return true;
////
//	// now we have our valid language packet
//
//	size_t pos = _stringURL.find("?");
//
//	if (pos != std::string::npos)
//	{
//		_cgiPath = _stringURL.substr(0, pos);
//		_query = _stringURL.substr(pos + 1);
//	}
//	else
//		_cgiPath = _stringURL;
//
//	size_t dot = _cgiPath.find_last_of('.');
//
//	if (dot != std::string::npos)
//	{
//		std::string temp = _cgiPath.substr(dot);
//
//		for (size_t i = 0; i < allowed_ending.size(); i++)
//		{
//			if (_cgiPath.size() < allowed_ending[i].size())
//				continue;
//			if (temp == allowed_ending[i])
//			{
//				_fileExtension = temp;
//				executeCgi();
//			}
//		}
//	}
//	return 0; // Return false if the file extension is not allowed or not found.
//}

bool clientRequest::checkLanguage() const {
	if (_fileExtension == ".py")
		return true;
	if (_fileExtension == ".php")
		return true;
	if (_fileExtension == ".js")
		return true;
	return false;
}
int clientRequest::inputCheck() {
	if(!checkLanguage())
		return 1;//INTERNAL_ERROR; // error 500
	_cgiPath = _stringURL + _cgiPath;

	if (_fileExtension != ".py" && _fileExtension != ".js" && _fileExtension != ".php")
		return 1;//METHOD_NOT_ALLOWED; // error 405

	if (access(_cgiPath.c_str(), F_OK) != 0)
		return 1;//NOT_FOUND; // error 404

	if (access(_cgiPath.c_str(), X_OK) != 0)
		return 1;//FORBIDDEN; // error 403
	return 0;
}


// check if the location is able to execute the script
//	e.g. if we get a .js request, but it can only run .php request, it shouldn't execute.

//void cgi::mainCgi(std::string _requestString, Server &serv)
//{
//	validCgiExtension();
//
//
//}

//void	cgi::executeCgi()
//{
//	int fd[2];
//
//	std::string exec;
//
//	if (validCgiExtension() == ".py")
//		exec = "python3";
//	else if (validCgiExtension() == ".php")
//		exec = "php";
//	else if (validCgiExtension() == ".js")
//		exec = "node";
//
//	char *query = (char*)_query.c_str();
//
//	char *env[] = {query, 0};
//	char *cmd = (char*)_cgiPath.c_str(); // everything after the path
//	char *argv[] = {const_cast<char *>(exec.c_str()), cmd, 0};
//
//
//	if (pipe(fd) == -1) {
//		//pipe failed
//	}
//	pid_t	childId;
//	childId = fork();
//	if (childId == -1)
//		//error
//	if (childId == 0) {
//		//close(fd[0]);
//		//if (dup2(fd[1], STDOUT_FILENO) == -1)
//		//	return error;
//
//		if (_fileExtension == ".py")
//			execve(cmd, argv, env); //cmd to run python // env = url and 0
//		else if (_fileExtension == ".php")
//			execve(cmd, argv, env); //cmd to run php // env = url and 0
//		else if (_fileExtension == ".js")
//			execve(cmd, argv, env); //cmd to run node // env = url and 0
//		else
//			return error;
//		close(fd[1]);
//	exit(1);
//	}
//	else {
//		close(fd[1])
//		if (dup2(fd[0], STDIN_FILENO) == -1)
//			//error
//			// close(fd[0]);
//		// if (alarm(scriptTimeout) == 0) { //probably not allowed
//		// 	kill(childPID, SIGTERM);
//		// }
//		waitpid(childId, NULL, 0);
//		close(fd[0]);
//	}
//}


//something wrong here!!
void clientRequest::executeCgi() {
	std::cout << "executeCgi " << std::endl;
	int fd[2];

	std::string exec;
	if (_fileExtension == ".py") {
		exec = "python3";
	} else if (_fileExtension == ".php") {
		exec = "php";
	} else if (_fileExtension == ".js") {
		exec = "node";
	} else {
		// Handle unsupported file extension error
		return;
	}
	char *query = (char*)_query.c_str();

	char *cmd = (char*)_cgiPath.c_str();
	char *env[] = {query, 0};
	char *argv[] = {const_cast<char *>(exec.c_str()), cmd, nullptr};

	if (pipe(fd) == -1) {
		// Handle pipe creation error
		return;
	}

	pid_t childId = fork();
	if (childId == -1) {
		// Handle fork error
	} else if (childId == 0) {
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1) {
			// Handle dup2 error
			return;
		}

		if (_fileExtension == ".py")
			execve("/usr/bin/python3", argv, env); //cmd to run python // env = url and 0
		else if (_fileExtension == ".php")
			execve("/usr/bin/php", argv, env); //cmd to run php // env = url and 0
		else if (_fileExtension == ".js")
			execve("/usr/bin/node", argv, env); //cmd to run node // env = url and 0

		// If execve fails, handle the error (execve should never return if successful)
		perror("execve");
		exit(EXIT_FAILURE);
	} else {
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1) {
			// Handle dup2 error
		}

		waitpid(childId, NULL, 0);
		close(fd[0]);

		// create a file to store the output of the script
		// read the output of the script
		// send the output of the script to the client
		// delete the file

	}
}
