
#include "server.hpp"

void	Server::getServerData(std::map<std::string, std::map<std::string, std::vector<std::string> > > nginxConfig)
{
	for (std::map<std::string, std::map<std::string, std::vector<std::string> > >::const_iterator blockIt = nginxConfig.begin(); blockIt != nginxConfig.end(); ++blockIt)
	{
	 	const std::map<std::string, std::vector<std::string> >& directives = blockIt->second;
		for (std::map<std::string, std::vector<std::string> >::const_iterator directiveIt = directives.begin(); directiveIt != directives.end(); ++directiveIt)
		{
			std::map<std::string, std::vector<std::string> >::const_iterator bracket = blockIt->second.find("}");
		// if (bracket == blockIt->second.end())
		// 	throw BracketsNotClosed();
			_serverData[directiveIt->first] = directiveIt->second;
		}
	}
}