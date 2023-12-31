/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                  :+:      :+:    :+:   */
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


class request {
	private:
		bool _validRequest;

		bool _get;
		bool _post;
		bool _delete;
		bool _URL;
		bool _cgi;
		bool _invalidPageMethod;
		bool _httpProtocol;

		bool _aliveConnection;
		bool _closeConnection;

		serverConf &_serverConfig;
		int _serverIndex;

		std::string _stringURL;
		std::string _stringHttpProtocol;

		std::string _request;
		std::string filePath;


	public:
		explicit request(std::vector<uint8_t> &clientRequest, serverConf &serverConfig, int serverIndex);
		virtual ~request();

		bool getValidRequest();


		bool getGetMethod();
		bool getPostMethod();
		bool getDeleteMethod();
		bool getCgi();
		bool checkPageMethod(std::string method);
		bool getURL();

		bool getAliveConnection();
		bool getCloseConnection();

		std::string getStringURL();
		std::string getReferer();
		std::string &getRequestString();
		bool getCgiMethod();

		bool checkCgi(std::string url);

		void setDefaultValues();
		void parseRequest();

		void validateRequest();
		void printRequest();
};

#endif



/*
steps for response class:
		what do I dont know ?
			- how much is the contenlength, all data or just file data
		- inherit from request class to get the url string
		-*/
