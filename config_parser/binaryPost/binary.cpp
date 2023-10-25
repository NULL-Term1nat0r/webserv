struct postInfo
{
    int                     _contentLen;
    std::string             _filename;
    std::string             _boundary;
    std::ofstream*          _outfile;
    std::vector<uint8_t>    _input;
};



void ConnectClients::initClientInfo(configParser& config)
{
    std::vector<uint8_t> input = _byteVector;
    int clientSocket = _fdPortList._fds[_x].fd;

    std::map<int, clientInfo>::iterator rm = _clientInfo.find(clientSocket);
    if (rm != _clientInfo.end() && rm->second._filePos > 0)
        return;
    if (rm != _clientInfo.end() && !rm->second._isMultiPart)
        _clientInfo.erase(rm);

    std::map<int, clientInfo>::iterator it = _clientInfo.find(clientSocket);
    if (it == _clientInfo.end())   // IF NOT INITTED YET
    {
        clientInfo initNewInfo;
        Request request(input);


        initNewInfo._url = config.getUrl();
        initNewInfo._fileContentType = request.getFileContentType(initNewInfo._url);
        initNewInfo._contentType = request.getContentType();
        initNewInfo._isMultiPart = false;


        initNewInfo._filePos = 0;
        if (initNewInfo._myHTTPMethod == M_POST)
        {
            initNewInfo._postInfo._input = input;

            initNewInfo._postInfo._filename = request.getFileName(initNewInfo._contentType, initNewInfo._postInfo._filename, UPLOAD_FOLDER);
            std::string temp_filename = UPLOAD_FOLDER + initNewInfo._postInfo._filename;
            initNewInfo._postInfo._outfile = new std::ofstream (temp_filename.c_str(), std::ofstream::out | std::ofstream::app | std::ofstream::binary);
            chmod((UPLOAD_FOLDER+initNewInfo._postInfo._filename).c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // no execution permission for user
            if (initNewInfo._contentType == "multipart/form-data")
            {
                initNewInfo._isMultiPart = true;
                initNewInfo._postInfo._boundary = request.getBoundary();
            }
            else
                initNewInfo._postInfo._filename = "tmpFile.txt";
        }
        _clientInfo[clientSocket] = initNewInfo;
    }
    else if (_isMultiPart)   // only for multipart!!
    {
        Request request(input);
        std::string oldFilename = _postInfo._filename;
        _postInfo._input = input;
        _postInfo._filename = request.getFileName(it->second._contentType, it->second._postInfo._filename, UPLOAD_FOLDER);
        if (oldFilename.compare(0, 13, "not_found_yet") == 0 && _postInfo._filename.compare(0, 13, "not_found_yet") != 0)
            rename((UPLOAD_FOLDER+oldFilename).c_str(), (UPLOAD_FOLDER+_postInfo._filename).c_str());
    }
}


