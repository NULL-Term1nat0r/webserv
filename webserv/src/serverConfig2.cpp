
#include "../includes/serverConf.hpp"

serverConf::serverConf() {}

serverConf::serverConf(Config conf){
	getServerConf(conf);
}

serverConf::~serverConf() {}

const char	*serverConf::WrongPort::what() const throw() {
	return "Port is wrong or is already in use.";
}

const char	*serverConf::WrongAmount::what() const throw() {
	return "Amount for the Context is not enough.";
}

const char	*serverConf::PortAlreadyInUse::what() const throw() {
	return "The Port is already used.";
}
const char	*serverConf::WrongCgiExtension::what() const throw() {
	return "The file extension for cgi is not correct or not available for the webserver.";
}

void	serverConf::_setBackLog(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("backlog") != globalContext.end()) {
		_backlog = atoi(globalContext["backlog"][0].c_str());
		if (_backlog < 0)
			throw WrongAmount();
	}
}

void	serverConf::_setBuffSize(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("buff_size") != globalContext.end()) {
		_buffSize = atoi(globalContext["buff_size"][0].c_str());
		if (_buffSize < 0)
			throw WrongAmount();
	}
}

void	serverConf::_setClientTimeout(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("client_timeout") != globalContext.end()) {
		_clientTimeout = atoi(globalContext["client_timeout"][0].c_str());
		if (_clientTimeout < 0)
			throw WrongAmount();
	}
}

void	serverConf::_setScriptTimeouts(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("script_timeout") != globalContext.end()) {
		_scriptTimeout = atoi(globalContext["script_timeout"][0].c_str());
		if (_scriptTimeout < 0)
			throw WrongAmount();
	}
}

void	serverConf::_setWorkerConnections(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("worker_connections") != globalContext.end()) {
		_workerConnections= atoi(globalContext["worker_connections"][0].c_str());
		if (_workerConnections < 0)
			throw WrongAmount();
	}
}

void	serverConf::_setWorkerProcesses(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("worker_processes") != globalContext.end()) {
		_workerProcesses = atoi(globalContext["worker_processes"][0].c_str());
		if (_workerProcesses < 0)
			throw WrongAmount();
	}
}

void	serverConf::_globalValues(Config conf) {
	std::map<std::string, std::vector<std::string> > globalContext = conf.getGlobalContext();
	void (serverConf::*globalFunc[]) (std::map<std::string, std::vector<std::string> >)
	= {&serverConf::_setWorkerProcesses, &serverConf::_setWorkerConnections, &serverConf::_setScriptTimeouts, &serverConf::_setClientTimeout, &serverConf::_setBuffSize, &serverConf::_setBackLog};
	for (size_t i = 0; i < 5; i++)
		(this->*globalFunc[i])(globalContext);
}

void	serverConf::_setErrorPage400(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_pages400") != location.end())
		conf.errorPages["error_page400"] = location["error_page400"][0].substr(0, location["error_page400"][0].size());
}

void	serverConf::_setErrorPage401(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_pages401") != location.end())
		conf.errorPages["error_page401"] = location["error_page401"][0].substr(0, location["error_page401"][0].size());
}

void	serverConf::_setErrorPage403(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_pages403") != location.end())
		conf.errorPages["error_page403"] = location["error_page403"][0].substr(0, location["error_page403"][0].size());
}

void	serverConf::_setErrorPage404(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_pages404") != location.end())
			conf.errorPages["error_page404"] = location["error_page404"][0].substr(0, location["error_page404"][0].size());
}

void	serverConf::_setErrorPage500(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_pages500") != location.end())
			conf.errorPages["error_page500"] = location["error_page500"][0].substr(0, location["error_page500"][0].size());
}

void	serverConf::_setErrorPage502(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_pages502") != location.end())
		conf.errorPages["error_page502"] = location["error_page502"][0].substr(0, location["error_page502"][0].size());
}

void	serverConf::_setErrorPage503(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_pages503") != location.end())
		conf.errorPages["error_page503"] = location["error_page503"][0].substr(0, location["error_page503"][0].size());
}

void	serverConf::_setErrorPages(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	void (serverConf::*errorPageFunc[]) (std::map<std::string, std::vector<std::string> > location, serverSettings &conf) = {&serverConf::_setErrorPage400, &serverConf::_setErrorPage401, &serverConf::_setErrorPage403, &serverConf::_setErrorPage404,
		&serverConf::_setErrorPage500, &serverConf::_setErrorPage502, &serverConf::_setErrorPage503};
	for (size_t i = 0; i < 7; i++)//change i value if error pages added
		(this->*errorPageFunc[i])(location, conf);
}

void	serverConf::_setServerName(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("server_name") != location.end())
		conf.serverName = location["server_name"][0].substr(0, location["server_name"][0].size());
}

void	serverConf::_setPort(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("listen") != location.end())
		conf.port = atoi(location["listen"][0].c_str());
	else
		conf.port = 80;
	if ((conf.port < 1023 && conf.port != 80) || conf.port > 65535)
		throw WrongPort();
}

void	serverConf::_setBodySize(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("body_size") != location.end()) {
		conf.bodySize = atoi(location["body_size"][0].c_str());
		if (conf.bodySize < 0)
			throw WrongAmount();
	}
}

void	serverConf::_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	void (serverConf::*serverFunc[]) (std::map<std::string, std::vector<std::string> > location, serverSettings &conf) = {&serverConf::_setBodySize, &serverConf::_setPort, &serverConf::_setServerName, &serverConf::_setErrorPages};
	for (size_t i = 0; i < 4; i++)
		(this->*serverFunc[i])(location, conf);
}
