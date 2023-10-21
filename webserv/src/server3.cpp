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

void 	Server::_addSocket(int socket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts){
	struct pollfd _pollfd;
	_pollfd.fd = socket;
	_pollfd.events = POLLIN;
	pollFileDescriptors.push_back(_pollfd);
	socketTimeouts.push_back(time(NULL));
}

void Server::_removeSocket(int index, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts){
	close(pollFileDescriptors[index].fd);
	pollFileDescriptors.erase(pollFileDescriptors.begin() + index);
	socketTimeouts.erase(socketTimeouts.begin() + index);
	std::cerr << "removed socket: " << index <<  std::endl;
}



int Server::_createSocket(int port) {
	int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket < 0) {
		std::cerr << "Error creating socket" << std::endl;
		return -1;
	}
	int reuse = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
		perror("setsockopt");
		close(server_socket);
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Error binding socket" << std::endl;
		return -1;
	}

	if (listen(server_socket, 5) < 0) {
		std::cerr << "Error listening" << std::endl;
		return -1;
	}

	std::cout << "Server listening on port " << port << std::endl;
	return server_socket;
}

void Server::_handleNewConnection(int server_socket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts) {
	int client_socket = accept(server_socket, nullptr, nullptr);
	if (client_socket < 0) {
		std::cerr << "Error accepting connection" << std::endl;
	} else {
		std::cout << "Accepted new connection" << std::endl;
		Server::_addSocket(client_socket, pollFileDescriptors, socketTimeouts);
	}
}

void Server::_handleClientData(int client_socket) {
	char buffer[900000];
	ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

	if (bytes_received <= 0) {
		std::cout << "Client with socket " << client_socket << " disconnected" << std::endl;
	} else {
		std::string request(buffer, bytes_received);
		std::cout << request << std::endl;

		if (request.find("POST") != std::string::npos) {
			clientRequest newClientRequest(request);
			newClientRequest.printRequest();
			response newResponse(newClientRequest.getStringURL());
			send(client_socket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
		}
		else {
			clientRequest newClientRequest(request);
			response newResponse(newClientRequest.getStringURL());
			send(client_socket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
		}
	}
}

int Server::_serverRoutine(Server &serv, int index) {
	int serverSocket = _createSocket(serv._server[index].port);
	std::cout << "server socket1: " << serverSocket << std::endl;
	if (serverSocket < 0) {
		return 1;
	}
	std::vector<struct pollfd> pollFileDescriptors;
	std::vector<long long> socketTimeouts;
	_addSocket(serverSocket, pollFileDescriptors, socketTimeouts);
	std::cout << "server socket2: " << pollFileDescriptors[0].fd << std::endl;

	while (true) {
		int num_ready = poll(&pollFileDescriptors[0], pollFileDescriptors.size(), 0);
		if (num_ready < 0) {
			std::cerr << "Error in poll" << std::endl;
			return 1;
		}
		if (pollFileDescriptors[0].revents & POLLIN) {
			_handleNewConnection(serverSocket, pollFileDescriptors, socketTimeouts);
		}
		for (size_t i = 1; i < pollFileDescriptors.size(); ++i) {
			if (pollFileDescriptors[i].revents & POLLIN) {
				_handleClientData(pollFileDescriptors[i].fd);
			}
			if (time(NULL) - socketTimeouts[i] > serv._clientTimeout) {
				_removeSocket(i, pollFileDescriptors, socketTimeouts);
			}
		}
	}
	close(serverSocket);
	return 0;
}



