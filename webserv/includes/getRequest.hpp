/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getgetRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:16:11 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/24 14:16:11 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:32:29 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/03 14:42:48 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef getRequest_HPP
#define getRequest_HPP

#include "Header.h"
#include "request.hpp"


class getRequest : public request{
private:
	std::string filePath;

public:
	explicit getRequest(std::vector<uint8_t> &getRequest);
	getRequest();
	~getRequest();

	class getRequestInvalidFileException : public std::exception
	{
		virtual const char *what() const throw();
	};

	bool fileExists(const char* filePath);
	std::string createFilePath();

	std::string getErrorPagePath(int errorCode);

	std::string getFilePath();

};

#endif


