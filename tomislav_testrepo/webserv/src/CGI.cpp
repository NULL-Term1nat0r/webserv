#include "../includes/response.hpp"
#include <mongocxx/client.hpp>

// server object
// right index for server
// path to location
// check for which error occurs if no packet is installed
// think of the usecase for the script



// check if extension is valid
bool cgiIterate(std::string) {
	for(size_t i = 0; i < cgi.size; i++)
	{
		if (_fileExtension == cgi[i])
			return true;
	}
	return false;
}


// check in request for "isCGI".

int Response::validCgiExtension() {
	std::vector<std::string> allowed_ending;
	allowed_ending.push_back(".py");

	cgiIterate(_fileExtension);

	if (_info._myHTTPMethod == M_POST)
	{
		std::string	convert(_info._postInfo._input.begin(), _info._postInfo._input.end());
		size_t		body = convert.find("\r\n\r\n");
//		if (convert.compare(body + 4, 9, "textData=") == 0)
//			return handleCookies(convert, body+13), IS_COOKIE;
		_info._cgiInfo._body = convert.substr(body + 4);
	}
	size_t pos = _info._url.find('?');

	if (pos != std::string::npos)
	{
		_info._cgiInfo._cgiPath = _info._url.substr(0, pos);
		_info._cgiInfo._query = _info._url.substr(pos + 1);
	}
	else
		_info._cgiInfo._cgiPath = _info._url;

	size_t dot = _info._cgiInfo._cgiPath.find_last_of('.');

	if (dot != std::string::npos)
	{
		std::string temp = _info._cgiInfo._cgiPath.substr(dot);

		for (size_t i = 0; i < allowed_ending.size(); i++)
		{
			if (_info._cgiInfo._cgiPath.size() < allowed_ending[i].size())
				continue;
			if (temp == allowed_ending[i])
			{
				_info._cgiInfo._fileExtension = temp;
				return callCGI();
			}
		}
	}
	return 0; // Return false if the file extension is not allowed or not found.
}

bool response::checkLanguage() const {
	if (_info._cgiInfo._fileExtension == ".py")
		return true;
	if (_info._cgiInfo._fileExtension == ".php")
		return true;
	return false;
}
int response::inputCheck() {
	if(!checkLanguage())
		return INTERNAL_ERROR;
	_info._cgiInfo._cgiPath = _info._configInfo._rootFolder + info._cgiInfo._cgiPath;

	if (_info._cgiInfo._fileExtension != ".py")
		return METHOD_NOT_ALLOWED;

	if (access(_info._cgiInfo._cgiPath.c_str(), F_OK) != 0)
		return NOT_FOUND;

	if (access(_info._cgiInfo._cgiPath.c_str(), X_OK) != 0)
		return FORBIDDEN;
	return 0;
}


// check if the location is able to execute the script
//	e.g. if we get a .js request, but it can only run .php request, it shouldn't execute.

void mainCgi(std::string _requestString, Server &serv)
{
	validCgiExtension();


}

void	executeCgi()
{
	int fd[2];

	std::string exec;

	if (validCgiExtension() == ".py")
		exec = "python3";
	else if (validCgiExtension() == ".php")
		exec = "php";
	else if (validCgiExtension() == ".js")
		exec = "node";

	char *env[] = {query, 0};
	char *cmd = (char*)_info._cgiInfo._cgiPath.c_str(); // everything after the path
	char *argv[] = {const_cast<char *>(exec.c_str()), cmd, 0};





	if (pipe(fd) == -1) {
		//pipe failed
	}
	pid_t	childId;
	childId = fork();
	if (childId == -1)
		//error
	if (childId == 0) {
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return error;

		if (cgiInfo._fileExtension == ".py")
			execve("/usr/bin/python", cmd & pathToCgi, env var); //cmd to run python // env = url and 0
		else if (cgiInfo._fileExtension == ".php")
			execve("/usr/bin/php", cmd & pathToCgi, env var); //cmd to run php // env = url and 0
		else if (cgiInfo._fileExtension == ".js")
			execve("/usr/bin/js", cmd & pathToCgi, env var); //cmd to run node // env = url and 0
		else
			return error;
		close(fd[1]);
	exit(1);
	}
	else {
		close(fd[1])
		if (dup2(fd[0], STDIN_FILENO) == -1)
			//error
			// close(fd[0]);
		// if (alarm(scriptTimeout) == 0) { //probably not allowed
		// 	kill(childPID, SIGTERM);
		// }
		waitpid(childId, NULL, 0);
	}
}