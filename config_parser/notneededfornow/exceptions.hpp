#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP
# include <iostream>
# include <string>

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

#endif