/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:32:29 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/03 14:42:48 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTREQUEST_HPP
#define CLIENTREQUEST_HPP

#include "Header.h"


class clientRequest{
	private:
		bool validRequest;

		bool _get;
		bool _post;
		bool _delete;

		std::string _referer;
		bool _httpProtocol;
		std::string _stringHttpProtocol;
		std::string _ip;
		int _portNumber;
		bool _aliveConnection;
		bool _closeConnection;

		std::string _request;


	public:
		clientRequest(std::string protocol);
		clientRequest();
		~clientRequest();

		bool getValidRequest();

		bool getGetMethod();
		bool getPostMethod();
		bool getDeleteMethod();

		bool getAliveConnection();
		bool getCloseConnection();

		std::string getReferer();
		int getPortNumber();
		std::string getIp();

		void printRequest();

		void parseProtocol();
		void parseGetRequest();
		void parsePostRequest();
		void parseDeleteRequest();


		
};

#endif