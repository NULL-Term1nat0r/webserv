
#include "binary.hpp"

Binary::Binary() {}

Binary::~Binary() {}

void	Binary::_getBinDataOfFile(std::ofstream &outfile) {

	std::string binData(_requestData.begin(), _requestData.end());
	std::string startBoundary = "--"+_boundary+"\r\n\r\n";
	std::string endBoundary = "\r\n--"+_boundary+"--";
	std::vector<uint8_t>::iterator startPos = _requestData.begin();
	std::vector<uint8_t>::iterator endPos = _requestData.end();
	size_t posStartBoundary = binData.find(startBoundary);
	size_t posEndBoundary = binData.find(endBoundary);
	//bool endOfFile = false;

	if (posStartBoundary != std::string::npos) {
		size_t	skipHeader = binData.find("\r\n\r\n", (posStartBoundary + startBoundary.size())) + 4;
		//if (bodyPos == std::string::npos)
		//	return true;
		startPos += skipHeader;
		if (posEndBoundary != std::string::npos) {
			endPos = _requestData.begin() + posEndBoundary;
			endoffile = true;
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
	{
		outfile.close();
		mySend(getRightResponse());
		return false;
	}
	return true;
}



void	Binary::_getFileName(const std::string& contentType)
{
	if (contentType.compare(0, 34, "multipart/form-data") == 0) {
		size_t startPos = _request.find("filename=\"");
		if (startPos != std::string::npos) {
			size_t endPos = _request.find("\"\r\n", startPos);
			if (endPos != std::string::npos) {
				_fileName = _request.substr(startPos + 10, endPos - startPos + 10);
				if (_fileName.rfind('.') == std::string::npos)
					_filename = ""; //error
				else
					_fileType = _filename.substr(_filename.rfind('.'), _filename.size() - _filename.rfind('.'));

				//if (fileExists(fileName, uploadFolder))
				//	fileName = getNewFilename(fileName, uploadFolder);


			}
			//return (&"tmpFileForSocket_" [ random()]);
		}
	}
}




void	Binary::_getBoundary()
{
	size_t	startPos = _request.find("multipart/form-data; boundary=");
	if (startPos != std::string::npos) {
		size_t	endPos = _request.find('\r', startPos);
		if (endPos != std::string::npos)
			return _request.substr(startPos + 30, endPos - (startPos + 30));
	}
	else
		_boundary = "not_found_yet";//or something else
}

void	Binary::_mainBinary()
{
	//_request(_requestData.begin(), requestData.end());
	_getBoundary();
	_getFileName("multipart/form-data");
	//getfilename and type: check if existing

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
		_filename = "tmpFile.txt";
}

int main()
{
	Binary bin;
	bin.postRequest("multipart/form-data");
	return 0;
}