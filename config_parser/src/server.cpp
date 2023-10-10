
#include "../inc/server.hpp"

LocationStruc::LocationStruc() : allowGet(false), allowPost(false), allowDelete(false), rewrite(), autoindex(), root(), index(), cgi() {}

LocationStruc::~LocationStruc(){}

ServerConf::ServerConf() : locations(), errorPages(), port(0), serverName() {}

ServerConf::~ServerConf() {}

void	Server::_setCgi(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("cgi") != location.end())
		conf.locations[i][locationName].cgi = location["cgi"];
}

void	Server::_setRewrite(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("rewrite") != location.end())
			conf.locations[i][locationName].rewrite = location["rewrite"];
}

void	Server::_setAllowMethods(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("allow_methods") != location.end()) {
		for (size_t j = 0; j < location["allow_methods"].size(); j++) {
			if (location["allow_methods"][j] == "GET")
				conf.locations[i][locationName].allowGet = true;
			else if (location["allow_methods"][j] == "POST")
				conf.locations[i][locationName].allowPost = true;
			else if (location["allow_methods"][j] == "DELETE")
				conf.locations[i][locationName].allowDelete = true;
		}
	}
	else {
		conf.locations[i][locationName].allowDelete = true;
		conf.locations[i][locationName].allowGet = true;
		conf.locations[i][locationName].allowPost = true;
	}
}

void	Server::_setAutoIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("autoindex") != location.end())
		conf.locations[i][locationName].autoindex = location["autoindex"][0];
}

void	Server::_setRoot(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (location.find("root") != location.end())
		conf.locations[i][locationName].root = location["root"][0];
}

void	Server::_setIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) { // +/
	if (location.find("index") != location.end())
		conf.locations[i][locationName].index = location["index"][0];
}

void	Server::_setLocationServerValues(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i) {
	if (i == 0)
		conf.locations = std::vector<std::map<std::string, LocationStruc> >();
	conf.locations.push_back(std::map<std::string, LocationStruc>());
	conf.locations[i][locationName] = LocationStruc();
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

void	Server::getServerConf(Config conf) {
	_globalValues(conf);
	_serverValues(conf);
}


void	Server::iterate() {
	for (ServerConf& server : _server) {
        if (!server.locations.empty()) {
            std::cout << "ServerName: " << server.serverName << std::endl;
            std::cout << "Port: " << server.port << std::endl;
            std::cout << "Error Pages:" << std::endl;
            for (const auto& errorPage : server.errorPages) {
                std::cout << "  " << errorPage.first << " -> " << errorPage.second << std::endl;
            }
            std::cout << "Locations:" << std::endl;
            for (const auto& locationMap : server.locations) {
                for (const auto& location : locationMap) {
                    std::cout << "  Location: " << location.first << std::endl;
                   	const LocationStruc& locStruct = location.second;
                    std::cout << "    allowGet: " << locStruct.allowGet << std::endl;
                    std::cout << "    allowPost: " << locStruct.allowPost << std::endl;
                    std::cout << "    allowDelete: " << locStruct.allowDelete << std::endl;
                    std::cout << "    autoindex: " << locStruct.autoindex << std::endl;
                    std::cout << "    root: " << locStruct.root << std::endl;
                    std::cout << "    index: " << locStruct.index << std::endl;
                    std::cout << "    Rewrite:" << std::endl;
                    for (const std::string& rewrite : locStruct.rewrite) {
                        std::cout << "      " << rewrite << std::endl;
                    }
                    std::cout << "    CGI:" << std::endl;
                    for (const std::string& cgi : locStruct.cgi) {
                        std::cout << "      " << cgi << std::endl;
                    }
                }
            }
            std::cout << std::endl;
        }
    }
}

