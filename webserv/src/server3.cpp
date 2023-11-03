#include <netdb.h>
#include "../includes/server.hpp"

void 	Server::_startServers(std::string pathConfigFile){
	Config conf((char *)pathConfigFile.c_str());
	Server serv(conf);

	for (size_t i = 0; i < serv._server.size(); i++)
	{
		std::cout << "index: " << i << std::endl;
		_serverRoutine(serv, i);
		std::cout << "server name: " << serv._server[i].serverName << "with port: " << serv._server[i].port << " got created "<< std::endl;
	}
}



struct sockaddr_in* Server::_configureServerAddress(){

	struct sockaddr_in *server_addr = new sockaddr_in;
	memset(server_addr, 0, sizeof(*server_addr));
	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(SERVER_PORT);
	server_addr->sin_addr.s_addr = INADDR_ANY;

	return server_addr;
}

request *Server::_returnClassPointer(int clientSocket, std::map<int, request*> &requestClass) {
	// Iterate through the map
	std::map<int, request*>::iterator it;
	for (it = requestClass.begin(); it != requestClass.end(); ++it) {
		if (it->first == clientSocket) {
			return it->second;
		}
	}
	return NULL;
}

void Server::_changeClassPointer(int clientSocket, std::map<int, request*> &requestClass, request *newRequest) {
	// Iterate through the map
	std::map<int, request*>::iterator it;
	for (it = requestClass.begin(); it != requestClass.end(); ++it) {
		if (it->first == clientSocket) {
			it->second = newRequest;
		}
	}
}

void 	Server::_addSocket(int socket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts, std::map<int, request *> &requestClass){
	struct pollfd _pollfd;
	_pollfd.fd = socket;
	_pollfd.events = POLLIN;
	pollFileDescriptors.push_back(_pollfd);
	socketTimeouts.push_back(time(NULL));
	requestClass.insert(std::make_pair(socket, (request *)NULL));
}

void Server::_removeSocket(int index, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts){
	close(pollFileDescriptors[index].fd);
	pollFileDescriptors.erase(pollFileDescriptors.begin() + index);
	socketTimeouts.erase(socketTimeouts.begin() + index);
	std::cerr << "removed socket: " << index <<  std::endl;
}

int Server::_createSocket(int port, Server &serv) {
	Server haha = serv;

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket < 0) {
		std::cerr << "Error creating socket" << std::endl;
		return -1;
	}
	int reuse = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
		perror("setsockopt");
		close(serverSocket);
		exit(EXIT_FAILURE);
	}
	if (bind(serverSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Error binding socket" << std::endl;
		return -1;
	}
	if (listen(serverSocket, 5) < 0) {
		std::cerr << "Error listening" << std::endl;
		return -1;
	}
	std::cout << "Server listening on port " << port << std::endl;
	return serverSocket;
}

void Server::_handleNewConnection(int serverSocket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts, std::map<int, request *> &requestClass) {
	int client_socket = accept(serverSocket, nullptr, nullptr);
	if (client_socket < 0) {
		std::cerr << "Error accepting connection" << std::endl;
	} else {
		std::cout << "Accepted new connection" << std::endl;
		Server::_addSocket(client_socket, pollFileDescriptors, socketTimeouts, requestClass);
		std::cout << "new client socket got created number: " << client_socket << std::endl;
	}
}

//void Server::_processPostRequest(Server &serv, int clientSocket, std::map<int, void *> &requestClass, std::vector<uint8_t> &clientRequest) {
//	if (_returnClassPointer(clientSocket, requestClass) == NULL) {
//		postRequest *newRequest = new postRequest(clientRequest);
//		newRequest->printPostRequest();
//		_changeClassPointer(clientSocket, requestClass, newRequest);
//	}
//	postRequest *a = static_cast<postRequest *>(_returnClassPointer(clientSocket, requestClass));
//	if (!a->getAllChunksSent()){
//		try {
//			a->writeBinaryToFile(clientRequest);
//		}
//		catch (std::exception &e){
//			std::cout << "caught exception of post Request" << std::endl;
//		}
//	}
//	else
//		std::cout << "all chunks sent" << std::endl;
//}


