
#include "../inc/server.hpp"

Server::Server() {}

Server::~Server() {}

const char	*Server::WrongPort::what() const throw() {
	return "Port is wrong or is already in use.";
}

void	Server::_setErrorLog(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("error_log") != globalContext.end())
		_errorLog = globalContext["error_log"];
}

void	Server::_setAccessLog(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("access_log") != globalContext.end())
		_accessLog = globalContext["access_log"];
}

void	Server::_setWorkerProcesses(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("worker_processes") != globalContext.end())
		_workerProcesses = globalContext["worker_processes"];
}

void	Server::_globalValues(Config conf) {
	std::map<std::string, std::vector<std::string> > globalContext = conf.getGlobalContext();
	void (Server::*globalFunc[]) (std::map<std::string, std::vector<std::string> >) = {&Server::_setErrorLog, &Server::_setAccessLog, &Server::_setWorkerProcesses};
	for (size_t i = 0; i < 3; i++)
		(this->*globalFunc[i])(globalContext);
}

void	Server::_setErrorPage400(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_pages400") != location.end())
		conf.errorPages["error_page400"] = location["error_page400"][0].substr(0, location["error_page400"][0].size());
}

void	Server::_setErrorPage401(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_pages401") != location.end())
		conf.errorPages["error_page401"] = location["error_page401"][0].substr(0, location["error_page401"][0].size());
}

void	Server::_setErrorPage403(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_pages403") != location.end())
		conf.errorPages["error_page403"] = location["error_page403"][0].substr(0, location["error_page403"][0].size());
}

void	Server::_setErrorPage404(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_pages404") != location.end())
			conf.errorPages["error_page404"] = location["error_page404"][0].substr(0, location["error_page404"][0].size());
}

void	Server::_setErrorPage500(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_pages500") != location.end())
			conf.errorPages["error_page500"] = location["error_page500"][0].substr(0, location["error_page500"][0].size());
}

void	Server::_setErrorPage502(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_pages502") != location.end())
		conf.errorPages["error_page502"] = location["error_page502"][0].substr(0, location["error_page502"][0].size());
}

void	Server::_setErrorPage503(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("error_pages503") != location.end())
		conf.errorPages["error_page503"] = location["error_page503"][0].substr(0, location["error_page503"][0].size());
}

void	Server::_setErrorPages(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	void (Server::*errorPageFunc[]) (std::map<std::string, std::vector<std::string> > location, ServerConf &conf) = {&Server::_setErrorPage400, &Server::_setErrorPage401, &Server::_setErrorPage403, &Server::_setErrorPage404,
		&Server::_setErrorPage500, &Server::_setErrorPage502, &Server::_setErrorPage503};
	for (size_t i = 0; i < 7; i++)
		(this->*errorPageFunc[i])(location, conf);
}

void	Server::_setServerName(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("server_name") != location.end())
		conf.serverName = location["server_name"][0].substr(0, location["server_name"][0].size());
}

void	Server::_setPort(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	if (location.find("listen") != location.end())
		conf.port = atoi(location["listen"][0].c_str());
	else
		conf.port = 80;
	if ((conf.port < 1023 && conf.port != 80) || conf.port > 65535)
		throw WrongPort();
}

void	Server::_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, ServerConf &conf) {
	void (Server::*serverFunc[]) (std::map<std::string, std::vector<std::string> > location, ServerConf &conf) = {&Server::_setPort, &Server::_setServerName, &Server::_setErrorPages};
	for (size_t i = 0; i < 3; i++)
		(this->*serverFunc[i])(location, conf);
}
