
#include "binary.hpp"

Binary::Binary() {}

Binary::~Binary() {}

void	Binary::_getBinDataOfFile(std::ofstream &outfile) {

	std::string binData(_requestData.begin(), _requestData.end());
	std::string startBoundary = "--"+_boundary+"\r\n\r\n";  //?
	std::string endBoundary = "\r\n--"+_boundary+"--";
	std::vector<uint8_t>::iterator startPos = _requestData.begin();
	std::vector<uint8_t>::iterator endPos = _requestData.end();
	size_t posStartBoundary = binData.find(startBoundary);
	size_t posEndBoundary = binData.find(endBoundary);
	bool endOfFile = false;

	if (posStartBoundary != std::string::npos) {
		size_t	skipHeader = binData.find("\r\n\r\n", (posStartBoundary + startBoundary.size())) + 4; //?
		if (skipHeader == std::string::npos)
			//error
		startPos += skipHeader;
		if (posEndBoundary != std::string::npos) {
			endPos = _requestData.begin() + posEndBoundary;
			endOfFile = true;
		}
	}
	else if (posEndBoundary != std::string::npos)
	{
		endPos = _requestData.begin() + posEndBoundary;
		endOfFile = true;
	}
	std::vector<uint8_t>::iterator it;
	for (it = startPos; it != endPos; it++)
		outfile << *it;

	//overlook
	if (endOfFile)
		outfile.close();
	//handle data in the response
}



void	Binary::_getFileName(const std::string& contentType)
{
	//if (contentType.compare(0, 34, "multipart/form-data") == 0) {
		size_t startPos = _request.find("filename=\"");
		if (startPos != std::string::npos) {
			size_t endPos = _request.find("\"\r\n", startPos);
			if (endPos != std::string::npos) {
				_fileName = _request.substr(startPos + 10, endPos - startPos + 10);
				if (_fileName.find_last_of('.') == std::string::npos)
					_fileName = ""; //error
				else
					_fileType = _fileName.substr(_fileName.find_last_of('.'), _fileName.size() - _fileName.find_last_of('.'));

				//if (fileExists(fileName, uploadFolder))
				//	fileName = getNewFilename(fileName, uploadFolder);
			}
		}
	// }
}




void	Binary::_getBoundary()
{
	size_t	startPos = _request.find("multipart/form-data; boundary=");
	if (startPos != std::string::npos) {
		size_t	endPos = _request.find('\r', startPos);
		if (endPos != std::string::npos)
			_boundary = _request.substr(startPos + 30, endPos - (startPos + 30));
	}
	else
		_boundary = "not_found_yet";//or something else
}

void	Binary::_mainBinary()
{
	_request.assign(_requestData.begin(), _requestData.end());
	_getBoundary();
	_getFileName("multipart/form-data");
	//getfilename and type: check if existing

	_getBinDataOfFile();

	//handle data in the response
}

void	Binary::postRequest(std::string contentType, std::vector<uint8_t> fileData)
{
	_isMultiPart = false;
	if (contentType == "multipart/form-data") {
		_mainBinary();
		_requestData = fileData;
		_isMultiPart = true;
	}
	else
		_fileName = "tmpFile.txt";
}

int main()
{
	Binary bin;
	bin.postRequest("multipart/form-data");
	return 0;
}