std::string Response::getContentType()
{
    if (_info._url.find('.') != std::string::npos)
    {
        std::string fileExtension;
        size_t startPos = _info._url.find_last_of('.');
        size_t endPos = _info._url.size();

        if (endPos != std::string::npos)
            fileExtension = _info._url.substr(startPos + 1, endPos - (startPos));
        else
            fileExtension = _info._url.substr(startPos);
        std::string contentType = comparerContentType(fileExtension);
        if (contentType == FAILURE)
            mySend(NOT_FOUND);
        return contentType;
    }
}

std::vector<uint8_t> Response::readFile(const std::string &fileName)
{
    if (_info._filePos > 0)
    {
        sendShittyChunk(fileName);
        return static_cast<std::vector<uint8_t> >(0);
    }
    std::ifstream file;
    file.open(fileName.c_str(), std::ios::binary);

    if (!file)
    {
#ifdef LOG
        Logging::log("Failed to open file: " + fileName, 500);
#endif
        return static_cast<std::vector<uint8_t> >(0);
    }

    // Read the file content into a vector
    std::vector<uint8_t> content(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
    );

    if (_info._myHTTPMethod == M_GET && content.size() > SEND_CHUNK_SIZE)
    {
        _info._fileContentType = getContentType();

        std::string header = "HTTP/1.1 200 " +
                             ErrorResponse::getErrorMessage(200) + "\r\n"
                                                                   "Content-Type: "+_info._fileContentType + "\r\n"
                                                                                                             "Set-Cookie: session_token="+g_cookieName+"; SameSite=None; Secure; HttpOnly\r\n"
                                                                                                                                                       "Content-Length: " + myItoS(content.size()) + "\r\n"
                                                                                                                                                                                                     "Connection: keep-alive\r\n"
                                                                                                                                                                                                     "\r\n";
#ifdef LOG
        Logging::log("send Data:\n" + header, 200);
#endif

        char buffer[SEND_CHUNK_SIZE];
        file.seekg(0);
        file.read(buffer, SEND_CHUNK_SIZE);

        std::string response = header.append(buffer, SEND_CHUNK_SIZE);
        int len = response.size();

        int check = send(_info._clientSocket, response.data(), len, MSG_DONTWAIT);
        if (check <= 0)
        {
#ifdef LOG
            Logging::log("Failed to send Data to Client", 500);
#endif
            file.close();
#ifdef INFO
            std::cout << BOLDRED << "Error: Failed to send Data to Client" << RESET << std::endl;
#endif
            return static_cast<std::vector<uint8_t> >(0);
        }

        _info._filePos = file.tellg();
        _info._isChunkedFile = true;
        file.close();
        return static_cast<std::vector<uint8_t> >(0);
    }

    _info._isChunkedFile = false;
    file.close();
    return content;
}



// ^ ^ ^  GET   ^ ^ ^

// --- --- --- --- ---

// v v v  POST  v v v



bool Response::uploadFile(const std::string& contentType, const std::string& boundary, std::ofstream *outfile)
{
    if (contentType == "multipart/form-data")
        return saveRequestToFile(*outfile, boundary);
    else if (contentType == "application/x-www-form-urlencoded")
        isCgi();
    return false;
}

bool Response::saveRequestToFile(std::ofstream &outfile, const std::string& boundary)
{
#ifdef INFO
    std::cout << BLU " . . . Received Data  --  POST  " <<_info._url<< "" << RESET << std::endl;
#endif
#ifdef LOG
    Logging::log("Received Data  --  POST  " + _info._url, 200);
#endif

    std::string convert(_info._postInfo._input.begin(), _info._postInfo._input.end());
    std::string startBoundary = "--"+boundary+"\r\n";
    std::string endBoundary = "\r\n--"+boundary+"--";
    std::vector<uint8_t>::iterator startPos69 = _info._postInfo._input.begin();
    std::vector<uint8_t>::iterator endPos69 = _info._postInfo._input.end();
    size_t posStartBoundary = convert.find(startBoundary);
    size_t posEndBoundary = convert.find(endBoundary);
    bool endOfFile = false;

    if NO_DATA_TO_UPLOAD
        return true;

    if (posStartBoundary != std::string::npos)  // cut header and put stuff afterward to outfile
    {
        size_t bodyPos = convert.find("\r\n\r\n", (posStartBoundary + startBoundary.size() + 2)) + 4;
        if (bodyPos == std::string::npos)   // not the beginning of body content
            return true;
        startPos69 += bodyPos;
        if (posEndBoundary != std::string::npos)    // found last boundary
        {
            endOfFile = true;
            endPos69 = _info._postInfo._input.begin() + posEndBoundary;
        }
    }
    else if (posEndBoundary != std::string::npos)    // found last boundary
    {
        endPos69 = _info._postInfo._input.begin() + posEndBoundary;
        endOfFile = true;
    }
    std::vector<uint8_t>::iterator it;
    for (it = startPos69; it != endPos69; it++)
        outfile << *it;

    if (endOfFile)
    {
        outfile.close();
        mySend(getRightResponse());
        return false;
    }
    return true;
}
