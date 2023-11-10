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
	//tryfiles
} LocationStruc;

typedef struct ServerConf
{
	ServerConf();
	~ServerConf();
	std::map<std::string, LocationStruc>	locations;//vector before
	// std::map<std::string, std::string>		errorPages;//maybe add some more // change to int, std::string
	short unsigned							port;
	std::string								serverName;
	int										bodySize;
	//??index, root, default_server

	//new
	std::map<int, std::string>		errorPages;//maybe add some more
} ServerConf;

class Server
{
	public:
		Server();
		~Server();
		void	getServerConf(Config conf);

		class WrongPort : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		class WrongAmount : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		class PortAlreadyInUse : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		class WrongCgiExtension : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		int							_workerProcesses;//could be auto;
		int							_workerConnections;
		int							_scriptTimeout;
		int							_clientTimeout;
		int							_buffSize;
		int							_backlog;
		std::vector<ServerConf>		_server;
	private:
		//*******************//
		//*** server.cpp ***//
		//*******************//
		void						_setCgi(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void						_setRewrite(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void						_setAutoIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void						_setRoot(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void						_setIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void						_setAllowMethods(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void						_setLocationServerValues(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf, size_t i);
		void						_setServerValues(std::map<std::string, std::map<std::string, std::vector<std::string> > > server, std::vector<std::string> locations);
		void						_serverValues(Config conf);
		//*******************//
		//*** server2.cpp ***//
		//*******************//
		void						_setErrorPage400(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setErrorPage401(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setErrorPage403(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setErrorPage404(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setErrorPage500(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setErrorPage502(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setErrorPage503(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setErrorPages(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setServerName(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setPort(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setBodySize(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setGlobalServerValues(std::map<std::string, std::vector<std::string> > location, ServerConf &conf);
		void						_setWorkerProcesses(std::map<std::string, std::vector<std::string> > globalContext);
		void						_setWorkerConnections(std::map<std::string, std::vector<std::string> > globalContext);
		void						_setScriptTimeouts(std::map<std::string, std::vector<std::string> > globalContext);
		void						_setClientTimeout(std::map<std::string, std::vector<std::string> > globalContext);		
		void						_setBuffSize(std::map<std::string, std::vector<std::string> > globalContext);
		void						_setBackLog(std::map<std::string, std::vector<std::string> > globalContext);
		void						_globalValues(Config conf);	
		void						_checkDuplicatePorts();
		//*******************//
		//**** variables ****//
		//*******************//
};

#endif
