
#include "../inc/server.hpp"

Server::Server() {}

Server::~Server() {}

const char	*Server::WrongPort::what() const throw() {
	return "Port is wrong or is already in use.";
}

const char	*Server::WrongAmount::what() const throw() {
	return "Amount for the Context is not enough.";
}

const char	*Server::PortAlreadyInUse::what() const throw() {
	return "The Port is already used.";
}

const char	*Server::WrongCgiExtension::what() const throw() {
	return "The file extension for cgi is not correct or not available for the webserver.";
}

void	Server::_setBackLog(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("backlog") != globalContext.end()) {
		_backlog = atoi(globalContext["backlog"][0].c_str());
		if (_backlog < 0)
			throw WrongAmount();
	}
}

// void	Server::_setBuffSize(std::map<std::string, std::vector<std::string> > globalContext) {
// 	if (globalContext.find("buff_size") != globalContext.end()) {
// 		_buffSize = atoi(globalContext["buff_size"][0].c_str()2);
// 		if (_buffSize < 0)
// 			throw WrongAmount();
// 	}
// }

void	Server::_setClientTimeout(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("client_timeout") != globalContext.end()) {
		_clientTimeout = atoi(globalContext["client_timeout"][0].c_str());
		if (_clientTimeout < 0)
			throw WrongAmount();
	}
}

void	Server::_setScriptTimeouts(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("script_timeout") != globalContext.end()) {
		_scriptTimeout = atoi(globalContext["script_timeout"][0].c_str());
		if (_scriptTimeout < 0)
			throw WrongAmount();
	}
}

void	Server::_setWorkerConnections(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("worker_connections") != globalContext.end()) {
		_workerConnections= atoi(globalContext["worker_connections"][0].c_str());
		if (_workerConnections < 0)
			throw WrongAmount();
	}
}

void	Server::_setWorkerProcesses(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("worker_processes") != globalContext.end()) {
		_workerProcesses = atoi(globalContext["worker_processes"][0].c_str());
		if (_workerProcesses < 0)
			throw WrongAmount();
	}
}

void	Server::_globalValues(Config conf) {
	std::map<std::string, std::vector<std::string> > globalContext = conf.getGlobalContext();
	void (Server::*globalFunc[]) (std::map<std::string, std::vector<std::string> >)
	= {&Server::_setWorkerProcesses, &Server::_setWorkerConnections, &Server::_setScriptTimeouts, &Server::_setClientTimeout, &Server::_setBuffSize, &Server::_setBackLog};
	for (size_t i = 0; i < 5; i++)
		(this->*globalFunc[i])(globalContext);
}

void	Server::_setErrorPages(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	void (Server::*errorPageFunc[]) (std::map<std::string, std::vector<std::string> > location, ServerConf &conf) = {&Server::_setErrorPage400, &Server::_setErrorPage401, &Server::_setErrorPage403, &Server::_setErrorPage404,
		&Server::_setErrorPage500, &Server::_setErrorPage502, &Server::_setErrorPage503};
	for (size_t i = 0; i < 7; i++)//change i value if error pages added
		(this->*errorPageFunc[i])(location, conf);
}

void	Server::_setPort(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("listen") != location.end())
		conf.port = atoi(location["listen"][0].c_str());
	else
		conf.port = 80;
	if ((conf.port < 1023 && conf.port != 80) || conf.port > 65535)
		throw WrongPort();
}

void	Server::_setBodySize(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("body_size") != location.end()) {
		conf.bodySize = atoi(location["body_size"][0].c_str());
		if (conf.bodySize < 0)
			throw WrongAmount();
	}
}

void	Server::_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	void (Server::*serverFunc[]) (std::map<std::string, std::vector<std::string> > location, ServerConf &conf) = {&Server::_setBodySize, &Server::_setPort, &Server::_setServerName, &Server::_setErrorPages};
	for (size_t i = 0; i < 4; i++)
		(this->*serverFunc[i])(location, conf);
}







			//***********//
			//*new stuff*//
			//***********//

//limit buffer size
void	Server::_setBuffSize(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("buff_size") != globalContext.end()) {
		_buffSize = atoi(globalContext["buff_size"][0].c_str());
		if (_buffSize < 9000 || _buffSize > 1000000)
			throw WrongAmount();
	}
}

//200 201 301 // read on at 400
//400 403 404 405 413 500 501 504

void	Server::_setErrorPage400(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_page400") != location.end())
		conf.errorPages[400] = location["error_page400"][0];
}

void	Server::_setErrorPage401(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_page401") != location.end())
		conf.errorPages[401] = location["error_page401"][0];
}

void	Server::_setErrorPage403(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_page403") != location.end())
		conf.errorPages[403] = location["error_page403"][0];
}

void	Server::_setErrorPage404(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_page404") != location.end())
		conf.errorPages[404] = location["error_page404"][0];
}

void	Server::_setErrorPage500(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_page500") != location.end())
		conf.errorPages[500] = location["error_page500"][0];
}

void	Server::_setErrorPage502(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_page502") != location.end())
		conf.errorPages[502] = location["error_page502"][0];
}

void	Server::_setErrorPage503(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_page503") != location.end())
		conf.errorPages[503] = location["error_page503"][0];
}


void	Server::_setServerName(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("server_name") != location.end())
		conf.serverName = location["server_name"][0];
}
