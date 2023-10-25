/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:34:43 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/03 16:34:43 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Header.h"
#include "../includes/request.hpp"
#include "../includes/parsing.hpp"
#include "../includes/server.hpp"
#include "../includes/response.hpp"

int main(){

//	Config conf = Config("../config_parser/confFiles/server.conf");
//	Server serv = Server(conf);
//	request test = request("GET /favicon.ico HTTP/1.1\\n\n"
//				  "Host: localhost:8080\\n\n"
//				  "Connection: keep-alive\\n\n"
//				  "sec-ch-ua: Google Chrome;v=\"117\", Not;A=Brand;v=8, Chromium;v=117\\n\n"
//				  "sec-ch-ua-mobile: ?0\\n\n"
//				  "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36\\n\n"
//				  "sec-ch-ua-platform: macOS\\n\n"
//				  "Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8\\n\n"
//				  "Sec-Fetch-Site: same-origin\\n\n"
//				  "Sec-Fetch-Mode: no-cors\\n\n"
//				  "Sec-Fetch-Dest: image\\n\n"
//				  "Referer: http:localhost:8080/\\n\n"
//				  "Accept-Encoding: gzip, deflate, br\\n\n"
//				  "Accept-Language: en-GB,en-US;q=0.9,en;q=0.8\\n");
//	std::cout << "-------------------------\n";
//	test.parseProtocol();
//	test.printRequest();
//	webServer::returnFileContent("./html_files/mainPage1.html");
//	try{
//		webServer::startAllServers("../config_parser/confFiles/server.conf");
//	}
//	catch (std::exception &e){
//		std::cout << e.what() << " julien\n" << std::endl;
//	}
	Server serv;
	serv._startServers("../config_parser/confFiles/server.conf");

	return 0;
}


//std::string getHtmlResponse() {
//	// Read the HTML file
//	std::ifstream htmlFile("../html_files/mainPage1.html");
//	if (!htmlFile) {
//		return "HTTP/1.1 404 Not Found\r\n\r\n<h1>404 Not Found</h1>";
//	}
//
//	std::string htmlContent((std::istreambuf_iterator<char>(htmlFile)), std::istreambuf_iterator<char>());
//
//	// Create an HTTP response with the HTML content
//	std::string response = "HTTP/1.1 200 OK\r\n";
//	response += "Content-Type: text/html\r\n";
//	response += "Content-Length: " + std::to_string(htmlContent.length()) + "\r\n";
//	response += "\r\n" + htmlContent;
//
//	return response;
//}