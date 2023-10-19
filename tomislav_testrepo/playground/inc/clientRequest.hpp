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
		bool _validRequest;

		bool _get;
		bool _post;
		bool _delete;
		bool _URL;
		bool _httpProtocol;
		int _portNumber;
		int _contentLength;
		bool _aliveConnection;
		bool _closeConnection;

		std::string _stringURL;
		std::string _referer;
		std::string _stringHttpProtocol;
		std::string _ip;
		std::string _request;
		std::string _binaryDataBoundary;
		std::string _binaryData;


	public:
		clientRequest(std::string protocol);
		clientRequest();
		~clientRequest();

		bool getValidRequest();

		bool getGetMethod();
		bool getPostMethod();
		bool getDeleteMethod();

		bool getURL();

		bool getAliveConnection();
		bool getCloseConnection();

		int getPortNumber();
		int getContentLength();
		std::string getStringURL();
		std::string getReferer();
		std::string getIp();
		std::string getBinaryData();
		std::string getBinaryDataBoundary();


		void parseURL(std::string line);
		void parseHttpProtocol(std::string line);
		void parseAddress(std::string line);
		void parseConnectionType(std::string line);
		void parseReferer();
		void parseContentLength();
		void parseBinaryDataBoundary();
		void parseBinaryData();

		void parseProtocol();
		void parseGetRequest();
		void parsePostRequest();
		void parseDeleteRequest();

		void validateRequest();
		void printRequest();



		
};

#endif