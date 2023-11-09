
#ifndef response_HPP
#define response_HPP

#include "Header.h"
#include "request.hpp"

class response
{
private:
	std::string _response;
	long _dataSend;
	bool _allChunkSent;


public:
	response();
	response(std::string url);
	response(const response &other);
	~response();
	response &operator=(const response &other);

	class responseInvalidFileException : public std::exception
	{
		virtual const char *what() const throw();
	};

	std::string getResponse();
	std::string createResponse(std::string url);
	std::string getFile(std::string directoryPath);
};

bool hasHtmlExtension(const char* filename);

#endif
