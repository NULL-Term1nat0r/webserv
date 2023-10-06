#ifndef CONFIG_HPP
# define CONFIG_HPP
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>

class Config
{
	public:
		Config();
		~Config();
		void	parseConfFile(char *file);
		class BracketsNotClosed : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		class BlocknameNotExisting : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		class NoSemicolonAtTheEndOfContext : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		class FileNotOpen : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class LocationAlreadyExists : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
		void	iterateContainer();
	private:
		bool	_locationExists(std::string line, int i);

		bool	_fileOpen(std::ifstream &nginxConfFile);
		void	_globalBlock(std::ifstream &nginxConfFile, std::string &line);
		bool	_checkEmptyAndComments(std::string &line);
		void	_serverBlock(std::ifstream &nginxConfFile, std::string &line, int i);
		void	_putContext(std::ifstream &nginxConfFile, std::string &line, int i);
		std::vector<std::string> _tokenize(const std::string& line);
		std::vector<std::map<std::string, std::map<std::string, std::vector<std::string> > > >	_confFile;
		std::map<std::string, std::vector<std::string> >										_globalContext;
};

#endif