
#include "binary.hpp"

Binary::Binary() {}

Binary::~Binary() {}



//if end boundary not in the _requestData continue adding everything to the file if it is in the _requestData stop adding and close the file
//parse outputfile for the endboundary
//if endboundary cant be found after last chunk either error or close the file


//store first chunk and then second put them together and then parse them for the endboundary
//if not inside delete first chunk and add seccond and third chunk together and parse them for the endboundary and so on

// class Client {
//     std::vector<uint8_t>	_firstChunk;
//     std::vector<uint8_t>	_secondChunk;
//     std::vector<uint8_t>	_fullChunk;
//     std::string				_endBoundary;
// };


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
		if (posEndBoundary != std::string::npos) { // for not full file chunks needed
			endPos = _requestData.begin() + posEndBoundary;
			endOfFile = true;
		}
	}
	else if (posEndBoundary != std::string::npos)
	{
		endPos = _requestData.begin() + posEndBoundary;
		endOfFile = true;
	}

    //maybe special condition when to use it
	std::vector<uint8_t>::iterator it;
	for (it = startPos; it != endPos; it++)
		outfile << *it;

	//overlook
	//give it to the response
	if (endOfFile)
		outfile.close();
	//handle data in the response
}

void	Binary::_initExtensionMap() {
		_fileTypes.insert(std::make_pair(".avif", "image/avif"));
        _fileTypes.insert(std::make_pair(".bmp", "image/bmp"));
        _fileTypes.insert(std::make_pair(".jpeg", "image/jpeg"));
        _fileTypes.insert(std::make_pair(".jpg", "image/jpeg"));
        _fileTypes.insert(std::make_pair(".gif", "image/gif"));
        _fileTypes.insert(std::make_pair(".ico", "image/vnd.microsoft.icon"));
        _fileTypes.insert(std::make_pair(".png", "image/png"));
        _fileTypes.insert(std::make_pair(".svg", "image/svg+xml"));
        _fileTypes.insert(std::make_pair(".tiff", "image/tiff"));
        _fileTypes.insert(std::make_pair(".tif", "image/tiff"));
        _fileTypes.insert(std::make_pair(".webp", "image/webp"));

        _fileTypes.insert(std::make_pair(".mp4", "video/mp4"));
        _fileTypes.insert(std::make_pair(".avi", "video/x-msvideo"));
        _fileTypes.insert(std::make_pair(".mpeg", "video/mpeg"));
        _fileTypes.insert(std::make_pair(".ogv", "video/ogg"));
        _fileTypes.insert(std::make_pair(".ts", "video/mp2t")); // cant even open (mac)
        _fileTypes.insert(std::make_pair(".webm", "video/webm"));
        _fileTypes.insert(std::make_pair(".3gp", "video/3gpp"));
        _fileTypes.insert(std::make_pair(".3g2", "video/3gpp2"));

        _fileTypes.insert(std::make_pair(".css", "text/css"));
        _fileTypes.insert(std::make_pair(".csv", "text/csv"));
        _fileTypes.insert(std::make_pair(".html", "text/html"));
        _fileTypes.insert(std::make_pair(".htm", "text/html"));
        _fileTypes.insert(std::make_pair(".ics", "text/calendar"));
        _fileTypes.insert(std::make_pair(".js", "text/javascript"));
        _fileTypes.insert(std::make_pair(".mjs", "text/javascript"));
        _fileTypes.insert(std::make_pair(".txt", "text/plain"));
        _fileTypes.insert(std::make_pair(".md", "text/plain"));

        _fileTypes.insert(std::make_pair(".abw", "application/x-abiword")); // dunno how to download
        _fileTypes.insert(std::make_pair(".arc", "application/x-freearc")); // dunno how to download
        _fileTypes.insert(std::make_pair(".azw", "application/vnd.amazon.ebook")); // dunno how to download
        _fileTypes.insert(std::make_pair(".bin", "application/octet-stream"));
        _fileTypes.insert(std::make_pair(".gz", "application/gzip"));
        _fileTypes.insert(std::make_pair(".json", "application/json"));
        _fileTypes.insert(std::make_pair(".pdf", "application/pdf"));
        _fileTypes.insert(std::make_pair(".doc", "application/msword"));
        _fileTypes.insert(std::make_pair(".docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"));
        _fileTypes.insert(std::make_pair(".bz", "application/x-bzip"));
        _fileTypes.insert(std::make_pair(".bz2", "application/x-bzip2"));
        _fileTypes.insert(std::make_pair(".cda", "application/x-cdf"));
        _fileTypes.insert(std::make_pair(".csh", "application/x-csh"));
        _fileTypes.insert(std::make_pair(".eot", "application/vnd.ms-fontobject"));
        _fileTypes.insert(std::make_pair(".epub", "application/epub+zip"));
        _fileTypes.insert(std::make_pair(".jar", "application/java-archive"));
        _fileTypes.insert(std::make_pair(".jsonld", "application/ld+json"));
        _fileTypes.insert(std::make_pair(".mpkg", "application/vnd.apple.installer+xml"));
        _fileTypes.insert(std::make_pair(".odp", "application/vnd.oasis.opendocument.presentation"));
        _fileTypes.insert(std::make_pair(".ods", "application/vnd.oasis.opendocument.spreadsheet"));
        _fileTypes.insert(std::make_pair(".odt", "application/vnd.oasis.opendocument.text"));
        _fileTypes.insert(std::make_pair(".ogx", "application/ogg"));
        _fileTypes.insert(std::make_pair(".php", "application/x-httpd-php"));
        _fileTypes.insert(std::make_pair(".ppt", "application/vnd.ms-powerpoint"));
        _fileTypes.insert(std::make_pair(".pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"));
        _fileTypes.insert(std::make_pair(".rar", "application/vnd.rar"));
        _fileTypes.insert(std::make_pair(".rtf", "application/rtf"));
        _fileTypes.insert(std::make_pair(".sh", "application/x-sh"));
        _fileTypes.insert(std::make_pair(".tar", "application/x-tar"));
        _fileTypes.insert(std::make_pair(".vsd", "application/vnd.visio"));
        _fileTypes.insert(std::make_pair(".xhtml", "application/xhtml+xml"));
        _fileTypes.insert(std::make_pair(".xls", "application/vnd.ms-excel"));
        _fileTypes.insert(std::make_pair(".xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"));
        _fileTypes.insert(std::make_pair(".xml", "application/xml"));
        _fileTypes.insert(std::make_pair(".xul", "application/vnd.mozilla.xul+xml"));
        _fileTypes.insert(std::make_pair(".zip", "application/zip"));
        _fileTypes.insert(std::make_pair(".7z", "application/x-7z-compressed"));
		_fileTypes.insert(std::make_pair(".webmanifest", "application/manifest+json"));



        _fileTypes.insert(std::make_pair(".otf", "font/otf"));
        _fileTypes.insert(std::make_pair(".ttf", "font/ttf"));
        _fileTypes.insert(std::make_pair(".woff", "font/woff"));
        _fileTypes.insert(std::make_pair(".woff2", "font/woff2"));


        _fileTypes.insert(std::make_pair(".aac", "audio/aac"));
        _fileTypes.insert(std::make_pair(".mid", "audio/midi"));
        _fileTypes.insert(std::make_pair(".midi", "audio/midi"));
        _fileTypes.insert(std::make_pair(".mid", "audio/x-midi"));
        _fileTypes.insert(std::make_pair(".midi", "audio/x-midi"));
        _fileTypes.insert(std::make_pair(".mp3", "audio/mpeg"));
        _fileTypes.insert(std::make_pair(".oga", "audio/ogg"));
        _fileTypes.insert(std::make_pair(".opus", "audio/opus"));
        _fileTypes.insert(std::make_pair(".wav", "audio/wav"));
        _fileTypes.insert(std::make_pair(".weba", "audio/webm"));

		// CGI
        _fileTypes.insert(std::make_pair(".py", ".py"));
        _fileTypes.insert(std::make_pair(".pl", ".pl"));
}

