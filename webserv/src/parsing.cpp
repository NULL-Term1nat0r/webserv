
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

std::string parsing::vectorToString(const std::vector<uint8_t>& inputVector) {
	std::string result;
	for (size_t i = 0; i < inputVector.size(); ++i) {
		result += static_cast<char>(inputVector[i]);
	}
	return result;
}

std::string parsing::returnValue(std::string key, std::string source, std::string limiter){
	size_t start = source.find(key);
	size_t end = source.find(limiter, start + key.length());
	if (key == "filename=\""){
		if (source.find(key) == std::string::npos)
			std::cout << "key not found" << std::endl;
	}
	return source.substr(start + key.length(), end - start - key.length());
}

std::vector<uint8_t> parsing::unsignedCharToVector(unsigned char *data, size_t size){
	std::vector<uint8_t> result;
	result.reserve(size); // Reserve space for the expected number of elements to avoid reallocation

	for (size_t i = 0; i < size; ++i) {
		result.push_back(data[i]);
	}

	return result;
}

