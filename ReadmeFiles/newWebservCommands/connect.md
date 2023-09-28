# Connect

```c
#include <sys/socket.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

## Purpose
The connect() function is used in C++ for establishing a network connection from a client application to a remote server. It is part of socket programming and enables communication with remote services over various network protocols, such as TCP/IP or UDP

## Usage
1. Socket Creation: First, you create a socket object using the socket() function to represent the endpoint for communication with the remote server.

2. Server Information: You specify the server's address (usually an IP address) and port number to which you want to connect. This information is typically stored in a struct sockaddr_in (for IPv4) or struct sockaddr_in6 (for IPv6).

3. Connection Establishment: The connect() function is called with the socket descriptor, server's address information, and the size of the address structure as arguments. It initiates the connection process to the remote server.

4. Communication: Once the connection is established, you can use the socket for sending and receiving data to and from the server.

## Function Parameters
- `int sockfd`: This is an integer value representing the socket that you want to use for the connection. The socket must be previously created using the socket() function. The sockfd parameter specifies the client socket through which the connection will be established.

- `const struct sockaddr *addr`: This parameter expects a pointer to a struct sockaddr data structure that contains the server's address information, including its IP address and port number. The struct sockaddr is typically defined as a generic structure, and you can use specific subtypes like struct sockaddr_in for IPv4 or struct sockaddr_in6 for IPv6 to provide the necessary details. The server's address information should be properly configured before calling connect().

- `socklen_t addrlen`: This parameter specifies the size, in bytes, of the server address structure. It is essential to correctly set the addrlen parameter to the size of the server address structure being passed. For example, if you are using struct sockaddr_in for IPv4, you should set addrlen to sizeof(struct sockaddr_in).
## Return Value
- `int`:
If the connection or binding succeeds, zero is returned.  On error, -1 is returned, and errno is set to indicate the error.

## Code example
```c
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Server information setup
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Server's port
    serverAddr.sin_addr.s_addr = inet_addr("10.12.11.52"); // Server's IP address

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connect failed");
        return 1;
    }

    // Use the clientSocket for communication with the server

    // Close the socket when done
    close(clientSocket);

    return 0;
}
```
## Description
- The socket() function is used to create a socket for network communication.
- The connect() function is used to establish a connection to the server.
It takes the client socket descriptor (clientSocket), a pointer to the serverAddr structure (cast to struct sockaddr *), and the size of the address structure (sizeof(serverAddr)) as arguments.
- If the connection fails, the connect() function returns a value less than 0, and an error message is printed using perror(). The program returns with an error code.
- Use the ClientSocket for Communication:
This section is a placeholder for your application logic. Once the connection is established, you can use the clientSocket to send and receive data with the server.
close(clientSocket);
After you are done with the communication, it's important to close the socket using the close() function to release the associated resources.

## Additional sources

[linux manual page](https://man7.org/linux/man-pages/man2/connect.2.html)
