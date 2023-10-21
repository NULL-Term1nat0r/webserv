#ifndef BINARY_HPP
# define BINARY_HPP
# include <iostream>
# include <string>
# include <fstream>
# include <vector>

class Binary {
	public:
		Binary();
		~Binary();
		void	postRequest(std::string contentType, std::vector<uint8_t> fileData);
	private:
		void	_getBinDataOfFile(std::ofstream &outfile);
		void					_getFileName(const std::string& contentType);
		void					_mainBinary();
		void					_getBoundary();
		std::string				_boundary;
		std::string				_fileName;
		std::string 			_fileType;
		std::vector<uint8_t>	_requestData;
		bool					_isMultiPart;
		std::string				_request;
};

#endif