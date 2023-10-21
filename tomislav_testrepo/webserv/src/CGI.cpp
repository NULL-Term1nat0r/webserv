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


int clientRequest::validCgiExtension() {
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


int clientRequest::executeCgi() {
	std::cout << "executeCgi " << std::endl;
	int fd[2];
	int status;

	std::string exec;
	if (_fileExtension == ".py") {
		exec = "python3";
	} else if (_fileExtension == ".php") {
		exec = "php";
	} else if (_fileExtension == ".js") {
		exec = "node";
	} else {
		// Handle unsupported file extension error
		return (0);
	}
	char *query = (char*)_query.c_str();

	char *cmd = (char*)_cgiPath.c_str();
	char *env[] = {query, 0};
	char *argv[] = {const_cast<char *>(exec.c_str()), cmd, nullptr};

	int file = open(TMP_CGI, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);		//creating a file to store the output of the script

	if (pipe(fd) == -1) {
		// Handle pipe creation error
		// close(file);						//closing the file
		return (0);
	}

	pid_t childId = fork();
	if (childId == -1) {
		// Handle fork error
		// close(file);						//closing the file
	}
	else if (childId == 0) {
		close(fd[0]);
		dup2(file, STDOUT_FILENO);		//redirecting the output of the script to the file
		alarm(CGI_TIMEOUT/1000);		//setting the timeout for the script

		if (_fileExtension == ".py")
			execve("/usr/bin/python3", argv, env); //cmd to run python // env = url and 0
		else if (_fileExtension == ".php")
			execve("/usr/bin/php", argv, env); //cmd to run php // env = url and 0
		else
			execve("/usr/bin/node", argv, env); //cmd to run node // env = url and 0

		// If execve fails, handle the error (execve should never return if successful)
		close(file);
		exit(EXIT_FAILURE);
	}
	else {
		close(fd[1]);
		waitpid(childId, &status, 0);
		close(fd[0]);
	}
	close(file);
	if (WIFSIGNALED(status))
	{
		remove(TMP_CGI);
		return GATEWAY_TIMEOUT;		// error 504

		// create a file to store the output of the script
		// read the output of the script
		// send the output of the script to the client
		// delete the file
	}
	return 0;
}

std::string myItoS(int val)
{
	std::stringstream ss;
	ss << val;
	return ss.str();
}

bool	clientRequest::cgiOutput() {
	std::ifstream inputFile(TMP_CGI);
	if (!inputFile.is_open()) {
		// Handle file opening error
	}
	std::string header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
	std::string line;
	std::string	response;

	while(std::getline(inputFile, line))
		response += line + "\n";
	response = header + myItoS(response.size()) + "\r\n\r\n" + response;

	//std::string convert(_input.begin(), _input.end());
//#ifdef LOG
//	Logging::log("send Data:\n" + _cgiPath, 200);
//#endif
//
//	ssize_t check = send(_clientSocket, (response).c_str(), response.size(), MSG_DONTWAIT);
//	if (check <= 0) {
//#ifdef LOG
//		Logging::log("Failed to send Data to Client", 500);
//#endif
//		inputFile.close();
//	}
	remove(TMP_CGI);
	inputFile.close();
	return false;
}