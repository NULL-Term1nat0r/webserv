Request::Request(const std::vector<uint8_t>& clientData):
        _tmp(std::string(clientData.begin(), clientData.end()))
{}

Request::~Request() {}


/* extracts last file of URL and identifies what content it contains
 *  eg. found  ".pdf"  ==>  returns  "application/pdf"          */
std::string Request::getFileContentType(const std::string& url)
{
    if (url.find('.') != std::string::npos)
    {
        size_t startPos = url.find_last_of('.');
        size_t endPos = url.size();

        // from found till end next space:
        std::string fileExtension;

        if (endPos != std::string::npos)
            fileExtension = (url.substr(startPos + 1, endPos - (startPos)));
        else
            fileExtension = (url.substr(startPos));
        std::string contentType = comparerContentType(fileExtension);
        if (contentType == "FAILURE")
            return FAILURE;
        return (contentType);
    }
    return FAILURE;
}







std::string Request::getNewFilename(const std::string& checkFilename, const std::string& uploadFolder)
{
    size_t lastDotPos = checkFilename.rfind('.'); // Find the last dot position

    if (lastDotPos == std::string::npos) // If dot is found
    {
#ifdef LOG
        Logging::log("unexpected Error: could not getNewFilename", 500);
#endif
    }

    std::string filename = checkFilename.substr(0, lastDotPos); // Take substring up to the last dot
    std::string fileExtension = checkFilename.substr(lastDotPos, checkFilename.size());

    int fileCount = 1;

    while (fileExists(filename + " (" + myItoS(fileCount) + ")" + fileExtension, uploadFolder))
        fileCount++;
    return (filename + " (" + myItoS(fileCount) + ")"+ fileExtension);
}


/* only for POST && multipart
 * extracts the filename defined in the header of the body      */
std::string Request::getFileName(const std::string& contentType, const std::string& prevFileName, const std::string& uploadFolder)
{
    if (!prevFileName.empty() && prevFileName.compare(0, 13, "not_found_yet") != 0)
        return prevFileName;    // correct filename was already found

    if (contentType.compare(0, 34, "multipart/form-data") == 0)
    {
        size_t foundPos = _tmp.find("filename=\"");

        if (foundPos != std::string::npos)
        {
            size_t endPos = _tmp.find("\"\r\n", foundPos);
            if (endPos != std::string::npos)
            {
                std::string fileName = _tmp.substr(foundPos + 10, (endPos) - (foundPos + 10));
                if (fileName.rfind('.') == std::string::npos) // no file with .
                    return (FAILURE);
                if (fileExists(fileName, uploadFolder))
                    fileName = getNewFilename(fileName, uploadFolder);

                if (getFileContentType(fileName) == FAILURE)
                    return BAD_CONTENT_TYPE;
                return fileName;
            }
            return (&"tmpFileForSocket_" [ random()]);
        }
        return "not_found_yet";
    }

    return FAILURE; // not failure but we don't consider filename if not POST
}


/* only for POST
 * returns the value as string after Content-Type:      */
std::string Request::getContentType()
{
    size_t foundPos = _tmp.find("Content-Type: ");
    size_t specialStart = _tmp.find("application/x-www-form-urlencoded");

    if (specialStart != std::string::npos)
    {
        size_t specialEnd = _tmp.find("\r\n", specialStart);
        if (specialEnd != std::string::npos)
        {
            std::string specialType = "application/x-www-form-urlencoded";
            return specialType;
        }
    }

    if (foundPos != std::string::npos)
    {
        size_t endPos = _tmp.find(';', foundPos);
        if (endPos != std::string::npos)
        {
            std::string contentType = _tmp.substr(foundPos + 14, endPos - (foundPos + 14));
            return contentType;
        }
    }
    return FAILURE;
}

/* only for POST
 * returns the value as string after Content-Length:      */
int Request::getContentLen()
{
    size_t foundPos = _tmp.find("Content-Length: ") + 16;
    if (foundPos != std::string::npos)
    {
        size_t endPos = _tmp.find('\r', foundPos);
        if (endPos != std::string::npos)
        {
            std::string contentLen = _tmp.substr(foundPos, endPos - (foundPos));
            return atoi(contentLen.c_str());
        }
    }
    return -1;
}

/* only for POST && multipart
 * extracts boundary for multipart      */
std::string Request::getBoundary()
{
    size_t foundPos = _tmp.find("multipart/form-data; boundary=");

    if (foundPos != std::string::npos)
    {
        size_t endPos = _tmp.find('\r', foundPos);
        if (endPos != std::string::npos)
        {
            std::string contentType = _tmp.substr(foundPos + 30, endPos - (foundPos + 30));
            return contentType;
        }
    }
    return FAILURE;
}