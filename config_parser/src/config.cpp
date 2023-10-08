
#include "../inc/config.hpp"

Config::Config() {}

Config::~Config() {}

const char	*Config::BracketsNotClosed::what() const throw() {
	return "Brackets for the block are not closed.";
}

const char	*Config::BlocknameNotExisting::what() const throw() {
	return "This blockname doesnt exist for the config file.";
}

const char	*Config::NoSemicolonAtTheEndOfContext::what() const throw() {
	return "The context has no semicolon at the end of it";
}

const char	*Config::FileNotOpen::what() const throw(){
	return "Could not open the config file.";
}

const char	*Config::LocationAlreadyExists::what() const throw() {
	return "Location already exists.";
}

std::vector<std::map<std::string, std::map<std::string, std::vector<std::string> > > >	Config::getConfFile() const {
	return _confFile;
}
	
std::map<std::string, std::vector<std::string> >	Config::getGlobalContext() const {
	return _globalContext;
}

std::vector<std::vector<std::string> >	Config::getLocations() const {
	return _locations;
}

std::vector<std::string>	Config::_tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while (iss >> token) {
		if (token[0] == '#')
			break;
        tokens.push_back(token);
	}
	if (tokens[tokens.size() - 1].find_first_of("#") != std::string::npos)
		tokens[tokens.size() - 1] = tokens[tokens.size() - 1].substr(0, tokens[tokens.size() - 1].find_first_of("#"));
	if (tokens[tokens.size() - 1].find_first_of(';') == std::string::npos)
		throw NoSemicolonAtTheEndOfContext();
    return tokens;
}

bool	Config::_checkEmptyAndComments(std::string &line) {
	if (line.find_first_not_of(" \t") == std::string::npos)
		return false;
	line = line.substr(line.find_first_not_of(" \t"), line.find_last_not_of(" \t") + 1);
	if (line.empty() || line[0] == '#')
		return false;
	return true;
}

void	Config::_putContext(std::ifstream &nginxConfFile, std::string &line, int i, std::string prevLine) {
	while (std::getline(nginxConfFile, line) && line.find('}') == std::string::npos && line.find('{') == std::string::npos) {
		if (!_checkEmptyAndComments(line))
			continue ;
		std::vector<std::string>	tmp = _tokenize(line);
		std::vector<std::string>tmp2(tmp.begin() + 1, tmp.end());
		_confFile[i][prevLine.substr(0, prevLine.find_first_of("{"))][tmp[0]] = tmp2;
	}
	if (!line.find('}'))
			throw BracketsNotClosed();
}

bool	Config::_locationExists(std::string line, int i) {
	std::vector<std::string>::iterator it = std::find(_locations[i].begin(), _locations[i].end(), line);
    if (it == _locations[i].end()) {
		_locations[i].push_back(line);
		return false;
	}
	return true;
}

void	Config::_removeWhitespace(std::string& line) {
    std::string::iterator it = line.begin();
    while (it != line.end()) {
        if (*it == ' ' || *it == '\t' || *it == '\n' || *it == '\r' || *it == '\f' || *it == '\v')
            it = line.erase(it);
		else
            ++it;
    }
}

void	Config::_handleLocation(std::ifstream &nginxConfFile, std::string &line, int i) {
	_removeWhitespace(line);
	if (_locationExists(line.substr(0, line.find_first_of("{")), i))
		throw LocationAlreadyExists();
	_confFile[i][line.substr(0, line.find_first_of("{"))] = std::map<std::string, std::vector<std::string> >();
	_putContext(nginxConfFile, line, i, line);
}

void	Config::_handleNoLocation(std::ifstream &nginxConfFile, std::string &line, int i) {
	if (_locationExists("noLocation", i))
		_confFile[i]["noLocation"] = std::map<std::string, std::vector<std::string> >();
	_putContext(nginxConfFile, line, i, "noLocation");
}

