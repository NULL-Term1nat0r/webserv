# accept(...) Function

```c
#include <sys/socket.h>

int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);

```

## Purpose
- `accept()`  function is used in network programming to accept incoming connections on a listening socket. It creates a new socket that represents the accepted connection, allowing data to be sent and received between the client and server.

## Usage
- Call `accept()` on a listening socket to accept an incoming connection.
- `socket` is the listening `socket` descriptor.
- `address` is a pointer to a structure that will hold the address information of the connected client.
- `address_len` is a pointer to the length of the address structure.
- On success, `accept()` returns a new socket descriptor for the accepted connection.
- The original listening `socket` remains open and can be used to `accept` more connections.

## Function Parameters
- `socket` (int): The descriptor of the listening `socket`.
- `address` (struct sockaddr *restrict): A pointer to a structure (sockaddr) where the address information of the connected client will be stored.
- `address_len` (socklen_t *restrict): A pointer to a variable that specifies the size of the address structure and will be   updated with the actual size after the call.

## Return Value
- `bind()`  returns a new socket descriptor (a file descriptor) representing the accepted connection. This new socket is used for data communication with the connected client.
On failure, it returns -1, and you can check `errno` for the error code.

## Code example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to an address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface
    serverAddr.sin_port = htons(8080); // Bind to port 8080

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("listen");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    // Accept an incoming connection
    clientAddrLen = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket == -1) {
        perror("accept");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Accepted connection from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    // Now you can read and write data on the clientSocket

    // Close the sockets when done
    close(clientSocket);
    close(serverSocket);

    return 0;
}
```
## Description

- The `accept()` function is essential for server applications in network programming. It waits for incoming connections on a listening socket, creates a new socket for the accepted connection, and returns the new socket descriptor. This new socket can be used for data communication with the connected client.

- In the code example, a server `socket` is created using `socket()`, and then `bind()` is used to bind the `socket` to a specific address and port. The serverAddr structure contains the address and port information to which the server `socket` is bound.

- The accepted `socket` (clientSocket) can then be used for sending and receiving data with the connected client. After communication is complete, both the server and client sockets should be closed using close().

## Additional sources

[linux manual page](https://linux.die.net/man/2/accept)