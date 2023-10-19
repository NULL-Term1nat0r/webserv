#ifndef CGI_HPP
# define CGI_HPP

#include "response.hpp"
#include "clientRequest.hpp"
#include "Header.h"

class cgi : virtual clientRequest {
public:
	std::string 	_cgiPath;		// to find a path to the cgi file
	std::string 	_query;			// to find a query string
	std::string 	_fileExtension;	// to find a file extension
	std::string 	_body;


private:

	int		callCGI();
	int 	inputCheck();
	bool	checkLanguage() const;
	int 	validCgiExtension();
	void 	executeCgi();
	bool 	cgiIterate(std::string);


};

#endif