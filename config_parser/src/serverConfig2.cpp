
#include "../includes/serverConf.hpp"

serverConf::serverConf() {}

serverConf::serverConf(Config conf) : _workerProcesses(0), _workerConnections(0), _scriptTimeout(-1), _clientTimeout(-1), _buffSize(0), _backlog(0),
	_server(), _validExtensions(){
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
	if (globalContext.find("backlog") != globalContext.end() && globalContext["backlog"][0] != "")
		_backlog = atoi(globalContext["backlog"][0].c_str());
	if (_backlog < 1)
		throw WrongAmount();
}


//check Timeouts!!!!!
void	serverConf::_setClientTimeout(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("client_timeout") != globalContext.end() && globalContext["client_timeout"][0] != "")
		_clientTimeout = atoi(globalContext["client_timeout"][0].c_str());
	if (_clientTimeout < 0 || _clientTimeout > 10)
		throw WrongAmount();
}

void	serverConf::_setScriptTimeouts(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("script_timeout") != globalContext.end() && globalContext["script_timeout"][0] != "")
		_scriptTimeout = atoi(globalContext["script_timeout"][0].c_str());
	if (_scriptTimeout < 0 || _scriptTimeout > 10)
		throw WrongAmount();
}

void	serverConf::_setWorkerConnections(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("worker_connections") != globalContext.end() && globalContext["worker_connections"][0] != "")
		_workerConnections= atoi(globalContext["worker_connections"][0].c_str());
	if (_workerConnections < 1)
		throw WrongAmount();
}

void	serverConf::_setWorkerProcesses(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("worker_processes") != globalContext.end() && globalContext["worker_processes"][0] != "")
		_workerProcesses = atoi(globalContext["worker_processes"][0].c_str());
	if (_workerProcesses < 1)
		throw WrongAmount();
}

void	serverConf::_globalValues(Config conf) {
	std::map<std::string, std::vector<std::string> > globalContext = conf.getGlobalContext();
	void (serverConf::*globalFunc[]) (std::map<std::string, std::vector<std::string> >)
	= {&serverConf::_setWorkerProcesses, &serverConf::_setWorkerConnections, &serverConf::_setScriptTimeouts, &serverConf::_setClientTimeout, &serverConf::_setBuffSize, &serverConf::_setBackLog};
	for (size_t i = 0; i < 5; i++)
		(this->*globalFunc[i])(globalContext);
}

void	serverConf::_setPort(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("listen") != location.end() && location["listen"][0] != "")
		conf.port = atoi(location["listen"][0].c_str());
	else
		conf.port = 80;
	if ((conf.port < 1023 && conf.port != 80) || conf.port > 65535)
		throw WrongPort();
}

void	serverConf::_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	void (serverConf::*serverFunc[]) (std::map<std::string, std::vector<std::string> > location, serverSettings &conf) = {&serverConf::_setBodySize, &serverConf::_setPort, &serverConf::_setServerName, &serverConf::_setErrorPages};
	for (size_t i = 0; i < 4; i++)
		(this->*serverFunc[i])(location, conf);
}

void	serverConf::_setBuffSize(std::map<std::string, std::vector<std::string> > globalContext) {
	if (globalContext.find("buff_size") != globalContext.end() && globalContext["buff_size"][0] != "")
		_buffSize = atoi(globalContext["buff_size"][0].c_str());
	if (_buffSize < 9000 || _buffSize > 1000000)
		throw WrongAmount();
}

void	serverConf::_setBodySize(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("body_size") != location.end() && location["body_size"][0] != "")
		conf.bodySize = atoi(location["body_size"][0].c_str());
	if (conf.bodySize < 1 || conf.bodySize > 500000000)
		throw WrongAmount();
}

void	serverConf::_setErrorPage400(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page400") != location.end() && location["error_page404"][0] != "")
		conf.errorPages[400] = location["error_page400"][0];
}

void	serverConf::_setErrorPage404(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page404") != location.end() && location["error_page404"][0] != "")
		conf.errorPages[404] = location["error_page404"][0];
}

void	serverConf::_setErrorPage405(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page405") != location.end() && location["error_page405"][0] != "")
		conf.errorPages[405] = location["error_page405"][0];
}

void	serverConf::_setErrorPage408(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page408") != location.end() && location["error_page408"][0] != "")
		conf.errorPages[408] = location["error_page408"][0];
}

void	serverConf::_setErrorPage413(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page413") != location.end() && location["error_page413"][0] != "")
		conf.errorPages[413] = location["error_page413"][0];
}

void	serverConf::_setErrorPage415(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page415") != location.end() && location["error_page415"][0] != "")
		conf.errorPages[415] = location["error_page415"][0];
}

void	serverConf::_setErrorPage500(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page500") != location.end() && location["error_page500"][0] != "")
		conf.errorPages[500] = location["error_page500"][0];
}

void	serverConf::_setErrorPage504(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page504") != location.end() && location["error_page504"][0] != "")
		conf.errorPages[504] = location["error_page504"][0];
}

void	serverConf::_setErrorPage505(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	if (location.find("error_page505") != location.end() && location["error_page505"][0] != "")
		conf.errorPages[505] = location["error_page505"][0];
}

void	serverConf::_setErrorPages(std::map<std::string, std::vector<std::string> > location, serverSettings &conf) {
	void (serverConf::*errorPageFunc[]) (std::map<std::string, std::vector<std::string> > location, serverSettings &conf) = {&serverConf::_setErrorPage400, &serverConf::_setErrorPage404, &serverConf::_setErrorPage405,
		&serverConf::_setErrorPage408, &serverConf::_setErrorPage413, &serverConf::_setErrorPage415, &serverConf::_setErrorPage500, &serverConf::_setErrorPage504, &serverConf::_setErrorPage505};
	for (size_t i = 0; i < 9; i++)
		(this->*errorPageFunc[i])(location, conf);
}

void	serverConf::_setServerName(std::map<std::string, std::vector<std::string> > location,serverSettings &conf) {
	if (location.find("server_name") != location.end() && location["server_name"][0] != "")
		conf.serverName = location["server_name"][0];
}
