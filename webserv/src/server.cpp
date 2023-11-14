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
	std::cout << "server" << this->serverIndex << " constructor for port: " << this->serverConfig._server[this->serverIndex].port << " got called\n" << std::endl;
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
	client newClient(clientSocket);
	clients.push_back(newClient);
	clientTimeouts.push_back(time(NULL));
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

//void server::handleClientRequest(int clientSocket) {
//	std::vector<uint8_t> clientRequest(serverConfig._buffSize);
//	recv(clientSocket, &clientRequest[0], serverConfig._buffSize, 0);
//	request newRequest = request(clientRequest);
//
//	if (returnRequestClass(clientSocket) == NULL) {
//		if (newRequest.getPostMethod()){
//			postRequest *newPostRequest = new postRequest(clientRequest);
//			updateClientRequests(clientSocket, newPostRequest);
//		}
//		else if (newRequest.getGetMethod()){
//			getRequest *newGetRequest = new getRequest(clientRequest);
//			updateClientRequests(clientSocket, newGetRequest);
//		}
//		else if (newRequest.getDeleteMethod()){
//			deleteRequest *newDeleteRequest = new deleteRequest(clientRequest);
//			updateClientRequests(clientSocket, newDeleteRequest);
//		}
//
//	}
//	request *requestPointer = returnRequestClass(clientSocket);
//	if  (dynamic_cast<postRequest*>(static_cast<request*>(requestPointer))){
//		std::cout << "post request incoming\n";
//		postRequest *postR = static_cast<postRequest *>(returnRequestClass(clientSocket));
//		postR->printPostRequest();
//		if (!postR->getAllChunksSent()){
//			try {
//				postR->writeBinaryToFile(clientRequest);
//			}
//			catch (std::exception &e){
//				std::cout << "caught exception of post Request" << std::endl;
//			}
//			if (postR->getAllChunksSent()) {
////				response newResponse = response(returnRequestClass(clientSocket)->getStringURL());
////				send(clientSocket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
//				updateClientRequests(clientSocket, NULL);
//				std::cout << "all chunks sent server3.cpp" << std::endl;
//				pollEvents[clientSocket].events = POLLOUT;
//			}
//		}
//	}
//	else if (dynamic_cast<getRequest*>(static_cast<request*>(requestPointer))){
//		std::cout << "get request incoming\n";
//		getRequest *get = static_cast<getRequest *>(returnRequestClass(clientSocket));
//		request newClientRequest(clientRequest);
////		response newResponse(newClientRequest.getStringURL());
////		send(clientSocket, newResponse.getResponse().c_str(), newResponse.getResponse().length(), 0);
//		updateClientRequests(clientSocket, NULL);
//	}
//	else if (dynamic_cast<deleteRequest*>(static_cast<request*>(requestPointer))){
//		std::cout << "delete request incoming\n";
//		deleteRequest *deleteR = static_cast<deleteRequest *>(returnRequestClass(clientSocket));
//	}
////		close(clientSocket);
//}

//void server::handleClientResponse(int clientSocket) {
//	response *responsePointer = returnResponseClass(clientSocket);
//	if (responsePointer != NULL) {
//		std::string responseString = responsePointer->getResponse();
//		send(clientSocket, responseString.c_str(), responseString.length(), 0);
//		updateClientResponses(clientSocket, NULL);
//	}
//}

void server::serverRoutine(){

	int num_ready = poll(&this->pollEvents[0], this->pollEvents.size(), 0);
	if (num_ready < 0) {
		std::cout << "num_ready smaller 0 " << std::endl;
		//throw pollNotWorking();
	}//	std::cout << "pollEvent -> size: " << pollEvents.size() << std::endl;
//	if (this->pollEvents[0].revents & POLLIN) {
//		handleNewConnection();
//	}
	for (size_t i = 0; i < this->pollEvents.size(); ++i) {
		if (this->pollEvents[i].revents == POLLIN) {
			if (this->pollEvents[i].fd == this->serverSocket) {
				std::cout << "new connection incoming" << std::endl;
				handleNewConnection();
			}
			else {
				this->pollEvents[i].revents = clients[i].executeClientRequest(this->serverConfig._buffSize, this->pollEvents, this->clients);
//				std::cout << "address of clientclass: " << &clients[i] << std::endl;
//				std::cout << "clientSocket.events = " << this->pollEvents[i].events << std::endl;
//				std::cout << "address of pollEvents: " << &this->pollEvents << std::endl;
//				std::cout << "address of struct in container: " << &this->pollEvents[i] << std::endl;
//				std::cout << "address of eventInt: " << &this->pollEvents[i].events << std::endl;
			}
		}
		if (pollEvents[i].revents == 0 && clients[i].clientResponse != NULL) {
			this->pollEvents[i].revents = clients[i].executeClientResponse(this->serverConfig._buffSize, this->pollEvents, this->clients);
		}
		usleep(300000);
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
//	for (int i = 0; i < static_cast<int>(serverConfigs._server.size()); i++) {
	for (int i = 0; i < 1; i++) {
		try{
			server *serverClass = new server(serverConfigs, i);
			servers.push_back(serverClass);
		}
		catch (std::exception &e){
			std::cout << "caught exception of server" << std::endl;
		}
	}
	while (true) {
//		for (int i = 0; i < servers.size(); i++){
		for (int i = 0; i < servers.size(); i++){
			servers[i]->serverRoutine();
		}
	}
}

serverConf& server::getServerConfig(){
	return this->serverConfig;
}

int server::getServerIndex(){
	return this->serverIndex;
}


