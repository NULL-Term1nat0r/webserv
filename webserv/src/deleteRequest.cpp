/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleteRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:17:32 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/24 20:25:26 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/deleteRequest.hpp"

deleteRequest::deleteRequest(std::vector<uint8_t> &requestContainer, serverConf &serverConfig, int serverIndex) : request(requestContainer, serverConfig, serverIndex), _serverConfig(serverConfig), serverIndex(serverIndex){
	deleteFile(getStringURL().c_str());
}

deleteRequest::~deleteRequest() {}

const char	*deleteRequest::deleteRequestInvalidFileException::what() const throw() {
	return "Couldn't remove file\n";
}

void deleteRequest::deleteFile(const char*filePath){
	if (remove(filePath) != 0)
		throw deleteRequestInvalidFileException();
}