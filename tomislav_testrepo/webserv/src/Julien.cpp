/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Julien.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:25:47 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/17 14:49:46 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/config.hpp"
#include "../includes/server.hpp"

void	wrongArgAmount() {
	std::cerr << "Error: Number of arguments has to be exactly 2." << std::endl;
}

int main(int argc, char **argv) {
	if (argc != 2)
		return (wrongArgAmount(), 1);
	try {
		Config	conf;
		conf.parseConfFile(argv[1]);
		// conf.iterateContainer();
		Server	serv;
		serv.getServerConf(conf);
		// serv.iterate();
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
