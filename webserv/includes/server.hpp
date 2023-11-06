#ifndef SERVER_HPP
#define SERVER_HPP

#include "Header.h"
#include "config.hpp"
#include "request.hpp"
#include "postRequest.hpp"
#include "deleteRequest.hpp"
#include "getRequest.hpp"
#include "response.hpp"

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
	std::map<std::string, std::string>		errorPages;//maybe add some more
	short unsigned							port;
	std::string								serverName;
	int										bodySize;
	//??index, root, default_server
} ServerConf;

class Server
{
	public:
		Server();
		Server(Config conf);
		~Server();
		void	getServerConf(Config conf);
		//server3.cpp
		void 				_startServers(std::string pathConfigFile);

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
		int		  					_workerProcesses;//could be auto;
		int							_workerConnections; // maxClients
		int							_scriptTimeout;
		int							_clientTimeout;
		int							_buffSize;
		int							_backlog; //how many cleints at the same time
		std::vector<ServerConf>		_server;
	private:
		//*******************//
		//*** server.cpp ***//
		//*******************//
		void						_setCgi(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf);
		void						_setRewrite(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf);
		void						_setAutoIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf);
		void						_setRoot(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf);
		void						_setIndex(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf);
		void						_setAllowMethods(std::map<std::string, std::vector<std::string> > location, std::string locationName, ServerConf &conf);
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
		//*** server3.cpp ***//
		//*******************//
		struct sockaddr_in*			_configureServerAddress();
		static request*				_returnClassPointer(int clientSocket, std::map<int, request*> &requestClass);
		static void					_changeClassPointer(int clientSocket, std::map<int, request*> &requestClass, request *newClassPointer);
		static int 					_createSocket(int port, Server &serv);
		static void 				_handleNewConnection(int server_socket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts, std::map<int, request *> &requestClass);
		static void 				_handleClientData(Server &serv, struct pollfd &client, std::vector<long long> &socketTimeouts, std::map<int, request *> &requestClass);
		static void 				_addSocket(int socket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts, std::map<int, request *> &requestClass);
		static void 				_removeSocket(int index, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts);
//		void 						_setPollStruct(std::vector<struct pollfd> &poll_fds, int socket);
		static void  				_processPostRequest(Server &serv, int clientSocket, std::map<int, request *> &requestClass, std::vector<uint8_t> &clientRequest);
		int							_serverRoutine(Server &serv, int index);

		//*******************//
		//**** variables ****//
		//*******************//
};

#endif
