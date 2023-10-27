
#include "../includes/parsing.hpp"

// Implement class methods here

parsing::parsing()
{
	std::cout << "parsing default constructor called" << std::endl;
}

parsing::~parsing()
{
	std::cout << "parsing destructor called" << std::endl;
}

int parsing::findWord(std::string str, std::string word){


	size_t found = str.find(word);

	while (found != std::string::npos) {
		found = str.find(word, found + 1);
		return 1;
	}
	return 0;
}

int parsing::findMethod(std::string str){
	std::string methodType[3] = {"GET", "POST", "DELETE"};
	for (int i = 0; i < 3; i++)
	{
		if (parsing::findWord(str, methodType[i]))
			return i;
	}
	return 0;
}

int parsing::findProtocol(std::string str){
	std::string protocolType[2] = {"HTTP/1.1", "HTTP/1.0"};
	for (int i = 0; i < 2; i++)
	{
		if (parsing::findWord(str, protocolType[i]))
			return i;
	}
	return 0;
}

std::string parsing::getValue(std::string str, std::string key, int number){
	std::string line;
	std::string value;
	std::istringstream iss(str);
	while (std::getline(iss, line, '\n'))
	{
		value = parsing::findValue(line, 1);
		if (value == key)
			return parsing::findValue(line, number);
	}
	return "";
}

std::string parsing::vectorToString(const std::vector<uint8_t>& inputVector) {
	std::string result;
	for (size_t i = 0; i < inputVector.size(); ++i) {
		result += static_cast<char>(inputVector[i]);
	}
	return result;
}

std::string parsing::vectorToLimitedString(const std::vector<uint8_t>& data, size_t maxBytes) {
	size_t length = std::min(maxBytes, data.size());
	std::string result(data.begin(), data.begin() + length);

	return result;
}

std::string parsing::getStringBetweenQuotes(std::string &input) {
	size_t startPos = input.find('"');
	size_t endPos = input.find('"', startPos + 1);
	std::string result = input.substr(startPos + 1, endPos - startPos - 1);
	return result;
}

std::string parsing::getLineOfKey(std::string str, std::string key) {
	std::string line;
	std::istringstream iss(str);
	while (std::getline(iss, line, '\n'))
	{
		if (parsing::findWord(line, key))
			return line;
	}
	return "";
}



//std::string parsing::findValue(std::string str, int number) {
//	size_t spacePos = str.find(' ');
//	if (spacePos != std::string::npos) {
//		std::string referer = str.substr(spacePos + 1);
//		referer.erase(0, referer.find_first_not_of(" \t\n\r\f\v"));
//		return referer;
//	} else
//		return "";
//}
//
//size_t spacePos = str.find(' ');
//if (spacePos != std::string::npos) {
//std::string referer = str.substr(spacePos + 1);
//referer.erase(0, referer.find_first_not_of(" \t\n\r\f\v"));
//return referer;
//} else
//return "";

std::string parsing::findValue(std::string str, int number) {
	std::istringstream iss(str);

	std::vector<std::string> words;
	std::string word;

	while (iss >> word) {
		words.push_back(word);
	}
	if (number >= 1 && static_cast<size_t>(number) <= words.size()) {
		words[number - 1].erase(0, words[number - 1].find_first_not_of(" \t\n\r\f\v"));
		return words[number - 1];
	} else {
		return "";
	}
}

int parsing::checkIfFound(std::string array[], std::string str){
	for (int i = 0; i < 3; i++)
	{
		if (parsing::findWord(str, array[i]))
			return i;
	}
	return -1;
}


