#include "../includes/Header.h"


void split(const std::string &s, char delim, std::vector<std::string> &result) {
	std::istringstream iss(s);
	std::string token;
	std::getline(iss, token, delim);
	result.push_back("/");
	while (std::getline(iss, token, delim)) {
		result.push_back(token);
	}
}

std::string getPage(std::vector<std::string> &result) {
	if (result[result.size() - 1].find(".") == std::string::npos)
		return (result[result.size() - 1]);
	else
		return (result[result.size() - 2]);
}

int main()
{

	//neue Logik: check ob file oder directory
	// wenn file dann vorletztes wort
	//bei ordner dann letztes wort
	std::vector<std::string> result;
	std::string s1 = "/upload/haha/picture.jpeg";
	std::string s2 = "/upload/haha";
	std::string s3 = "/upload";

	split(s1, '/', result);
	for (std::vector<std::string>::iterator it = result.begin(); it != result.end(); ++it) {
		std::cout << *it << std::endl;
	}


	return 0;
}