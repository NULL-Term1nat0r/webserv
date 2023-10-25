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

std::vector<uint8_t> Server::_processData(Server &serv, int clientSocket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts) {
	std::vector<uint8_t> buffer(serv._buffSize); // Allocate a vector for a chunk
	ssize_t bytes_received = 0;
	ssize_t total_bytes_received = 0;
	std::vector<uint8_t> request;// This vector will store the accumulated data
//	long long currentTime = time(NULL);

	while ((bytes_received = recv(clientSocket, &buffer[0], serv._buffSize, 0)) > 0) {
		total_bytes_received += bytes_received;
		request.insert(request.end(), buffer.begin(), buffer.begin() + bytes_received);
		std::fill(buffer.begin(), buffer.end(), 0); // Clear the buffer
	}
	if (bytes_received < 0) {
		_removeSocket(clientSocket, pollFileDescriptors, socketTimeouts);// Handle the receive error
		std::cerr << "Error receiving data." << std::endl;
	} else {
		std::cout << "Total bytes received: " << total_bytes_received << std::endl;
	}
	return (request);
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

void Server::_handleNewConnection(int serverSocket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts) {
	int client_socket = accept(serverSocket, nullptr, nullptr);
	if (client_socket < 0) {
		std::cerr << "Error accepting connection" << std::endl;
	} else {
		std::cout << "Accepted new connection" << std::endl;
		Server::_addSocket(client_socket, pollFileDescriptors, socketTimeouts);
		std::cout << "new client socket got created number: " << client_socket << std::endl;
	}
}

void Server::_handleClientData(Server &serv, int clientSocket, std::vector<struct pollfd> &pollFileDescriptors, std::vector<long long> &socketTimeouts) {
//	char buffer[90000];
	std::vector<uint8_t> clientRequest;
	clientRequest = Server::_processData(serv, clientSocket, pollFileDescriptors, socketTimeouts);
	std::string check = parsing::vectorToLimitedString(clientRequest, 900);
	std::cout << check << std::endl;

		if (check.find("POST") != std::string::npos) {
			std::cout << "post request incoming\n";
			request newClientRequest(clientRequest);
			newClientRequest.printRequest();
			response newResponse(newClientRequest.getStringURL());
			send(clientSocket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
		}
		else {
			std::cout << "get request incoming\n";
			request newClientRequest(clientRequest);
			response newResponse(newClientRequest.getStringURL());
			send(clientSocket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
			std::cout << "send response: \n" << newResponse.getResponse() << std::endl;
		}
		close(clientSocket);
}

int Server::_serverRoutine(Server &serv, int index) {
	index = 0;
	int serverSocket = _createSocket(serv._server[index].port, serv);
	if (serverSocket < 0) {
		return 1;
	}
	std::vector<struct pollfd> pollFileDescriptors;
	std::vector<long long> socketTimeouts;

	_addSocket(serverSocket, pollFileDescriptors, socketTimeouts);

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
			std::cout << "size pollFileDescriptors: " << pollFileDescriptors.size() << std::endl;
			if (pollFileDescriptors[i].revents & POLLIN) {
				_handleClientData(serv, pollFileDescriptors[i].fd, pollFileDescriptors, socketTimeouts);
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