void	Binary::_checkIfFileTypeExisting() {
	if (_fileTypes.empty())
		_initExtensionMap();
	std::map<std::string, std::string>::iterator _typeFound = _fileTypes.find(_fileType); 
	if (_typeFound != _fileTypes.end())
		_fileType = _typeFound->second;
	_fileType = "not found";
}



void	Binary::_getFileName(const std::string& contentType)
{
    size_t startPos = _request.find("filename=\"");
    if (startPos != std::string::npos) {
        size_t endPos = _request.find("\"\r\n", startPos);
        if (endPos != std::string::npos) {
            _fileName = _request.substr(startPos + 10, endPos - startPos + 10);
            if (_fileName.find_last_of('.') == std::string::npos)
                _fileName = ""; //error
            else
                _fileType = _fileName.substr(_fileName.find_last_of('.'), _fileName.size() - _fileName.find_last_of('.'));
            _checkIfFileTypeExisting();
            if (_fileType != "not found")//change that
                _fileName = _fileType + _fileName;
            else
                _fileName = ""; //error
        }
    }
    else
        _fileName = ""; //error
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
		_fileName = "tmpFile.txt";// or html or something else check!!!!
}

int main()
{
	Binary bin;
	bin.postRequest("multipart/form-data");
	return 0;
}