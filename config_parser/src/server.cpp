
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




void	Server::_setErrorPage400(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_serverContextExists(location, "error_pages400"))
		conf.errorPages["error_page400"] = location["error_page400"][0].substr(0, location["error_page400"][0].size());
}

void	Server::_setErrorPage401(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_serverContextExists(location, "error_pages401"))
		conf.errorPages["error_page401"] = location["error_page401"][0].substr(0, location["error_page401"][0].size());
}

void	Server::_setErrorPage403(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_serverContextExists(location, "error_pages403"))
		conf.errorPages["error_page403"] = location["error_page403"][0].substr(0, location["error_page403"][0].size());
}

void	Server::_setErrorPage404(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_serverContextExists(location, "error_pages404"))
			conf.errorPages["error_page404"] = location["error_page404"][0].substr(0, location["error_page404"][0].size());
}

void	Server::_setErrorPage500(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_serverContextExists(location, "error_pages500"))
			conf.errorPages["error_page500"] = location["error_page500"][0].substr(0, location["error_page500"][0].size());
}

void	Server::_setErrorPage502(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_serverContextExists(location, "error_pages502"))
		conf.errorPages["error_page502"] = location["error_page502"][0].substr(0, location["error_page502"][0].size());
}

void	Server::_setErrorPage503(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	if(_serverContextExists(location, "error_pages503"))
		conf.errorPages["error_page503"] = location["error_page503"][0].substr(0, location["error_page503"][0].size());
}

void	Server::_setErrorPages(std::map<std::string, std::vector<std::string> > location, serverConf &conf) {
	void (Server::*errorPageFunc[]) (std::map<std::string, std::vector<std::string> > location, serverConf &conf) {&Server::_setErrorPage400, &Server::_setErrorPage401, &Server::_setErrorPage403, &Server::_setErrorPage404,
		&Server::_setErrorPage500, &Server::_setErrorPage502, &Server::_setErrorPage503};
	for (size_t i = 0; i < 7; i++)
		(this->*errorPageFunc[i])(location, conf);
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
	void (Server::*serverFunc[]) (std::map<std::string, std::vector<std::string> > location, serverConf &conf) {&Server::_setPort, &Server::_setServerName, &Server::_setErrorPages};
	for (size_t i = 0; i < 3; i++)
		(this->*serverFunc[i])(location, conf);
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


// void	Server::iterate() {
// 	for (serverConf& server : _server) {
//         if (!server.locations.empty()) {
//             std::cout << "ServerName: " << server.serverName << std::endl;
//             std::cout << "Port: " << server.port << std::endl;
//             std::cout << "Error Pages:" << std::endl;
//             for (const auto& errorPage : server.errorPages) {
//                 std::cout << "  " << errorPage.first << " -> " << errorPage.second << std::endl;
//             }
//             std::cout << "Locations:" << std::endl;
//             for (const auto& locationMap : server.locations) {
//                 for (const auto& location : locationMap) {
//                     std::cout << "  Location: " << location.first << std::endl;
//                     LocationStruc& locStruct = location.second;
//                     std::cout << "    allowGet: " << locStruct.allowGet << std::endl;
//                     std::cout << "    allowPost: " << locStruct.allowPost << std::endl;
//                     std::cout << "    allowDelete: " << locStruct.allowDelete << std::endl;
//                     std::cout << "    autoindex: " << locStruct.autoindex << std::endl;
//                     std::cout << "    root: " << locStruct.root << std::endl;
//                     std::cout << "    index: " << locStruct.index << std::endl;
//                     std::cout << "    Rewrite:" << std::endl;
//                     for (const std::string& rewrite : locStruct.rewrite) {
//                         std::cout << "      " << rewrite << std::endl;
//                     }
//                     std::cout << "    CGI:" << std::endl;
//                     for (const std::string& cgi : locStruct.cgi) {
//                         std::cout << "      " << cgi << std::endl;
//                     }
//                 }
//             }
//             std::cout << std::endl;
//         }
//     }
// }


typedef struct locationStruc
{
	bool						allowGet;
	bool						allowPost;
	bool						allowDelete;
	std::vector<std::string>	rewrite;// look how to really parse it
	std::string					autoindex;
	std::string					root;
	std::string					index;
	std::vector<std::string>	cgi;

	//client_max_body_size; wie wird der Wert geparsed
	//tryfiles
};

typedef struct serverConf
{
	std::vector<std::map<std::string, locationStruc> >	locations;
	std::map<std::string, std::string>				errorPages;
	short unsigned									port;
	std::string										serverName;
};


std::vector<serverConf>		_server;