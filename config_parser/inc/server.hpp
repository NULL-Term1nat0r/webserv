#ifndef SERVER_HPP
# define SERVER_HPP
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include "../inc/config.hpp"

typedef struct LocationStruc
{
	LocationStruc();
	~LocationStruc();
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
} LocationStruc;

typedef struct ServerConf
{
	ServerConf();
	~ServerConf();
	std::vector<std::map<std::string, LocationStruc> >	locations;
	std::map<std::string, std::string>				errorPages;
	short unsigned									port;
	std::string										serverName;
} ServerConf;

class Server
{
	public:
		Server();
		~Server();
		void	getServerConf(Config conf);
		void	 iterate();
		class WrongPort : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
	private:
		//*******************//
		//*** server.cpp ***//
		//*******************//
		void	_setClientMaxBodySize(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		
		void	_setCgi(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void	_setRewrite(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void	_setAutoIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void	_setRoot(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void	_setIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void	_setAllowMethods(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void	_setLocationServerValues(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void	_setServerValues(std::map<std::string, std::map<std::string, std::vector<std::string> > > server, std::vector<std::string> locations);
		void	_serverValues(Config conf);
		//*******************//
		//*** server2.cpp ***//
		//*******************//
		void	_setErrorPage400(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setErrorPage401(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setErrorPage403(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setErrorPage404(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setErrorPage500(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setErrorPage502(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setErrorPage503(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setErrorPages(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setServerName(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setPort(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void	_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setErrorLog(std::map<std::string, std::vector<std::string> > globalContext);
		void						_setAccessLog(std::map<std::string, std::vector<std::string> > globalContext);
		void						_setWorkerProcesses(std::map<std::string, std::vector<std::string> > globalContext);
		void						_globalValues(Config conf);
		std::string					_include;




	
	
		std::vector<std::string>	_workerProcesses;
		std::vector<std::string>	_accessLog;
		std::vector<std::string>	_errorLog;
		std::vector<ServerConf>		_server;
};

#endif
//loactions will still be usefulll moving on (for URL)