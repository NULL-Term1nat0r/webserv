#ifndef SERVER_HPP
# define SERVER_HPP
# include <string>
# include <vector>
# include <map>
# include <iostream>

class Server
{
	public:
		void	getServerData( std::map<std::string, std::map<std::string, std::vector<std::string> > > nginxConfig);
	private:
		std::vector<std::map<std::string, std::map<std::string, std::vector<std::string> > > >	_confFile;
		std::map<std::string, std::vector<std::string> >										_globalContext;
};
#endif
// std::vector<std::map<std::string, std::map<std::string, std::vector<std::string> > > >	_serverData;
//make seperate var for global vars in config file