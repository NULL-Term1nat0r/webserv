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
	std::vector<bool>					allowMethods;//true by default
	std::string							index;
};

typedef struct serverConf
{
	std::vector<std::map<std::string, location> >	locations;
	std::map<std::string, std::string>				errorPages;
	std::string										port;
	std::string										serverName;
};

class Server
{
	public:
		Server();
		~Server();
		void	getServerConf(Config conf);
	private:
		void					_setAccessLog(std::map<std::string, std::vector<std::string> > globalContext);
		void					_globalValues(Config conf);
		std::string				_include;
		std::string				_workerProcesses;
		std::vector<std::string>				_accessLog;
		std::string				_errorLog;
		std::vector<serverConf>	_server;
};

#endif
//loactions will still be usefulll moving on (for URL)