
#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <random>

//2 approaches: 1. throw exception string and search in map
//2. throw exception int and search in map 



int getRandomNumber() {
    std::random_device rd;  // Create a random device
    std::mt19937 generator(rd());  // Create a Mersenne Twister random number generator
    std::uniform_int_distribution<int> distribution(1, 3);  // Create a uniform distribution between 1 and 3
    return distribution(generator);  // Generate and return a random number between 1 and 3
}

void	testFunc()
{
	int i = getRandomNumber();
	if (i == 1)
		throw 301;
	else if (i == 2)
		throw 400;
	else if (i == 3)
		throw 445;
}


int main(){
	std::map<int, std::string>		errorPages;
	errorPages[301] = "301.html";
	errorPages[400] = "400.html";
	errorPages[404] = "404.html";
	errorPages[500] = "500.html";
	errorPages[501] = "501.html";
	try{
		testFunc();
	}
	catch(int statusCode){
		if (errorPages.find(statusCode) != errorPages.end())
			std::cout << errorPages[statusCode] << std::endl;
		else
			std::cout << "Unknown error" << std::endl;
	}
}
