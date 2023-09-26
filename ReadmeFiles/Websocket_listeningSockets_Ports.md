# Sockets
Sockets are software endpoints that allow a web server to establish and manage connections with clients (usually web browsers) over the Internet. These sockets enable the server to send and receive HTTP requests and responses, allowing for the exchange of web pages, files, and other resources between the server and clients. Web servers use sockets to listen for incoming client connections, handle multiple simultaneous requests, and efficiently manage the flow of web traffic.

Clients, such as web browsers, also use sockets to establish connections to web servers. They create sockets to send HTTP requests to the server and receive the corresponding HTTP responses. Sockets on the client side enable the browser to retrieve web content, including HTML, CSS, JavaScript files, images, and videos, by establishing connections to the appropriate web server sockets. This bidirectional communication between web servers and clients via sockets enables the browsing experience and the retrieval of web resources.

## Function
```bash
int socket(int domain, int type, int protocol);
```
- domain: Specifies the communication domain or address family. It defines the protocol family used for communication, such as IPv4 (AF_INET), IPv6 (AF_INET6), or local communication (AF_UNIX or AF_LOCAL).

- type: Specifies the socket type, which determines the communication characteristics. Common types include SOCK_STREAM for stream sockets (used with TCP) and SOCK_DGRAM for datagram sockets (used with UDP).

- protocol: Specifies the protocol to be used. Typically, this parameter is set to 0, allowing the operating system to choose the most appropriate protocol based on the combination of the domain and type parameters. In some cases, you may specify a protocol explicitly, such as IPPROTO_TCP for TCP or IPPROTO_UDP for UDP.

## Two most common socket types

- Stream Sockets (SOCK_STREAM): Stream sockets are used for reliable, connection-oriented communication, typically implemented over the TCP (Transmission Control Protocol) protocol. They provide a continuous stream of data and guarantee that data sent from one end will arrive in the same order at the other end. Stream sockets are commonly used for applications where data integrity and order are essential, such as web browsing, email, and file transfers.

- Datagram Sockets (SOCK_DGRAM): Datagram sockets are used for connectionless, unreliable communication, usually implemented over the UDP (User Datagram Protocol) protocol. Datagram sockets allow data to be sent as discrete packets, and there is no guarantee of delivery or order. Datagram sockets are suitable for applications where speed is more critical than reliability, such as online gaming, streaming media, and real-time communication.


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


For Datagram sockets bind is optional, listen and accept are not used since UDP works connectionless.

## Sources
- https://www.geeksforgeeks.org/socket-programming-cc/
- https://www.youtube.com/watch?v=gntyAFoZp-E&t=12s
- https://www.codingninjas.com/studio/library/learning-socket-programming-in-c
- https://docs.oracle.com/cd/E19455-01/806-1017/sockets-4/index.html
