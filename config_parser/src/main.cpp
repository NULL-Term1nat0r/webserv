
#include "../inc/config.hpp"
#include "../inc/server.hpp"

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
