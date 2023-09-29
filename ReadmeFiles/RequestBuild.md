# RequestBuild (in http Protocol)

## Purpose of Building an HTTP Request

The purpose of building an HTTP (Hypertext Transfer Protocol) request is to send a structured message from a client, such as a web browser or application, to a server, requesting a specific action or resource. HTTP requests play a fundamental role in how the World Wide Web operates, serving several key purposes:

1. **Resource Retrieval:** HTTP requests are used to retrieve resources from a web server. These resources can include web pages (HTML documents), images, stylesheets, scripts, videos, and other types of files or data hosted on the server.

2. **Interaction with Web Services:** HTTP requests enable interaction with web services and APIs. Clients can send requests to servers to request data, perform operations, or submit data. Commonly used HTTP methods include GET (retrieve data), POST (submit data), PUT (update data), and DELETE (remove data).

3. **Data Submission:** Clients use HTTP POST requests to submit data to a server. This is often seen in web forms where users submit information such as login credentials, search queries, registration details, and more.

4. **State Management:** HTTP requests are used to manage the state of web applications. When users interact with web pages by clicking links or buttons, clients can send requests to the server to perform actions and update the application's state.

5. **Authentication and Authorization:** HTTP requests may include headers and credentials for authentication and authorization purposes. Servers use this information to verify the client's identity and determine if the client has permission to access specific resources or perform particular actions.

6. **Caching and Content Negotiation:** HTTP requests can include headers that specify caching preferences (e.g., "If-Modified-Since") and content negotiation preferences (e.g., "Accept"). These headers control how resources are served and cached by the server and client.

7. **Error Handling:** HTTP responses from the server include status codes that indicate the outcome of the request. These status codes help clients understand whether the request was successful, encountered an error, or requires further action.

8. **Redirection:** HTTP requests and responses can include redirection instructions (status code 3xx) to inform the client that it should request a different resource or URL.

9. **Custom Communication:** HTTP is a versatile protocol that can be extended for various purposes. Clients and servers can define custom HTTP headers or use specific HTTP methods to support custom communication patterns.

To build an HTTP request, a client constructs a structured message that includes elements such as the request method (e.g., GET, POST), the target URL, headers (including content type and content length), and, in the case of POST requests, a request body containing data to be sent to the server.

In summary, HTTP requests are essential for communication between clients and servers on the web, enabling the retrieval of resources, data submission, interaction with web services, and management of web application state. They are a core component of how web applications and websites function.

## Usage

The information provided in the headers of the request are helping you to set up the resources the webserver should provide for the client. Here is an example:

```mathematica
Accept-Language: en-GB,en-US;q=0.9,en;q=0.8
``` 
In this example we get information about the language the client is using. The server can use this information to provide the client with the right language.
If you want to only content in one language you can ignore this header and it is not important for your Parser.
In the end it is about your implementations and what you want to do with the information you get from the client.

## Example
```mathematica
GET / HTTP/1.1
Host: www.example.com
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Connection: keep-alive
```

## Description

**Request Method and Target URL:** The request begins with the HTTP method "GET" and specifies the target URL as "/". This indicates that the client is making a "GET" request to the root or home page of the website.

**HTTP Version:** The HTTP version used in the request is "HTTP/1.1," indicating that the client and server are using the HTTP/1.1 protocol for communication.

**Host:** The "Host" header specifies the domain name or hostname of the server to which the request is being sent. In this case, it is "www.example.com." This header is crucial for virtual hosting, allowing the server to determine which website or resource the client is requesting when multiple websites are hosted on the same server.

**Accept:** The "Accept" header indicates the types of media or content formats that the client can accept in the response. It lists multiple content types, including "text/html," "application/xhtml+xml," and "application/xml," along with their respective quality values (q-values). These q-values provide a relative preference for each content type. For example, "text/html" is the preferred content type with a quality value of 1.0, while "application/xml" is accepted but less preferred with a quality value of 0.9. The "/" wildcard indicates that the client can accept any content type with a default preference of 0.8 if no specific match is found.

**Connection:** The "Connection" header is set to "keep-alive," indicating that the client requests that the connection with the server be kept alive after this request is processed. Keeping the connection alive can improve performance by allowing multiple requests and responses to be sent over the same connection without the overhead of establishing a new connection for each request.

This HTTP request header is a typical example of a "GET" request sent by a web client to a server. It specifies the desired resource (the root or home page), the preferred content types, and the request for a persistent (keep-alive) connection with the server. The "Host" header ensures that the server can correctly route the request to the appropriate website when hosting multiple sites.

## Common HTTP Methods

|Method|Description|Possible Body|
|:----|----|:----:|
|**`GET`** | Retrieve a specific resource or a collection of resources, should not affect the data/resource| No|
|**`POST`** | Perform resource-specific processing on the request content| Yes|
|**`DELETE`** | Removes target resource given by a URI| Yes|
|**`PUT`** | Creates a new resource with data from message body, if resource already exist, update it with data in body | Yes|
|**`HEAD`** | Same as GET, but do not transfer the response content  | No|

__GET__

HTTP GET method is used to read (or retrieve) a representation of a resource. In case of success (or non-error), GET returns a representation of the resource in response body and HTTP response status code of 200 (OK). In an error case, it most often returns a 404 (NOT FOUND) or 400 (BAD REQUEST).

__POST__

HTTP POST method is most often utilized to create new resources. On successful creation, HTTP response code 201 (Created) is returned.

__DELETE__


# Example with one of our test server files for the GET-Method

## Step 1: create an example file with html code in the same folder where you start your server program

<img width="682" alt="Screen Shot 2023-09-29 at 6 56 48 PM" src="https://github.com/NULL-Term1nat0r/webserv/assets/109620716/1c1269c0-20e4-4759-9d0f-c43cea7f6776">

<img width="545" alt="Screen Shot 2023-09-29 at 6 57 10 PM" src="https://github.com/NULL-Term1nat0r/webserv/assets/109620716/68a1cfb4-902f-4942-9afc-6fb569bf85fe">

## Step 2: start the program

<img width="589" alt="Screen Shot 2023-09-29 at 6 45 56 PM" src="https://github.com/NULL-Term1nat0r/webserv/assets/109620716/5503cdf2-ea4a-447e-b646-7e1495509ba2">

## Step 3: open your web browser and type in the url

<img width="495" alt="Screen Shot 2023-09-29 at 6 46 44 PM" src="https://github.com/NULL-Term1nat0r/webserv/assets/109620716/ee9063b5-aef6-4f33-b485-803dcde6e6a9">

## Step 4: press enter and you will see the following

<img width="560" alt="Screen Shot 2023-09-29 at 6 47 28 PM" src="https://github.com/NULL-Term1nat0r/webserv/assets/109620716/98b4b9f6-9c13-4c0a-b874-413820deef4b">

## Step 5: checkout the terminal and you will see the following request message by the client

<img width="589" alt="Screen Shot 2023-09-29 at 6 47 42 PM" src="https://github.com/NULL-Term1nat0r/webserv/assets/109620716/7b27238d-8c9f-4c4b-a4ca-2240255b3a9a">

