
#ifndef response_HPP
#define response_HPP

#include "Header.h"
#include "server.hpp"

class server;

class response : public request
{
private:

public:
	response(std::string filePath);
	~response();
	response &operator=(const response &other);

	class responseInvalidFileException : public std::exception
	{
		virtual const char *what() const throw();
	};

	std::string url;
	std::string filePath;

	long _dataSend;
	long startPosition;
	long bodySize;
	bool firstChunkSent;
	bool _allChunkSent;

	std::string getResponse();
	long countFileSize(std::string filePath);
	std::string readFileContent(int chunkSize);

	std::string createFirstChunk(int chunkSize);
	std::string getChunk(int chunkSize);

	bool removeFile(const char* filepath);
};

#endif
