#include "../includes/server.hpp"

server::client::client(int clientSocket) :  clientSocket(clientSocket), lastActivity(time(0)), clientRequest(NULL), clientResponse(NULL)  {
}

server::client::~client() {
}

int server::client::executeClientRequest(int buffSize, std::vector<struct pollfd> pollEvents, std::vector<client> &clients){
//	std::cout << "address of client class: " << this << std::endl;
//	std::cout << "execute client request called\n";
//	std::cout << "adress pollevents from server << : " << &pollEvents << std::endl;
//	std::cout << "address of struct in container: " << &pollEvents[clientSocket] << std::endl;
//	std::cout << "address of eventInt: " << &pollEvents[clientSocket].events << std::endl;
	std::vector<uint8_t> _request(buffSize);
	recv(this->clientSocket, &_request[0], buffSize, 0);

	if (this->clientRequest == NULL) {
		request newRequest = request(_request);
		if (newRequest.getPostMethod()){
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
				delete this->clientRequest;
				this->clientRequest = NULL;
				return 0;
			}
		}
	}
	else if (dynamic_cast<getRequest*>(static_cast<request*>(this->clientRequest))){
		getRequest *get = static_cast<getRequest *>(this->clientRequest);
		response *newResponse = new response(get->getFilePath());
		clientResponse = newResponse;
		delete clientRequest;
		clientRequest = NULL;
		return POLLOUT;
		std::cout << "changed event to POLLOUT: " << pollEvents[clientSocket].events << std::endl;
	}
	else if (dynamic_cast<deleteRequest*>(static_cast<request*>(this->clientRequest))){
		std::cout << "delete request incoming\n";
		return 0;
	}
}

int server::client::executeClientResponse(int buffSize, std::vector<struct pollfd> pollEvents, std::vector<client> &clients){
	std::cout << "execute client response called\n";
	if (this->clientResponse != NULL){
		if (this->clientResponse->_allChunkSent){
			std::cout << "all chunks are sent return 0 now\n";
			delete this->clientResponse;
			this->clientResponse = NULL;
			return 0;
		}
		else {
			std::string chunk = this->clientResponse->getChunk(buffSize);
			send(this->clientSocket, &chunk[0], chunk.length(), 0);
			return POLLOUT;
		}
	}
	return 0;
}
