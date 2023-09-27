# listen(...) Function

```c
#include <sys/socket.h>

int listen(int socket, int backlog);

```

## Purpose
- `listen()`   function is used in network programming to mark a socket as a passive socket, ready to accept incoming connections. It prepares the socket for accepting connections initiated by remote clients.

## Usage

To use the `listen()` function effectively in your network application, follow these guidelines:

1. Call `listen()` on a socket after binding it to a local address and port using the `bind()` function. This setup is typically performed on the server side of a network application.

2. Ensure that you have the descriptor of the socket you want to mark as a passive socket. This socket descriptor should be obtained earlier in your code, typically through the `socket()` function.

3. Specify the `backlog` parameter, which represents the maximum number of pending connections that can be queued up, waiting for acceptance. It should be set to a reasonable value based on the expected load of your server.

4. After calling `listen()`, your socket is prepared and ready to accept incoming connections initiated by remote clients.

5. You can now use the `accept()` function to accept incoming connections and create new sockets for communication with connected clients.

By following these steps, you can effectively use the `listen()` function to manage incoming connections in your network application.


## Function Parameters

- `socket` (int): The descriptor of the socket to be marked as a passive socket.

- `backlog` (int): The maximum number of pending connections that can be queued up for acceptance. Typically, it is set to a reasonable value based on the expected load of the server.

## Return Value
- `listen()` returns 0 on success.

- On failure, it returns -1, and you can check `errno` for the error code.


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

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("listen");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    // Rest of the server code...

    // Close the socket when done
    close(serverSocket);

    return 0;
}

```
## Description

The `listen()` function is responsible for preparing a socket to accept incoming connections. It plays a crucial role on the server side of network applications. Here's a breakdown of its functionality:

- The `listen()` function is typically used after creating a socket and binding it to a local address and port using the `socket()` and `bind()` functions.

- Once you've successfully created and bound the socket, you call `listen()` to make it ready to accept incoming connections.

- Subsequently, your socket becomes fully prepared to accept incoming connections using the `accept()` function.

- The `backlog` parameter in `listen()` is essential; it specifies the maximum number of pending connections that can be queued up, waiting for acceptance. It's crucial to set this value appropriately based on your server's expected load.

By understanding and utilizing the `listen()` function in this way, you can efficiently manage incoming connections in your network applications.

## Additional sources

[linux manual page](https://linux.die.net/man/2/listen)