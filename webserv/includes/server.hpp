/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server1.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:02:17 by estruckm          #+#    #+#             */
/*   Updated: 2023/11/13 17:25:27 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Header.h"
//#include "config.hpp"
#include "request.hpp"
#include "postRequest.hpp"
#include "deleteRequest.hpp"
#include "getRequest.hpp"
#include "cgiRequest.hpp"
#include "response.hpp"
#include "serverConf.hpp"

class response;

class server {

	private:

	public:
		server(serverConf &serverConf, int serverIndex);
		~server();

		class client {
			public:

				client(int clientSocket);
				~client();

				void executeClientRequest(int buffSize, std::vector<struct pollfd> pollEvents, std::vector<client> &clients);
				void executeClientResponse(int buffSize, std::vector<struct pollfd> pollEvents, std::vector<client> &clients);

				int clientSocket;
				time_t lastActivity;
				request *clientRequest;
				response *clientResponse;
		};

		class pollNotWorking : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		serverConf &serverConfig;
		int serverSocket;
		int serverIndex;
		std::vector<struct pollfd> pollEvents;
		std::vector<client> clients;

		std::vector<long long> clientTimeouts;
		std::map<int, request*> clientRequests;
		std::map<int, response*> clientResponses;

		request *returnRequestClass(int clientSocket);
		response *returnResponseClass(int clientSocket);

		void updateClientRequests(int clientSocket, request *newRequest);
		void updateClientResponses(int clientSocket, response *newResponse);

		void handleNewConnection();

		void addSocket(int clientSocket);
		void removeSocket(int clientSocket);

		void handleClientRequest(int clientSocket);
		void handleClientResponse(int clientSocket);

		void createServerSocket();

		void serverRoutine();

		static void runAllServers(std::string configFilePath);

		serverConf& getServerConfig();
		int getServerIndex();
};


#endif