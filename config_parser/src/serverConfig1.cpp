
#include "../includes/serverConf.hpp"

LocationStruc::LocationStruc() : allowGet(false), allowPost(false), allowDelete(false), rewrite(""), autoindex(""), root(""), index(""), cgi() {}

LocationStruc::~LocationStruc(){}

serverSettings::serverSettings() : locations(), errorPages(), port(0), serverName("") {}


serverSettings::~serverSettings() {}

void	serverConf::_setCgi(std::map<std::string, std::vector<std::string> > location, std::string locationName,serverSettings &conf) {
	if (location.find("cgi") != location.end() && location["cgi"][0] != "") {
		for (size_t i = 0; i < location["cgi"].size(); i++) {
			if (location["cgi"][i] != ".py" && location["cgi"][i] != ".php") 
				throw WrongCgiExtension();
		}
		conf.locations[locationName].cgi = location["cgi"];
	}
}

void	serverConf::_setRewrite(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverSettings &conf) {
	if (location.find("rewrite") != location.end() && location["rewrite"][0] != "")
			conf.locations[locationName].rewrite = location["rewrite"][0];
}

void	serverConf::_setAllowMethods(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverSettings &conf) {
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

void	serverConf::_setAutoIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverSettings &conf) {
	if (location.find("autoindex") != location.end() && location["autoindex"][0] != "")
		conf.locations[locationName].autoindex = location["autoindex"][0];
}

void	serverConf::_setRoot(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverSettings &conf) {
	if (location.find("root") != location.end() && location["root"][0] != "")
		conf.locations[locationName].root = location["root"][0];
}

void	serverConf::_setIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverSettings &conf) {
	if (location.find("index") != location.end() && location["index"][0] != "")
		conf.locations[locationName].index = location["index"][0];
}

void	serverConf::_setLocationServerValues(std::map<std::string, std::vector<std::string> > location, std::string locationName, serverSettings &conf, size_t i) {
	if (i == 0)
		conf.locations = std::map<std::string, LocationStruc>();
	locationName = locationName.substr(8, locationName.size() - 8);
	conf.locations[locationName] = LocationStruc();
	void (serverConf::*locationFunc[]) (std::map<std::string, std::vector<std::string> > location, std::string locationName, serverSettings &conf)
		= {&serverConf::_setCgi, &serverConf::_setRewrite, &serverConf::_setAutoIndex, &serverConf::_setRoot, &serverConf::_setIndex, &serverConf::_setAllowMethods};
	for (size_t j = 0; j < 6; j++)
		(this->*locationFunc[j])(location, locationName, conf);
}

void	serverConf::_setServerValues(std::map<std::string, std::map<std::string, std::vector<std::string> > > server, std::vector<std::string> locations) {
	serverSettings	conf;
	for (size_t i = 0, j = 0; j < locations.size(); j++) {
		if (locations[j] == "noLocation")
			_setGlobalServerValues(server[locations[j]], conf);
		else
			_setLocationServerValues(server[locations[j]], locations[j], conf, i++);
	}
	_server.push_back(conf);
}

void	serverConf::_serverValues(Config conf) {
	std::vector<std::map<std::string, std::map<std::string, std::vector<std::string> > > >	serverContext = conf.getConfFile();
	std::vector<std::vector<std::string> >	locations = conf.getLocations();
	for (size_t i = 0; i < serverContext.size(); i++)
		_setServerValues(serverContext[i], locations[i]);
}

void	serverConf::_checkDuplicatePorts() {
	for (size_t i = 0; i < _server.size() - 1; i++) {
		for (size_t j = i + 1 ; j < _server.size(); j++) {
			if (_server[i].port == _server[j].port)
				throw PortAlreadyInUse();
		}
	}
}

void	serverConf::getServerConf(Config conf) {
	_globalValues(conf);
	_serverValues(conf);
	_checkDuplicatePorts();
	if (_server.empty())
		throw WrongAmount();
}