void	Config::_serverBlock(std::ifstream &nginxConfFile, std::string &line, int i) {
	_locations.push_back(std::vector<std::string>());
	_confFile.push_back(std::map<std::string, std::map<std::string, std::vector<std::string> > >());
	while ((line.find('{') != std::string::npos && _checkEmptyAndComments(line)) || (std::getline(nginxConfFile, line) && line.find('}') == std::string::npos) || !_checkEmptyAndComments(line)) {
		if (!_checkEmptyAndComments(line))
			continue ;
		if (line.find("location") == std::string::npos && line.find("server") == std::string::npos && line.find('{') != std::string::npos)
			throw BlocknameNotExisting();
		if (line.find("location") != std::string::npos)
			_handleLocation(nginxConfFile, line, i);
		else
			_handleNoLocation(nginxConfFile, line, i);
	}
	if (line.find('}') == std::string::npos || !_checkEmptyAndComments(line))
			throw BracketsNotClosed();
}

void	Config::_globalBlock(std::ifstream &nginxConfFile, std::string &line) {
	do {
		if (line.find('}') != std::string::npos || line.find('{') != std::string::npos)
			break ;
		if (!_checkEmptyAndComments(line))
			continue ;
		std::vector<std::string>	tmp = _tokenize(line);
		std::vector<std::string>tmp2(tmp.begin() + 1, tmp.end());
		_globalContext[tmp[0]] = tmp2;  
    } while (std::getline(nginxConfFile, line) && line.find('{') == std::string::npos);
}

bool	Config::_fileOpen(std::ifstream &nginxConfFile) {
	if (!nginxConfFile.is_open())
		return false;
	return true;
}

void	Config::parseConfFile(char *file) {
    std::ifstream nginxConfFile(file);
	if (!_fileOpen(nginxConfFile))
		throw FileNotOpen();
    std::string currentBlock;
    std::string line;
	for (int i = 0; (line.find("server") != std::string::npos && _checkEmptyAndComments(line)) || std::getline(nginxConfFile, line);) {
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













// void	Config::iterateContainer()
// {
// 	std::string partition(50, '-');
	
// 	std::cout << partition << std::endl;
// 	std::cout << "_confFile\n";
// 	std::cout << partition << std::endl;
// 	for (const auto& outerMap : _confFile) {
//         // Iterate through the outer map
//         for (const auto& outerPair : outerMap) {
//             const std::string& outerKey = outerPair.first;
//             const std::map<std::string, std::vector<std::string> >& innerMap = outerPair.second;

//             // Print outer map key and values
//            std::cout << "Outer Key: " << outerKey << std::endl;

//             // Iterate through the inner map
//             for (const auto& innerPair : innerMap) {
//                 const std::string& innerKey = innerPair.first;
//                 const std::vector<std::string>& innerValue = innerPair.second;

//                 // Print inner map key and values
//                 std::cout << innerKey << std::endl;
//                 std::cout << "Inner Values:" << std::endl;

//                 // Iterate through the inner vector
//                 for (const std::string& value : innerValue) {
//                     std::cout << value << std::endl;
//                 }
//             }
//         }
//     }
// 	std::cout << partition << std::endl;
// 	std::cout << "_globalContext\n";
// 	std::cout << partition << std::endl;
// 	for (const auto& pair : _globalContext) {
// 		const std::string& key = pair.first;
// 		const std::vector<std::string>& values = pair.second;

// 		std::cout << "Key: " << key << std::endl;
// 		std::cout << "Values:" << std::endl;

// 		// Iterate through the vector of values
// 		for (const std::string& value : values) {
// 			std::cout << "  " << value << std::endl;
// 		}
// 	}
// 	std::cout << partition << std::endl;
// 	std::cout << "_loactions\n";
// 	std::cout << partition << std::endl;
// 	for (int i = 0; i < _locations.size(); i++) {
// 		for (int j = 0; j <_locations[i].size(); j++)
// 			std::cout << _locations[i][j] << std::endl;
// 	}
// }
