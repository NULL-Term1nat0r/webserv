/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:13:02 by estruckm          #+#    #+#             */
/*   Updated: 2023/11/06 15:13:02 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

server::server(serverConf &serverConf, int serverIndex) : serverConfig(serverConf), serverIndex(serverIndex) {
	std::cout << "server " << serverIndex << " constructor for port: " << serverConfig._server[serverIndex].port << " got called\n" << std::endl;
	try {
		createServerSocket();
	}
	catch (std::exception &e){
		std::cout << "caught exception of server" << std::endl;
	}
}

server::~server() {
	close(serverSocket);
}

void server::createServerSocket() {
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(serverConfig._server[serverIndex].port);
//	std::cout << "serversocker with port: " << serverConfig._server[serverIndex].port << std::endl;
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	this->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->serverSocket < 0)
		throw std::runtime_error("Socket creation failed");

	int opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		close(this->serverSocket);
		throw std::runtime_error("setsockopt");
	}
	if (bind(this->serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
		throw std::runtime_error("Socket binding failed");

	if (listen(this->serverSocket, 5) < 0)
		throw std::runtime_error("Socket listening failed");
	addSocket(this->serverSocket);
}

void server::addSocket(int clientSocket) {
	struct pollfd _pollfd;
	_pollfd.fd = clientSocket;
	_pollfd.events = POLLIN;
	pollEvents.push_back(_pollfd);
	clientTimeouts.push_back(time(NULL));
	clientRequests[clientSocket] = (request *)NULL;
	clientResponses[clientSocket] = (response *)NULL;
}

void server::removeSocket(int index) {
	close(pollEvents[index].fd);
	clientTimeouts.erase(clientTimeouts.begin() + index);
	clientRequests.erase(pollEvents[index].fd);
	clientResponses.erase(pollEvents[index].fd);
	pollEvents.erase(pollEvents.begin() + index);
}

void server::updateClientRequests(int clientSocket, request *newRequest) {
	clientRequests[clientSocket] = newRequest;
}

void server::updateClientResponses(int clientSocket, response *newResponse) {
	clientResponses[clientSocket] = newResponse;
}

request *server::returnRequestClass(int clientSocket) {
	if (clientRequests.find(clientSocket) != clientRequests.end())
		return clientRequests[clientSocket];
	return NULL;
}

response *server::returnResponseClass(int clientSocket) {
	if (clientResponses.find(clientSocket) != clientResponses.end())
		return clientResponses[clientSocket];
	return NULL;
}

void server::handleNewConnection() {
	int clientSocket;
	struct sockaddr_in clientAddress;
	socklen_t clientAddressSize = sizeof(clientAddress);

	clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
	if (clientSocket < 0)
		throw std::runtime_error("Socket accept failed");

//	fcntl(clientSocket, F_SETFL, O_NONBLOCK);
	addSocket(clientSocket);
}

void server::handleClientRequest(int clientSocket) {
	std::vector<uint8_t> clientRequest(serverConfig._buffSize);
	recv(clientSocket, &clientRequest[0], serverConfig._buffSize, 0);
	request newRequest = request(clientRequest);

	if (returnRequestClass(clientSocket) == NULL) {
		if (newRequest.getPostMethod()){
			postRequest *newPostRequest = new postRequest(clientRequest);
			updateClientRequests(clientSocket, newPostRequest);
		}
		else if (newRequest.getGetMethod()){
			getRequest *newGetRequest = new getRequest(clientRequest);
			updateClientRequests(clientSocket, newGetRequest);
		}
		else if (newRequest.getDeleteMethod()){
			deleteRequest *newDeleteRequest = new deleteRequest(clientRequest);
			updateClientRequests(clientSocket, newDeleteRequest);
		}
		
	}
	request *requestPointer = returnRequestClass(clientSocket);
	if  (dynamic_cast<postRequest*>(static_cast<request*>(requestPointer))){
		std::cout << "post request incoming\n";
		postRequest *postR = static_cast<postRequest *>(returnRequestClass(clientSocket));
		postR->printPostRequest();
		if (!postR->getAllChunksSent()){
			try {
				postR->writeBinaryToFile(clientRequest);
			}
			catch (std::exception &e){
				std::cout << "caught exception of post Request" << std::endl;
			}
			if (postR->getAllChunksSent()) {

				response newResponse(returnRequestClass(clientSocket)->getStringURL());
				send(clientSocket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
				updateClientRequests(clientSocket, NULL);
				std::cout << "all chunks sent server3.cpp" << std::endl;
				pollEvents[clientSocket].events = POLLOUT;
			}
		}
	}
	else if (dynamic_cast<getRequest*>(static_cast<request*>(requestPointer))){
		std::cout << "get request incoming\n";
		getRequest *get = static_cast<getRequest *>(returnRequestClass(clientSocket));
		request newClientRequest(clientRequest);
		response newResponse(newClientRequest.getStringURL());
		send(clientSocket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
		updateClientRequests(clientSocket, NULL);
	}
	else if (dynamic_cast<deleteRequest*>(static_cast<request*>(requestPointer))){
		std::cout << "delete request incoming\n";
		deleteRequest *deleteR = static_cast<deleteRequest *>(returnRequestClass(clientSocket));
	}
//		close(clientSocket);
	
}

void server::serverRoutine(){
	serverConfig._server[serverIndex].port = 9;
//	std::cout << "serverRoutine got called for port " << serverConfig._server[serverIndex].port << std::endl;
	int num_ready = poll(&pollEvents[0], pollEvents.size(), 0);
	if (num_ready < 0) {
		std::cout << "num_ready smaller 0 " << std::endl;
		//throw pollNotWorking();
	}
//	std::cout << "pollEvent -> size: " << pollEvents.size() << std::endl;
	if (pollEvents[0].revents & POLLIN) {
		handleNewConnection();
	}
	for (size_t i = 0; i < pollEvents.size(); ++i) {
		if (pollEvents[i].revents != 32)
//			std::cout << "size revents: " << pollEvents[i].revents << " pollin: " << POLLIN << std::endl;
		if (pollEvents[i].revents & POLLIN) {
			if (pollEvents[i].fd == serverSocket) {
				std::cout << "new connection incoming" << std::endl;
				handleNewConnection();
			}
			else {
				handleClientRequest(pollEvents[i].fd);
				std::cout << "handle clientRequest incoming" << std::endl;
			}
		}
		if (pollEvents[i].revents & POLLOUT) {
			std::cout << "POLLOUT activated" << std::endl;//something
		}
//			std:
//			std::cout << "if (time: " << time(NULL) << "- socketTimeouts[" << i << "]: " << socketTimeouts[i] << " > serv._clienttimeout: " << serv._clientTimeout << std::endl;
//			if (time(NULL) - socketTimeouts[i] > serv._clientTimeout) {
//				_removeSocket(i, pollEvents, socketTimeouts);
//			}
	}
}

void server::runAllServers(std::string configFilePath) {
	Config conf(configFilePath);
	serverConf serverConfigs(conf);
	std::vector<server *> servers;
	for (int i = 0; i < static_cast<int>(serverConfigs._server.size()); i++) {
		try{
			server *serverClass = new server(serverConfigs, i);
			servers.push_back(serverClass);
		}
		catch (std::exception &e){
			std::cout << "caught exception of server" << std::endl;
		}
	}
	while (true) {
		for (int i = 0; i < servers.size(); i++){
			servers[i]->serverRoutine();
		}
	}
}

