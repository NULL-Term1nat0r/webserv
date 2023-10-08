
#include "server.hpp"

Server::Server() {}

Server::~Server() {}

bool	Server::_contextExists(std::map<std::string, std::vector<std::string> > location, std::string context) {
	std::map<std::string, std::vector<std::string> >::iterator it = location.find(context);
	if (it != location.end())
		return true;
	return false;
}

void	Server::_setErrorLog(std::map<std::string, std::vector<std::string> > globalContext) {
	std::map<std::string, std::vector<std::string>>::iterator it = globalContext.find("error_log");
	if (it != globalContext.end())
		_errorLog = it->second;
}

void	Server::_setAccessLog(std::map<std::string, std::vector<std::string> > globalContext) {
	std::map<std::string, std::vector<std::string>>::iterator it = globalContext.find("access_log");
	if (it != globalContext.end())
		_accessLog = it->second;
}

void	Server::_setWorkerProcesses(std::map<std::string, std::vector<std::string> > globalContext) {
	std::map<std::string, std::vector<std::string>>::iterator it = globalContext.find("worker_processes");
	if (it != globalContext.end())
		_workerProcesses = it->second;
}

void	Server::_globalValues(Config conf) {
	std::map<std::string, std::vector<std::string> > globalContext = conf.getGlobalContext();
	void (Server::*globalFunc[]) (std::map<std::string, std::vector<std::string> >) {&Server::_setErrorLog, &Server::_setAccessLog, &Server::_setWorkerProcesses};
	for (size_t i = 0; i < 3; i++)
		(this->*globalFunc[i])(globalContext);
}


void	Server::_setErrorPages(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {//special case since error_page 400 error_page 500 same key
	//if(_contextExists(location, ""))
}

void	Server::_setServerName(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_contextExists(location, "server_name"))
		conf.serverName = location["server_name"][0].substr(0, location["server_name"][0].size());
}

void	Server::_setPort(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	
	//check if port is under 1024 or over max port number
	// std::map<std::string, std::vector<std::string> >
	if (_contextExists(location, "listen"))
		conf.port = atoi(location["listen"][0].c_str());
}




void	Server::_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	_setPort(location, conf);
	_setServerName(location, conf);
	_setErrorPages(location, conf);
}

void	Server::_setLocationServerValues(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {

}

void	Server::_setServerValues(std::map<std::string, std::map<std::string, std::vector<std::string> > > server, std::vector<std::string> locations, size_t i) {
	serverConf	conf;
	for (size_t i = 0; i < locations.size(); i++) {
		if (locations[i] == "nolocation")
			_setGlobalServerValues(server[locations[i]], conf);
		else
			_setLocationServerValues(server[locations[i]], conf);
	}

	_server.push_back(conf);
}

void	Server::_serverValues(Config conf) {
	std::vector<std::map<std::string, std::map<std::string, std::vector<std::string> > > >	serverContext = conf.getConfFile();
	std::vector<std::vector<std::string> >	locations = conf.getLocations();//carefull with index
	for (size_t i = 0; i < serverContext.size(); i)
		_setServerValues(serverContext[i], locations[i], i);
}

void	Server::getServerConf(Config conf) {
	_globalValues(conf);
	_serverValues(conf);
}
