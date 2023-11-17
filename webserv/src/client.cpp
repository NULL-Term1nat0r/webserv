#include "../includes/server.hpp"

server::client::client(int clientSocket, serverConf &serverConfig, int serverIndex) : serverConfig(serverConfig), serverIndex(serverIndex), clientSocket(clientSocket) {
	this->lastActivity = time(0);
	this->clientGetRequest = NULL;
	this->clientPostRequest = NULL;
	this->clientDeleteRequest = NULL;
	this->clientCgiRequest = NULL;
	this->clientResponse = NULL;

}

server::client::~client() {
}

void server::client::executeClientRequest(){
	std::vector<uint8_t> _request(serverConfig._buffSize);
	recv(this->clientSocket, &_request[0], serverConfig._buffSize, 0);

	createNewRequest(_request);
	try {
		if (checkGetRequest(_request))
			return;
		else if (checkPostRequest(_request))
			return;
		else if (checkDeleteRequest(_request))
			return;
		else if (checkCgiRequest(_request))
			return;
		else
			return;
	}
	catch (std::exception &e) {
		std::cout << "caught exception of clientRequest" << std::endl;
	}
}

bool server::client::checkPostRequest(std::vector<uint8_t> _request) {
	if  (this->clientPostRequest != NULL) {
		std::cout << "post request gets handled\n";
		clientPostRequest->printPostRequest();
		if (!clientPostRequest->getAllChunksSent()) {
			try {
				clientPostRequest->writeBinaryToFile(_request);
			}
			catch (std::exception &e) {
				std::cout << "caught exception of post Request" << std::endl;
			}
			if (clientPostRequest->getAllChunksSent()) {
				response *newResponse = new response("./html_files/uploadSuccessful.html", 201);
				clientResponse = newResponse;
				delete this->clientPostRequest;
				this->clientPostRequest = NULL;
			}
		}
		return true;
	}
	return false;
}

bool server::client::checkGetRequest(std::vector<uint8_t> _request) {
	if (this->clientGetRequest != NULL) {
		std::cout << "address of redirection boolean: " << &clientGetRequest->redirection << std::endl;

		if (clientGetRequest->getRedirection()) {
			std::cout << "redirection request incoming\n";
			response *newResponse = new response(clientGetRequest->getFilePath(), 301);
			clientResponse = newResponse;
			delete clientGetRequest;
			clientGetRequest = NULL;
			return true;
		}
		response *newResponse = new response(clientGetRequest->getFilePath(), 200);
		clientResponse = newResponse;
		delete clientGetRequest;
		clientGetRequest = NULL;
		return true;
	}
	return false;
}

bool server::client::checkDeleteRequest(std::vector<uint8_t> _request) {
	if (this->clientDeleteRequest != NULL) {
		std::cout << "delete request incoming\n";
		response *newResponse = new response("./html_files/deleteSuccessful.html", 200);
		clientResponse = newResponse;
		delete clientDeleteRequest;
		clientDeleteRequest = NULL;
		return true;
	}
	return false;
}

bool server::client::checkCgiRequest(std::vector<uint8_t> _request) {
	if (this->clientCgiRequest != NULL) {
		std::cout << "cgi request incoming\n";
		clientCgiRequest->executeCgi();

		response *newResponse = new response(clientCgiRequest->getFilePath(), 200);
		std::cout << "cgi response file path: " << newResponse->filePath << std::endl;
		clientResponse = newResponse;
		delete clientCgiRequest;
		clientCgiRequest = NULL;
		return true;
	}
	return false;
}

void server::client::createNewRequest(std::vector<uint8_t> _request){

	if (this->clientGetRequest == NULL && this->clientPostRequest == NULL && this->clientDeleteRequest == NULL && this->clientCgiRequest == NULL) {
		request newRequest = request(_request, serverConfig, serverIndex);
		std::cout << " new client request url: " << newRequest.getStringURL() << std::endl;
		std::cout << parsing::vectorToString(_request) << std::endl;
		std::cout << "get cgi method: " << newRequest.getCgi() << std::endl;
		if (newRequest.getGetMethod() && newRequest.getCgi()) {
			std::cout << "create new CgiRequest\n";
			cgiRequest *newCgiRequest = new cgiRequest(_request, serverConfig, serverIndex);
			this->clientCgiRequest = newCgiRequest;
		}
		else if (newRequest.getPostMethod()){
			std::cout << "create new PostRequest\n";
			postRequest *newPostRequest = new postRequest(_request, serverConfig, serverIndex);
			this->clientPostRequest= newPostRequest;
		}
		else if (newRequest.getGetMethod()){
			std::cout << "create new GetRequest\n";
			getRequest *newGetRequest = new getRequest(_request, serverConfig, serverIndex);
			this->clientGetRequest = newGetRequest;
		}
		else if (newRequest.getDeleteMethod()){
			deleteRequest *newDeleteRequest = new deleteRequest(_request, serverConfig, serverIndex);
			this->clientDeleteRequest = newDeleteRequest;
		}
	}
}

void server::client::executeClientResponse(){
	std::cout << "execute client response called\n";
	std::cout << "filepath Response: " << this->clientResponse->filePath << std::endl;
	if (this->clientResponse != NULL){
		if (this->clientResponse->_allChunkSent && this->clientResponse->filePath.find("html_files/tmzgugp_cgi") != std::string::npos) {
			if (this->clientResponse->removeFile(this->clientResponse->filePath.c_str()))
				std::cout << "file removed\n";
			else
				std::cout << "file not removed\n";
		}
		else if (this->clientResponse->_allChunkSent) {
			std::cout << "all chunks are sent return 0 now\n";
			delete this->clientResponse;
			this->clientResponse = NULL;
		}
		else {
			std::string chunk = this->clientResponse->getChunk(serverConfig._buffSize);
			send(this->clientSocket, &chunk[0], chunk.length(), 0);
		}
	}
}
