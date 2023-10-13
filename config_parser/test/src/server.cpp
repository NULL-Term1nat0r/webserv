
#include "../inc/server.hpp"

LocationStruc::LocationStruc() : allowGet(false), allowPost(false), allowDelete(false), rewrite(), autoindex(), root(), index(), cgi() {}

LocationStruc::~LocationStruc(){}

ServerConf::ServerConf() : locations(), errorPages(), port(0), serverName() {}

ServerConf::~ServerConf() {}

void	Server::_setCgi(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("cgi") != location.end())
		conf.locations[locationName].cgi = location["cgi"];
}

void	Server::_setRewrite(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("rewrite") != location.end())
			conf.locations[locationName].rewrite = location["rewrite"];
}

void	Server::_setAllowMethods(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("allow_methods") != location.end()) {
		for (size_t j = 0; j < location["allow_methods"].size(); j++) {
			if (location["allow_methods"][j] == "GET")
				conf.locations[locationName].allowGet = true;
			else if (location["allow_methods"][j] == "POST")
				conf.locations[locationName].allowPost = true;
			else if (location["allow_methods"][j] == "DELETE")
				conf.locations[locationName].allowDelete = true;
		}
	}
	else {
		conf.locations[locationName].allowDelete = true;
		conf.locations[locationName].allowGet = true;
		conf.locations[locationName].allowPost = true;
	}
}

void	Server::_setAutoIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("autoindex") != location.end())
		conf.locations[locationName].autoindex = location["autoindex"][0];
}

void	Server::_setRoot(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("root") != location.end())
		conf.locations[locationName].root = location["root"][0];
}

void	Server::_setIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) { // ??????????+/
	if (location.find("index") != location.end())
		conf.locations[locationName].index = location["index"][0];
}

void	Server::_setLocationServerValues(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (i == 0)
		conf.locations = std::map<std::string, LocationStruc>();
	locationName = locationName.substr(8, locationName.size() - 8);
	conf.locations[locationName] = LocationStruc();
	void (Server::*locationFunc[]) (std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i)
		= {&Server::_setCgi, &Server::_setRewrite, &Server::_setAutoIndex, &Server::_setRoot, &Server::_setIndex, &Server::_setAllowMethods};
	for (size_t j = 0; j < 6; j++)
		(this->*locationFunc[j])(location, locationName, conf, i);
}

void	Server::_setServerValues(std::map<std::string, std::map<std::string, std::vector<std::string> > > server, std::vector<std::string> locations) {
	ServerConf	conf;
	for (size_t i = 0, j = 0; j < locations.size(); j++) {
		if (locations[j] == "noLocation")
			_setGlobalServerValues(server[locations[j]], conf);
		else
			_setLocationServerValues(server[locations[j]], locations[j], conf, i++);
	}
	_server.push_back(conf);
}

void	Server::_serverValues(Config conf) {
	std::vector<std::map<std::string, std::map<std::string, std::vector<std::string> > > >	serverContext = conf.getConfFile();
	std::vector<std::vector<std::string> >	locations = conf.getLocations();
	for (size_t i = 0; i < serverContext.size(); i++)
		_setServerValues(serverContext[i], locations[i]);
}

void	Server::_checkDuplicatePorts() {
	for (size_t i = 0; i < _server.size() - 1; i++) {
		for (size_t j = i + 1 ; j < _server.size(); j++) {
			if (_server[i].port == _server[j].port)
				throw PortAlreadyInUse();
		}
	}
}

void	Server::getServerConf(Config conf) {
	_globalValues(conf);
	_serverValues(conf);
	_checkDuplicatePorts();
}
