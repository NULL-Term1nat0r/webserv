# Sockets
Sockets are software endpoints that allow a web server to establish and manage connections with clients (usually web browsers) over the Internet. These sockets enable the server to send and receive HTTP requests and responses, allowing for the exchange of web pages, files, and other resources between the server and clients. Web servers use sockets to listen for incoming client connections, handle multiple simultaneous requests, and efficiently manage the flow of web traffic.

Clients, such as web browsers, also use sockets to establish connections to web servers. They create sockets to send HTTP requests to the server and receive the corresponding HTTP responses. Sockets on the client side enable the browser to retrieve web content, including HTML, CSS, JavaScript files, images, and videos, by establishing connections to the appropriate web server sockets. This bidirectional communication between web servers and clients via sockets enables the browsing experience and the retrieval of web resources.


## Procedure in Client-Server Communication
- Socket: Create a new communication
- Setsockopt: This step is optional and involves setting socket options. You can configure various properties of the socket, such as its behavior, timeout values, or socket-level options.
- Bind: Attach a local address to a socket
- Listen: Announce willingness to accept connections
- Accept: Block caller until a connection request arrives
- Connect: Actively attempt to establish a connection
- Send: Send some data over a connection
- Receive: Receive some data over a connection
- Close: Release the connection


![socket_c++_grafik](https://github.com/NULL-Term1nat0r/webserv/assets/96915676/e310b737-2c79-4f2e-9e64-25af95edc0c0)



## Datagram Socket Operations
This section describes how to use communication styles that don't use connections (styles SOCK_DGRAM and SOCK_RDM). Using these styles, you group data into packets and each packet is an independent communication. You specify the destination for each packet individually.
The listen and accept functions are not allowed for sockets using connectionless communication styles.

## Sources
- https://www.geeksforgeeks.org/socket-programming-cc/
- https://www.youtube.com/watch?v=gntyAFoZp-E&t=12s
