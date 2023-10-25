
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

	static int findWord(std::string str, std::string word);
	static int findMethod(std::string str);
	static int findProtocol(std::string str);
	static std::string findValue(std::string str, int number);
	static int checkIfFound(std::string array[], std::string str);
	static std::string getValue(std::string str, std::string key, int number);
	static std::string vectorToString(const std::vector<uint8_t>& inputVector);
	static std::string vectorToLimitedString(const std::vector<uint8_t>& data, size_t maxBytes);
//	int findConnection(std::string str);
//	int findPortNumber(std::string str);
//	int findIp(std::string str);
};

#endif
