#include "exceptions.hpp"

const char	*BracketsNotClosed::what() const throw(){
	return "Brackets for the block are not closed.";
}

const char	*BlocknameNotExisting::what() const throw(){
	return "This blockname doesnt exist for the config file.";
}

const char	*NoSemicolonAtTheEndOfContext::what() const throw(){
	return "The context has no semicolon at the end of it";
}
