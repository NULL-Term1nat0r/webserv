
#include <string>
#include <iostream>
#include "../includes/config.hpp"
#include "../includes/serverConf.hpp"

void	wrongArgAmount() {
	std::cerr << "Error: Number of arguments has to be exactly 2." << std::endl;
}

//valid extensions for upload
void	serverConf::iterate() {
	std::cout << "WorkerProcess: " << _workerProcesses << std::endl;
	std::cout << "WorkerConnections: "<< _workerConnections << std::endl;
	std::cout << "ScriptTimeout: " << _scriptTimeout << std::endl;
	std::cout << "ClientTimeout: " << _clientTimeout << std::endl;
	std::cout << "BuffSize: " << _buffSize << std::endl;
	std::cout << "Backlog: " << _backlog << std::endl;
	for (serverSettings& server : _server) {
        if (!server.locations.empty()) {
			std::cout << "Bodysize: " << server.bodySize << std::endl;
            std::cout << "ServerName: " << server.serverName << std::endl;
            std::cout << "Port: " << server.port << std::endl;
            std::cout << "Error Pages:" << std::endl;
            for (const auto& errorPage : server.errorPages) {
                std::cout << "  " << errorPage.first << " -> " << errorPage.second << std::endl;
            }
            std::cout << "Locations:" << std::endl;
            for (const auto& location : server.locations) {
                    std::cout << "  Location: " << location.first << std::endl;
                   	const LocationStruc& locStruct = location.second;
                    std::cout << "    allowGet: " << locStruct.allowGet << std::endl;
                    std::cout << "    allowPost: " << locStruct.allowPost << std::endl;
                    std::cout << "    allowDelete: " << locStruct.allowDelete << std::endl;
                    std::cout << "    autoindex: " << locStruct.autoindex << std::endl;
                    std::cout << "    root: " << locStruct.root << std::endl;
                    std::cout << "    index: " << locStruct.index << std::endl;
                    std::cout << "    Rewrite:" << locStruct.rewrite << std::endl;
                    std::cout << "    CGI:" << std::endl;
                    for (const std::string& cgi : locStruct.cgi) {
                        std::cout << "      " << cgi << std::endl;
                    }
                }
            std::cout << std::endl;
        }
    }
}

int main(int argc, char **argv) {
	if (argc != 2)
		return (wrongArgAmount(), 1);
	try {
		Config	conf;
		conf.parseConfFile(argv[1]);
		// conf.iterateContainer();
		serverConf	serv;
		serv.getServerConf(conf);
		serv.iterate();
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
