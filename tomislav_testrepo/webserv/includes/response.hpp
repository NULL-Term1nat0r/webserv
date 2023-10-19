
#ifndef response_HPP
#define response_HPP

#include "Header.h"
#include "clientRequest.hpp"

//struct cgiInfo
//{
//	std::string 	_cgiPath;		// to find a path to the cgi file
//	std::string 	_query;			// to find a query string
//	std::string 	_fileExtension;	// to find a file extension
//	std::string 	_body;
//};

class response
{
private:
	std::string _response;

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
//	int	callCGI();	// added by me
//	int inputCheck();	// added by me
//	bool checkLanguage() const;	// added by me
//	int validCgiExtension();	// added by me
//	void executeCgi();	// added by me


};

bool hasHtmlExtension(const char* filename);

#endif
