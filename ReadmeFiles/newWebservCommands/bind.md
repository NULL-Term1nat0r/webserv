# bind(...) Function

```c
#include <sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr,
         socklen_t addrlen);

```


## Purpose
- `bind()` is typically used on the server side of a network application to specify the local address and port on which the server socket should listen for incoming connections or data.

## Usage
- Call `bind()` to associate a socket with a local address and port.
Specify the socket descriptor, local address, and port as function arguments.
After binding, the socket is ready to receive incoming connections or data on the specified address and port.

## Function Parameters
- `socket` (int): The `socket` descriptor that you want to bind.
- `address` (struct sockaddr *): A pointer to a structure (sockaddr) that contains the local address information. This structure depends on the address family (e.g., sockaddr_in for IPv4, sockaddr_in6 for IPv6).
- `address_len` (socklen_t): The size of the address structure.


## Return Value
- `bind()` returns 0 on success.
- On failure, it returns -1, and you can check errno for the error code to determine the reason for the failure.

## Code example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr;

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

    printf("Server socket is bound to port 8080.\n");

    // Rest of the server code...
    // Listen for incoming connections, accept them, and handle data.

    // Close the socket when done
    close(serverSocket);

    return 0;
}
```
## Description

- In the code example, a server socket is created using socket(), and then bind() is used to bind the socket to a specific address and port. The serverAddr structure contains the address and port information to which the server socket is bound.

- The server is now ready to listen for incoming connections or data on the specified address and port.

- The INADDR_ANY constant for the sin_addr.s_addr field allows the server to bind to any available network interface, meaning it can receive connections on any network interface that the machine has. If you want to bind to a specific network interface, you can specify its IP address instead.

- After binding, the server can use listen() to start listening for incoming connections or use other socket operations to send and receive data as needed.

## Additional sources

[linux manual page](https://linux.die.net/man/2/bind)