void Server::_handleClientData(Server &serv, int clientSocket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts, std::map<int, request *> &requestClass) {
	std::vector<uint8_t> clientRequest(serv._buffSize);
	recv(clientSocket, &clientRequest[0], serv._buffSize, 0);
//	clientRequest = parsing::unsignedCharToVector(buffer, 2000);
//	std::string str(clientRequest.begin(), clientRequest.end());
//	std::string check = parsing::vectorToString(clientRequest);
//	std::cout << check << std::endl;
	request newRequest = request(clientRequest);

	if (_returnClassPointer(clientSocket, requestClass) == NULL) {
		if (newRequest.getPostMethod()){
			postRequest *newPostRequest = new postRequest(clientRequest);
			_changeClassPointer(clientSocket, requestClass, newPostRequest);
		}
		else if (newRequest.getGetMethod()){
			getRequest *newGetRequest = new getRequest(clientRequest);
			_changeClassPointer(clientSocket, requestClass, newGetRequest);
		}
		else if (newRequest.getDeleteMethod()){
			deleteRequest *newDeleteRequest = new deleteRequest(clientRequest);
			_changeClassPointer(clientSocket, requestClass, newDeleteRequest);
		}
//		else
//			std::cout << "wrong request method: " << newRequest.getRequestString() << std::endl;
	}
	request *classPointer = _returnClassPointer(clientSocket, requestClass);
	if  (dynamic_cast<postRequest*>(static_cast<request*>(classPointer))){
		std::cout << "post request incoming\n";
		postRequest *postR = static_cast<postRequest *>(_returnClassPointer(clientSocket, requestClass));
		if (!postR->getAllChunksSent()){
			try {
				postR->writeBinaryToFile(clientRequest);
			}
			catch (std::exception &e){
				std::cout << "caught exception of post Request" << std::endl;
			}
		}
		else{
			_changeClassPointer(clientSocket, requestClass, NULL);
			std::cout << "all chunks sent server3.cpp" << std::endl;
		}
	}
	else if (dynamic_cast<getRequest*>(static_cast<request*>(classPointer))){
		std::cout << "get request incoming\n";
		getRequest *get = static_cast<getRequest *>(_returnClassPointer(clientSocket, requestClass));
		request newClientRequest(clientRequest);
		response newResponse(newClientRequest.getStringURL());
		send(clientSocket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
		_changeClassPointer(clientSocket, requestClass, NULL);
	}
	else if (dynamic_cast<deleteRequest*>(static_cast<request*>(classPointer))){
		std::cout << "delete request incoming\n";
		deleteRequest *deleteR = static_cast<deleteRequest *>(_returnClassPointer(clientSocket, requestClass));
	}
//		close(clientSocket);
}

int Server::_serverRoutine(Server &serv, int index) {
	index = 0;
	int serverSocket = _createSocket(serv._server[index].port, serv);
	if (serverSocket < 0) {
		return 1;
	}
	std::vector<struct pollfd> pollFileDescriptors;
	std::vector<long long> socketTimeouts;
	std::map<int, request*> requestClass;

	_addSocket(serverSocket, pollFileDescriptors, socketTimeouts, requestClass);

	while (true) {
		int num_ready = poll(&pollFileDescriptors[0], pollFileDescriptors.size(), 0);
		if (num_ready < 0) {
			std::cerr << "Error in poll" << std::endl;
			return 1;
		}
		if (pollFileDescriptors[0].revents & POLLIN) {
			_handleNewConnection(serverSocket, pollFileDescriptors, socketTimeouts, requestClass);
		}
		for (size_t i = 1; i < pollFileDescriptors.size(); ++i) {
//			std::cout << "size pollFileDescriptors: " << pollFileDescriptors.size() << std::endl;
			if (pollFileDescriptors[i].revents & POLLIN) {
				_handleClientData(serv, pollFileDescriptors[i].fd, pollFileDescriptors, socketTimeouts, requestClass);
			}
//			std::cout << "if (time: " << time(NULL) << "- socketTimeouts[" << i << "]: " << socketTimeouts[i] << " > serv._clienttimeout: " << serv._clientTimeout << std::endl;
//			if (time(NULL) - socketTimeouts[i] > serv._clientTimeout) {
//				_removeSocket(i, pollFileDescriptors, socketTimeouts);
//			}
		}
	}
	close(serverSocket);
	return 0;
}



