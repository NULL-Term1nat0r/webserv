
#include "../inc/server.hpp"

Server::Server() {}

Server::~Server() {}

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


bool	Server::_serverContextExists(std::map<std::string, std::vector<std::string> > location, std::string context) {
	std::map<std::string, std::vector<std::string> >::iterator it = location.find(context);
	if (it != location.end())
		return true;
	return false;
}

void	Server::_setErrorPages(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {//special case since error_page 400 error_page 500 same key
	//if(_contextExists(location, ""))
}

void	Server::_setServerName(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_serverContextExists(location, "server_name"))
		conf.serverName = location["server_name"][0].substr(0, location["server_name"][0].size());
}

void	Server::_setPort(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	
	//check if port is under 1024 or over max port number
	// std::map<std::string, std::vector<std::string> >
	if (_serverContextExists(location, "listen"))
		conf.port = atoi(location["listen"][0].c_str());
}



//change to function pointer
void	Server::_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	// void (Server::*serverFunc[]) (std::map<std::string, std::vector<std::string> > location, serverConf &conf) {&Server::_setPort, &Server::_setServerName, &Server::_setErrorPages};
	// for (size_t i = 0; i < 3; i++)
	// 	(this->*serverFunc[i])(location, conf);
}



bool	Server::_locationContextExists(std::map<std::string, std::vector<std::string> > location, std::string context)
{
	std::map<std::string, std::vector<std::string> >::iterator it = location.find(context);
	if (it != location.end())
		return true;
	return false;
}

void	Server::_setCgi(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverConf &conf, size_t i) {
	if (_locationContextExists(location, "cgi"))
		conf.locations[i][locationName].cgi = location["cgi"];
}

void	Server::_setRewrite(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverConf &conf, size_t i) {
	if (_locationContextExists(location, "rewrite"))
		conf.locations[i][locationName].rewrite = location["rewrite"];
}

void	Server::_setAllowMethods(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverConf &conf, size_t i) {
	if (_locationContextExists(location, "allow_methods")) {
		conf.locations[i][locationName].allowGet = false;
		conf.locations[i][locationName].allowPost = false;
		conf.locations[i][locationName].allowDelete = false;
		for (size_t i = 0; i < location["allow_methods"].size(); i++) {
			if (location["allow_methods"][i] == "GET")
				conf.locations[i][locationName].allowGet = true;
			else if (location["allow_methods"][i] == "POST")
				conf.locations[i][locationName].allowPost = true;
			else if (location["allow_methods"][i] == "DELETE")
				conf.locations[i][locationName].allowDelete = true;
		}
	}
	else {
		conf.locations[i][locationName].allowDelete = true;
		conf.locations[i][locationName].allowGet = true;
		conf.locations[i][locationName].allowPost = true;
	}
}

void	Server::_setAutoIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverConf &conf, size_t i) {
	if (_locationContextExists(location, "autoindex"))
		conf.locations[i][locationName].index = location["autoindex"][0];
}

void	Server::_setRoot(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverConf &conf, size_t i) {
	if (_locationContextExists(location, "root"))
		conf.locations[i][locationName].index = location["root"][0];
}

void	Server::_setIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverConf &conf, size_t i) {
	if (_locationContextExists(location, "index"))
		conf.locations[i][locationName].index = location["index"][0];
}

void	Server::_setLocationServerValues(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverConf &conf, size_t i) {
	conf.locations[i][locationName] = locationStruc();
	void (Server::*locationFunc[]) (std::map<std::string, std::vector<std::string> > location, std::string locationName, serverConf &conf, size_t i) {&Server::_setCgi, &Server::_setRewrite, &Server::_setAutoIndex, &Server::_setRoot, &Server::_setIndex, &Server::_setAllowMethods};
	for (size_t i = 0; i < 6; i++)
		(this->*locationFunc[i])(location, locationName, conf, i);
}

void	Server::_setServerValues(std::map<std::string, std::map<std::string, std::vector<std::string> > > server, std::vector<std::string> locations, size_t i) {
	serverConf	conf;
	for (size_t i = 0; i < locations.size(); i++) {
		if (locations[i] == "nolocation")
			_setGlobalServerValues(server[locations[i]], conf);
		else
			_setLocationServerValues(server[locations[i]], locations[i], conf, i);
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
