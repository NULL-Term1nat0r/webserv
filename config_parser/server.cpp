
#include "server.hpp"

Server::Server() {}

Server::~Server() {}

void	Server::_setAccessLog(std::map<std::string, std::vector<std::string> > globalContext) {
	std::map<std::string, std::vector<std::string>>::iterator it = globalContext.find("access_log");
	if (it != globalContext.end())
		_accessLog = it->second;
}

void	Server::_globalValues(Config conf) {
	//set default values
	std::map<std::string, std::vector<std::string> > globalContext = conf.getGlobalContext();
	//make loop with function pointer
}

void	Server::getServerConf(Config conf) {
	_globalValues(conf);
}