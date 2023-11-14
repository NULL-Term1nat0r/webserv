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


class request{
	protected:
		bool _validRequest;

		bool _get;
		bool _post;
		bool _delete;
		bool _URL;
		bool _httpProtocol;

		bool _aliveConnection;
		bool _closeConnection;

		std::string _stringURL;
		std::string _stringHttpProtocol;

		std::string _request;
		std::string filePath;


	public:
		explicit request(std::vector<uint8_t> &clientRequest);
		request();
		virtual ~request();

		bool getValidRequest();

		bool getGetMethod();
		bool getPostMethod();
		bool getDeleteMethod();

		bool getURL();

		bool getAliveConnection();
		bool getCloseConnection();

		std::string getStringURL();
		std::string getReferer();
		std::string &getRequestString();

		void setDefaultValues();
		void parseRequest();

		void validateRequest();
		void printRequest();
};

#endif