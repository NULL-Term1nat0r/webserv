#ifndef BINARY_HPP
# define BINARY_HPP
# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <map>
#include <cstddef>
#include <cstdint>

class Binary {
	public:
		Binary();
		~Binary();
		void	postRequest(std::string contentType, std::vector<uint8_t> fileData);
		void	cutFileEnd();
		void	cutFileStart();

		void	checkLastChunk(std::vector<uint8_t> &lastChunk, std::string startBoundary);
	private:
		void	_initExtensionMap();
		void	_checkIfFileTypeExisting();
		void	_getBinDataOfFile(std::ofstream &outfile);
		void					_getFileName(const std::string& contentType);
		void					_mainBinary();
		void					_getBoundary();
		std::string							_boundary;
		std::string							_fileName;
		std::string 						_fileType;
		std::map<std::string, std::string>	_fileTypes;
		std::vector<uint8_t>				_requestData;
		bool								_isMultiPart;
		std::string							_request;
};

#endif