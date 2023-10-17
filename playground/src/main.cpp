
#include "../inc/config.hpp"
#include "../inc/server.hpp"

#include "../inc/Header.h"
#include "../inc/clientRequest.hpp"
#include "../inc/parsing.hpp"
#include "../inc/webServer.hpp"
#include "../inc/response.hpp"

void	wrongArgAmount() {
	std::cerr << "Error: Number of arguments has to be exactly 2." << std::endl;
}

int main(int argc, char **argv) {
	if (argc != 2)
		return (wrongArgAmount(), 1);
	try {
		Config	conf;
		conf.parseConfFile(argv[1]);
		Server	serv;
		serv.getServerConf(conf);

		size_t z = 0;
		// webServer::startServer(serv, z);
		for (size_t z = 0; z < serv._server.size(); z++)
			webServer::startServer(serv, z);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
