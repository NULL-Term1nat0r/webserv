# Sockets
Sockets are software endpoints that allow a web server to establish and manage connections with clients (usually web browsers) over the Internet. These sockets enable the server to send and receive HTTP requests and responses, allowing for the exchange of web pages, files, and other resources between the server and clients. Web servers use sockets to listen for incoming client connections, handle multiple simultaneous requests, and efficiently manage the flow of web traffic.

Clients, such as web browsers, also use sockets to establish connections to web servers. They create sockets to send HTTP requests to the server and receive the corresponding HTTP responses. Sockets on the client side enable the browser to retrieve web content, including HTML, CSS, JavaScript files, images, and videos, by establishing connections to the appropriate web server sockets. This bidirectional communication between web servers and clients via sockets enables the browsing experience and the retrieval of web resources.

## Function
```bash
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```
- domain: Specifies the communication domain or address family. It defines the protocol family used for communication, such as IPv4 (AF_INET), IPv6 (AF_INET6), or local communication (AF_UNIX or AF_LOCAL).

- type: Specifies the socket type, which determines the communication characteristics. Common types include SOCK_STREAM for stream sockets (used with TCP) and SOCK_DGRAM for datagram sockets (used with UDP).

- protocol: Specifies the protocol to be used. Typically, this parameter is set to 0, allowing the operating system to choose the most appropriate protocol based on the combination of the domain and type parameters. In some cases, you may specify a protocol explicitly, such as IPPROTO_TCP for TCP or IPPROTO_UDP for UDP.

If the socket function is successful, it returns a non-negative integer, which is the socket descriptor and if an error occurs, socket returns -1.

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

## Blocking Sockets
- Blocking sockets are the traditional and default mode of operation for sockets in many programming languages.
- When you perform a read or write operation on a blocking socket, the operation will block, or wait, until it completes successfully or encounters an error.
- If you try to read from a blocking socket, and there is no data available to read, your program will wait until data arrives or a timeout occurs.
- Similarly, if you try to send data through a blocking socket, and the socket's send buffer is full or the connection is slow, your program will wait until the data can be sent.
- Blocking sockets are simple to use but can lead to performance problems in applications with multiple sockets or when you want to perform other tasks while waiting for network operations to complete.
- Blocking sockets are often simpler to use and are suitable for applications where it's acceptable for the program to wait for network operations to complete before proceeding.

## Non-blocking Sockets
- Non-blocking sockets, on the other hand, allow your program to continue executing other tasks without waiting for a network operation to complete.
- When you perform a read or write operation on a non-blocking socket, the operation will return immediately, either with the amount of data read/written or an error code.
- If there is no data available to read from a non-blocking socket, the read operation returns immediately with an indication that no data is ready. This allows your program to perform other tasks and periodically check the socket for data.
- Similarly, if you try to send data through a non-blocking socket and the socket's send buffer is full or the connection is slow, the write operation will return immediately with an indication that the operation would block.
- To handle non-blocking sockets effectively, you typically need to use techniques like polling or asynchronous I/O to check for data readiness and manage multiple sockets efficiently.
- Non-blocking sockets are more complex to work with but are useful in applications that need to handle multiple sockets simultaneously or perform other tasks while waiting for network operations. They are commonly used in real-time or event-driven systems.

## Sources
- https://www.geeksforgeeks.org/socket-programming-cc/
- https://www.youtube.com/watch?v=gntyAFoZp-E&t=12s
- https://www.codingninjas.com/studio/library/learning-socket-programming-in-c
- https://docs.oracle.com/cd/E19455-01/806-1017/sockets-4/index.html
- http://dwise1.net/pgm/sockets/blocking.html#WHY
- https://www.geeksforgeeks.org/what-is-web-socket-and-how-it-is-different-from-the-http/
