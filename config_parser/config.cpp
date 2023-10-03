
#include "config.hpp"

Config::Config() {}

Config::~Config() {}

const char	*Config::BracketsNotClosed::what() const throw(){
	return "Brackets for the block are not closed.";
}

const char	*Config::BlocknameNotExisting::what() const throw(){
	return "This blockname doesnt exist for the config file.";
}

const char	*Config::NoSemicolonAtTheEndOfContext::what() const throw(){
	return "The context has no semicolon at the end of it";
}

const char	*Config::FileNotOpen::what() const throw(){
	return "Could not open the config file.";
}

std::vector<std::string>	Config::_tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while (iss >> token)
	{
		if (token[0] == '#')
			break;
        tokens.push_back(token);
	}
	if (tokens[tokens.size() - 1].find_first_of("#") != std::string::npos)
		tokens[tokens.size() - 1] = tokens[tokens.size() - 1].substr(0, tokens[tokens.size() - 1].find_first_of("#"));// maybe + 1
    if (tokens[tokens.size() - 1].find_first_of(';') == std::string::npos)
		throw NoSemicolonAtTheEndOfContext();
    return tokens;
}

bool	Config::_checkEmptyAndComments(std::string &line)
{
	if (line.find_first_not_of(" \t") == std::string::npos)
		return false;
	line = line.substr(line.find_first_not_of(" \t"), line.find_last_not_of(" \t") + 1);
	if (line.empty() || line[0] == '#')
		return false;
	return true;
}

void	Config::_putContext(std::ifstream &nginxConfFile, std::string &line, int i)
{
	while (std::getline(nginxConfFile, line) && line.find('}') == std::string::npos)
	{
		if (!_checkEmptyAndComments(line))
			continue ;
		std::vector<std::string>	tmp = _tokenize(line);
		std::vector<std::string>tmp2(tmp.begin() + 1, tmp.end());
		_confFile[i][line.substr(0, line.find_first_of("{"))][tmp[0]] = tmp2;//maybe + 1		
	}
	if (!line.find('}'))
			throw BracketsNotClosed();
}

void	Config::_serverBlock(std::ifstream &nginxConfFile, std::string &line, int i)
{
	_confFile.push_back(std::map<std::string, std::map<std::string, std::vector<std::string> > >());
	while (std::getline(nginxConfFile, line) && line.find('}') == std::string::npos)
	{
		if (!_checkEmptyAndComments(line))
			continue ;
		if (line.find("location") != std::string::npos)//check location specific method
		{
			_confFile[i][line.substr(0, line.find_first_of("{"))] = std::map<std::string, std::vector<std::string> >();
			_putContext(nginxConfFile, line, i);
		}
		else
		{
			std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator block = _confFile[i].find("nolocation");
			if (block != _confFile[i].end())
				_confFile[i]["nolocation"] = std::map<std::string, std::vector<std::string> >();
			_putContext(nginxConfFile, line, i);
		}
	};
	if (!line.find('}'))
			throw BracketsNotClosed();
}

void	Config::_globalBlock(std::ifstream &nginxConfFile, std::string &line)
{
	while (std::getline(nginxConfFile, line) && line.find('{') == std::string::npos)
	{
		if (!_checkEmptyAndComments(line))
			continue ;
		std::vector<std::string>	tmp = _tokenize(line);
		std::vector<std::string>tmp2(tmp.begin() + 1, tmp.end());
		_globalContext[tmp[0]] = tmp2;  
	};
}

bool	Config::_fileOpen(std::ifstream &nginxConfFile)
{
	if (!nginxConfFile.is_open()) //could be an exception
		return false;
	return true;
}

void	Config::parseConfFile(char *file)
{
    std::ifstream nginxConfFile(file);
	if (!_fileOpen(nginxConfFile))
		throw FileNotOpen();
    std::string currentBlock;
    std::string line;
	for (int i = 0; std::getline(nginxConfFile, line);)
	{
		if (!_checkEmptyAndComments(line))
			continue ;
		else if (line.find("server") != std::string::npos)
			_serverBlock(nginxConfFile, line, i++);
		else if (line.find("{") == std::string::npos)
			_globalBlock(nginxConfFile, line);
		else
			throw BlocknameNotExisting();
	}
	nginxConfFile.close();
}

void	Config::iterateContainer()
{
	  for (size_t i = 0; i < _confFile.size(); ++i) {
        const std::map<std::string, std::map<std::string, std::vector<std::string> > >& innerMap1 = _confFile[i];

        // Iterate through the first map
        for (std::map<std::string, std::map<std::string, std::vector<std::string> > >::const_iterator it1 = innerMap1.begin(); it1 != innerMap1.end(); ++it1) {
            const std::string& key1 = it1->first;
            const std::map<std::string, std::vector<std::string> >& innerMap2 = it1->second;

            // Iterate through the second map
            for (std::map<std::string, std::vector<std::string> >::const_iterator it2 = innerMap2.begin(); it2 != innerMap2.end(); ++it2) {
                const std::string& key2 = it2->first;
                const std::vector<std::string>& vectorOfString = it2->second;

                // Iterate through the vector
                for (size_t j = 0; j < vectorOfString.size(); ++j) {
                    const std::string& str = vectorOfString[j];
                    // Process 'str' here
                    std::cout << "Element: " << str << std::endl;
                }
            }
        }
    }
}