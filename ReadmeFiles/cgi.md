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

![cgi](https://github.com/NULL-Term1nat0r/webserv/assets/96915676/fecdce7a-f33c-4c94-b190-d36ab34e65b2)


## CGI example script
```c
#include <iostream>
#include <cstdlib>
#include <string>

int main() {
    // Set the content type to HTML
    std::cout << "Content-type:text/html\r\n\r\n";

    // HTML response
    std::cout << "<html>\n";
    std::cout << "<head><title>CGI C++ Example</title></head>\n";
    std::cout << "<body>\n";

    // Process user input from the query string
    char* query = getenv("QUERY_STRING");
    if (query != nullptr) {
        std::string userInput(query);

        // Print the user's input on the web page
        std::cout << "<h2>User Input:</h2>\n";
        std::cout << "<p>" << userInput << "</p>\n";
    } else {
        std::cout << "<p>No input received.</p>\n";
    }

    std::cout << "</body>\n";
    std::cout << "</html>\n";
}
```
## Description
- This is a simple example of a CGI script written in C++ that takes user input via a web form, processes it, and generates a dynamic web page as output.
- We start by setting the content type to HTML using the HTTP header Content-type:text/html\r\n\r\n. This tells the web server to expect HTML content in the response.
- We then output an HTML page with a title and body.
- We retrieve user input from the query string using the getenv("QUERY_STRING") function. The query string contains data submitted via a web form.
- If user input is found, we print it in an HTML paragraph.
- Finally, we close the HTML tags and return 0 to indicate successful execution.
- To use this CGI script, you would typically save it with a .cgi or .cpp extension in a directory configured for CGI execution on your web server. Make sure the script file has executable permissions, and then you can create a web form that submits data to this script. When the form is submitted, the script will process the input and display it on the resulting web page.

## Sources
- https://www.ionos.com/digitalguide/websites/web-development/what-is-a-cgi/
- https://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm
- https://www.youtube.com/watch?v=NwRVJX0Ieno
