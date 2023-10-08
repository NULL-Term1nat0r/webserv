#ifndef SERVER_HPP
# define SERVER_HPP
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include "config.hpp"

typedef struct location
{

	std::string							autoindex;
	std::string							rewrite;
	std::string							root;
	std::string							proxyPass;
//	std::vector<bool>					allowMethods;//true by default
	bool								allowGet;
	bool								allowPost;
	bool								allowDelete;
	std::string							index;
};

typedef struct serverConf
{
	std::vector<std::map<std::string, location> >	locations;
	std::map<std::string, std::string>				errorPages;
	short unsigned									port;
	std::string										serverName;
};

class Server
{
	public:
		Server();
		~Server();
		void	getServerConf(Config conf);
	private:
		bool	_contextExists(std::map<std::string, std::vector<std::string> > location, std::string context);

		void	_setLocationServerValues(std::map<std::string, std::vector<std::string> > location, serverConf &conf);
	
		void	_setErrorPages(std::map<std::string, std::vector<std::string> > location, serverConf &conf);
		void	_setServerName(std::map<std::string, std::vector<std::string> > location, serverConf &conf);
		void	_setPort(std::map<std::string, std::vector<std::string> > location, serverConf &conf);
		
		void	_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, serverConf &conf);
		void	_setServerValues(std::map<std::string, std::map<std::string, std::vector<std::string> > > server, std::vector<std::string> locations, size_t i);
		void						_serverValues(Config conf);
	
	
		void						_setErrorLog(std::map<std::string, std::vector<std::string> > globalContext);
		void						_setAccessLog(std::map<std::string, std::vector<std::string> > globalContext);
		void						_setWorkerProcesses(std::map<std::string, std::vector<std::string> > globalContext);
		void						_globalValues(Config conf);
		std::string					_include;
		std::vector<std::string>	_workerProcesses;
		std::vector<std::string>	_accessLog;
		std::vector<std::string>	_errorLog;
		std::vector<serverConf>		_server;
};

#endif
//loactions will still be usefulll moving on (for URL)