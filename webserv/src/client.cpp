#include "../includes/server.hpp"

server::client::client(int clientSocket) :  clientSocket(clientSocket), lastActivity(time(0)), clientRequest(NULL), clientResponse(NULL)  {
}

server::client::~client() {
}

void server::client::executeClientRequest(int buffSize, std::vector<struct pollfd> pollEvents, std::vector<client> &clients){
	std::vector<uint8_t> _request(buffSize);
	recv(this->clientSocket, &_request[0], buffSize, 0);

	if (this->clientRequest == NULL) {
		request newRequest = request(_request);
		std::cout << " bew client request url: " << newRequest.getStringURL() << std::endl;
		std::cout << parsing::vectorToString(_request) << std::endl;
		std::cout << "get cgi method: " << newRequest.getCgi() << std::endl;
		if (newRequest.getGetMethod() && newRequest.getCgi()) {
			std::cout << "create new CgiRequest\n";
			cgiRequest *newCgiRequest = new cgiRequest(_request);
			this->clientRequest = newCgiRequest;
		}
		else if (newRequest.getPostMethod()){
			std::cout << "create new PostRequest\n";
			postRequest *newPostRequest = new postRequest(_request);
			this->clientRequest = newPostRequest;
		}
		else if (newRequest.getGetMethod()){
			std::cout << "create new GetRequest\n";
			getRequest *newGetRequest = new getRequest(_request);
			this->clientRequest = newGetRequest;
		}
		else if (newRequest.getDeleteMethod()){
			deleteRequest *newDeleteRequest = new deleteRequest(_request);
			this->clientRequest = newDeleteRequest;
		}
	}
	if  (dynamic_cast<postRequest*>(static_cast<request*>(this->clientRequest))) {
		std::cout << "post request gets handled\n";
		postRequest *postR = static_cast<postRequest *>(this->clientRequest);
		postR->printPostRequest();
		if (!postR->getAllChunksSent()) {
			try {
				postR->writeBinaryToFile(_request);
			}
			catch (std::exception &e) {
				std::cout << "caught exception of post Request" << std::endl;
			}
			if (postR->getAllChunksSent()) {
				response *newResponse = new response("./html_files/uploadSuccessful.html");
				clientResponse = newResponse;
				delete this->clientRequest;
				this->clientRequest = NULL;
			}
		}
	}
	else if (dynamic_cast<getRequest*>(static_cast<request*>(this->clientRequest))){
		getRequest *get = static_cast<getRequest *>(this->clientRequest);
		response *newResponse = new response(get->getFilePath());
		clientResponse = newResponse;
		delete clientRequest;
		clientRequest = NULL;
	}
	else if (dynamic_cast<deleteRequest*>(static_cast<request*>(this->clientRequest))){
		std::cout << "delete request incoming\n";
		deleteRequest *_delete = static_cast<deleteRequest *>(this->clientRequest);
		response *newResponse = new response("./html_files/deleteSuccessful.html");
		clientResponse = newResponse;
		delete clientRequest;
		clientRequest = NULL;
	}
	else if (dynamic_cast<cgiRequest*>(static_cast<request*>(this->clientRequest))){
		std::cout << "cgi request incoming\n";
		cgiRequest *cgiR = static_cast<cgiRequest *>(this->clientRequest);
		cgiR->executeCgi();
		response *newResponse = new response(cgiR->getFilePath());
		clientResponse = newResponse;
		delete clientRequest;
		clientRequest = NULL;
	}
}

void server::client::executeClientResponse(int buffSize, std::vector<struct pollfd> pollEvents, std::vector<client> &clients){
	std::cout << "execute client response called\n";
	std::cout << "filepath Response: " << this->clientResponse->filePath << std::endl;
	if (this->clientResponse != NULL){
		if (this->clientResponse->_allChunkSent && this->clientResponse->filePath.find("src/tmp_cgi") != std::string::npos) {
			if (this->clientResponse->removeFile(this->clientResponse->filePath.c_str()))
				std::cout << "file removed\n";
			else
				std::cout << "file not removed\n";
		}
		else if (this->clientResponse->_allChunkSent && this->clientResponse->filePath.find("src/tmp_cgi.html") == std::string::npos) {
			std::cout << "all chunks are sent return 0 now\n";
			delete this->clientResponse;
			this->clientResponse = NULL;
		}
		else {
			std::string chunk = this->clientResponse->getChunk(buffSize);
			send(this->clientSocket, &chunk[0], chunk.length(), 0);
		}
	}
}
