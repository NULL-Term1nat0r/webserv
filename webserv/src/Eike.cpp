/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:34:43 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/03 16:34:43 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Header.h"
#include "../includes/request.hpp"
#include "../includes/parsing.hpp"
//#include "../includes/serverConf.hpp"
//#include "../includes/response.hpp"
#include "../includes/server.hpp"

int main(){
	try {
		server::runAllServers("../config_parser/confFiles/server.conf");
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}