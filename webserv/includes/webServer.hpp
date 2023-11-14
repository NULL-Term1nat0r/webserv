/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:32:29 by estruckm          #+#    #+#             */
/*   Updated: 2023/11/13 17:24:46 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef webServer_HPP
#define webServer_HPP

#include "Header.h"

#include "request.hpp"
#include "serverConf.hpp"

class webServer
{
private:
	// Class members

public:
	webServer();
	webServer(std::string type);
	webServer(const webServer &other);
	~webServer();
	webServer &operator=(const webServer &other);

	static std::string returnFileContent(std::string fileName);
	static int startAllServers(std::string file_path);
	static int startServer();

};

#endif
