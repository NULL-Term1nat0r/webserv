#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "exceptions.hpp"
#include "server.hpp"

void	removeWhiteSpaces(std::string	&line)
{
	std::string tmp;

	tmp = line;
	line.clear();
    for (std::string::const_iterator it = tmp.begin(); it != tmp.end(); ++it) {
        char c = *it;
        if (c != ' ' && c != '\t')
            line += c;
    }
}

std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while (iss >> token)
	{
		if (token.find_first_of('#') != std::string::npos)
			break;
		removeWhiteSpaces(token);
        tokens.push_back(token);
	}
    if (tokens[tokens.size() - 1][tokens[tokens.size() - 1].size() - 1] != ';')//tokens[tokens.size() - 1].find_first_of(';') == std::string::npos || 
	{
		throw NoSemicolonAtTheEndOfContext();
	}

    return tokens;
}

int blockExists(const std::string currentBlock)//const
{
	if (currentBlock == "http" || currentBlock == "server" || currentBlock == "location /"
		|| currentBlock == "upstream" || currentBlock == "if" || currentBlock == "map" 
		|| currentBlock == "limit_except" || currentBlock == "geo")
		return 0;
	//if check for this special condition and also location
	return 1;
}


void    configTry()
{
    std::ifstream nginxConfFile("nginx.conf");//close //take argv
    if (!nginxConfFile.is_open()) {
        std::cerr << "Error: Could not open nginx.conf." << std::endl;
        return ;
    }
    std::map<std::string, std::map<std::string, std::vector<std::string> > > nginxConfig;
    std::string currentBlock;

    std::string line;
    while (std::getline(nginxConfFile, line))
	{
		if (line.find_first_not_of(" \t") == std::string::npos)
			continue;
        line = line.substr(line.find_first_not_of(" \t"), line.find_last_not_of(" \t") + 1);
		if (line.empty() || line[0] == '#')
            continue;
		else if (line.find('{') != std::string::npos)
		{
            currentBlock = line.substr(0, line.find('{'));
			removeWhiteSpaces(currentBlock);
			std::cout << currentBlock << std::endl;
            // if (blockExists(currentBlock))
            // 	throw BlocknameNotExisting();
            nginxConfig[currentBlock] = std::map<std::string, std::vector<std::string> >();
        }
		else if (line == "}")
		{
			// std::vector<std::string> emptyVector;
			// nginxConfig[currentBlock].insert(std::make_pair("}", emptyVector));
            currentBlock = "";
		}
		else
		{
            std::vector<std::string> tokens = tokenize(line);
            if (tokens.size() >= 2)
			{
				std::vector<std::string>tmp(tokens.begin() + 1, tokens.end());
                nginxConfig[currentBlock][tokens[0]] = tmp;
			}
        }
    }
}

int main()
{
    try
	{
		configTry();
		Server	server;
		//server.getServerData();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Config File Error: " << e.what() << std::endl;
		return 1;
    }
}

//remove whitespaces only before 
//spaces infront of semicolon
//check for comments after ; how to handle
//check if {} are closed
//what to make if some variables are declared in main block out of {}
// can make location / problems
//special parsing for location
//think about the brackets how to check them properly

// for (std::map<std::string, std::map<std::string, std::vector<std::string> > >::const_iterator blockIt = nginxConfig.begin(); blockIt != nginxConfig.end(); ++blockIt)
	// {
   	// 	std::cout << "Block: " << blockIt->first << std::endl;
	//  	const std::map<std::string, std::vector<std::string> >& directives = blockIt->second;
    

		// std::map<std::string, std::vector<std::string> >::const_iterator bracket = blockIt->second.find("}");
		// if (bracket == blockIt->second.end())
		// 	throw BracketsNotClosed();

		// for (std::map<std::string, std::vector<std::string> >::const_iterator directiveIt = directives.begin(); directiveIt != directives.end(); ++directiveIt)
	// 	{
	// 		std::cout << "  " << directiveIt->first << " = ";
	// 		for (size_t i = 0; i != directiveIt->second.size(); i++)
	// 			std::cout << directiveIt->second[i];
	// 		std::cout << std::endl;
	// 	}
	// }