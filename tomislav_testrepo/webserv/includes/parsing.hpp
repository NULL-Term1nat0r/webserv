
#ifndef parsing_HPP
#define parsing_HPP

#include "Header.h"

class parsing
{
private:
	// Class members

public:
	parsing();
	~parsing();

//	static int checkIfFound(std::string array[], std::string str);
//	static std::string getValue(std::string str, std::string key, int number);
	static std::string vectorToString(const std::vector<uint8_t>& inputVector);
	static std::string vectorToLimitedString(const std::vector<uint8_t>& data, size_t maxBytes);
//	static std::string getLineOfKey(std::string str, std::string key);


	static std::string returnValue(std::string key, std::string source, std::string limiter);
	static std::vector<uint8_t> unsignedCharToVector(unsigned char *data, size_t size);

};

#endif
