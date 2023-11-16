std::string response::createResponse(std::string url) {

	std::string filePath = "./html_files" + url + "/" + getFile("./html_files" + url);
	std::ifstream htmlFile(filePath);

	if (!htmlFile && !cgiCheckConditions(url)) {
		return "HTTP/1.1 404 Not Found\r\n\r\n<h1>404 Not Found</h1>";
	} else if (!htmlFile && cgiCheckConditions(url)) {
		if (_cgiInstance._isError) {
			std::ifstream inputFile("html_files/error_test/error505.html");
			std::string cgiContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

			if (cgiContent.empty()) {
				return "HTTP/1.1 500 Internal Server Error\r\n\r\n<h1>500 Internal Server Error</h1>";
			}

			std::string response = "HTTP/1.1 200 OK\r\n";
			response += "Content-Type: text/html\r\n";
			response += "Content-Length: " + std::to_string(cgiContent.length()) + "\r\n";
			response += "\r\n" + cgiContent;

			return response;

		} else {
			std::ifstream inputFile("src/tmp_cgi.txt");
			std::string cgiContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

			if (cgiContent.empty()) {
				return "HTTP/1.1 500 Internal Server Error\r\n\r\n<h1>500 Internal Server Error</h1>";
			}

			std::string response = "HTTP/1.1 200 OK\r\n";
			response += "Content-Type: text/html\r\n";
			response += "Content-Length: " + std::to_string(cgiContent.length()) + "\r\n";
			response += "\r\n" + cgiContent;

			remove("src/tmp_cgi.txt");
			return response;
		}
	}

	std::string htmlContent((std::istreambuf_iterator<char>(htmlFile)), std::istreambuf_iterator<char>());

	// Create an HTTP response with the HTML content
	std::string response = "HTTP/1.1 200 OK\r\n";
	response += "Content-Type: text/html\r\n";
	response += "Content-Length: " + std::to_string(htmlContent.length()) + "\r\n";
	response += "\r\n" + htmlContent;

	return response;
}



//----cgi
bool response::cgiCheckConditions(std::string url) {
	if (_cgiInstance.cgiValidExtension(url)) {
		_cgiInstance.executeCgi();
		return true;
	}
	return false;
}