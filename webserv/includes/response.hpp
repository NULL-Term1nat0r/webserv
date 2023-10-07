
#ifndef response_HPP
#define response_HPP

#include <string>
#include <iostream>

class response
{
private:
	// Class members

public:
	response();
	response(std::string type);
	response(const response &other);
	~response();
	response &operator=(const response &other);

	static std::string getResponse();
};

#endif
