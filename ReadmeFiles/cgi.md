# CGI

## Definition
The Common Gateway Interface (CGI) is a protocol and standard that enables web servers to interact with external programs or scripts to generate dynamic web content.
CGI allows a web server to communicate with applications or scripts written in various programming languages, such as Perl, Python, Ruby, and others, to generate web pages on-the-fly in response to user requests.

## How does it work?

1. Client Request: A user sends a request to a web server by accessing a URL, clicking a link, or submitting a form on a web page.This request typically includes specific information, such as the URL and any form data.

2. Web Server Handling: The web server receives the request and determines that it needs to execute a CGI script to generate the dynamic content. This determination is typically based on the file extension of the requested resource (e.g., ".cgi", ".pl", ".py").

3. CGI Execution: The web server launches the specified CGI script or program as a separate process on the server. It sets up an environment that includes important information such as HTTP request headers, form data, and other relevant parameters. This information is made available to the CGI script through environment variables.

4. Script Processing: The CGI script processes the information provided by the web server, performs its intended operations (e.g., data processing, database queries, calculations), and generates dynamic content in the form of HTML, XML, JSON, or other suitable formats.

5. Response Generation: The generated content is returned by the CGI script to the web server through standard input and output streams. The web server collects this output.

6. Client Response: The web server sends the dynamically generated content as an HTTP response to the user's browser, which then renders the page. The browser has no knowledge that the content was generated dynamically; it simply receives and displays the HTML or other data.

7. Clean-up: After the CGI script completes its execution and the response is sent to the client, the script's process typically terminates. Any temporary files or resources created by the script may be cleaned up.
