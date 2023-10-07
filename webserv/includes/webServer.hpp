
#ifndef webServer_HPP
#define webServer_HPP

#include "Header.h"

#include "response.hpp"

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
	static int startServer();

};

#endif
