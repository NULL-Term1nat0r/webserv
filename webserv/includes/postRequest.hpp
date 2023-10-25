/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postpostRequest.hpp                                    :+:      :+:    :+:   */
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
/*   postRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:32:29 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/03 14:42:48 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef postRequest_HPP
#define postRequest_HPP

#include "Header.h"
#include "request.hpp"


class postRequest : public request{
private:
	std::string				_boundary;
	int 					_contentLength;
	std::string				_fileName;
	std::string				_fileType;

	std::vector<uint8_t> 	_binaryData;

	bool					_multiFormData;
	bool					_textData;
	bool					_cgi;

	bool					firstChunkSent;


public:
	explicit postRequest(std::vector<uint8_t> &postRequest);
	postRequest();
	~postRequest();

	void parseBoundary(std::string &data);
	void parseContentLength(std::string &data);
	void parseFileName(std::vector<uint8_t> &data);
	void parseFileType(std::vector<uint8_t> &data);
	void parseDataType(std::string &data);
	void parseCgi(std::string &data);

	int checkPostrequest();

	std::string getBoundary();
	int getContentLength();
	bool getMultiFormData();
	bool getTextData();
};

#endif


