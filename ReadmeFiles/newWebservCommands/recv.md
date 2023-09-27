# recv(...) Function

```c
#include <sys/socket.h>

ssize_t recv(int socket, void *buffer, size_t length, int flags);

```

## Purpose
- `recv()`    function is used in network programming to receive data from a socket. It is commonly used to receive data from a connected socket

## Usage

To use the `recv()` function effectively in your network application, follow these guidelines:

- Call `recv()` on a socket when you need to receive data from it.
- Ensure you have the `socket` descriptor of the socket from which you want to receive data.
- Use `buffer`, a pointer to the buffer where the received data will be stored.
- Specify `length`, which is the maximum number of bytes you want to receive in a single call.
- You can also provide `flags`, a set of flags that modify the behavior of the `recv()` function. For example, you can use flags to control the reception of out-of-band data or set the socket to non-blocking mode.

- On success, `recv()` returns the number of bytes received, which may be less than or equal to the specified `length`. It returns 0 if the remote side has closed the connection.

- In case of failure, `recv()` returns -1, and you can check the `errno` variable for the specific error code, helping you diagnose and handle the error effectively.


## Function Parameters

- `socket` (int): The descriptor of the socket from which you want to receive data.

- `buffer` (void *): A pointer to the buffer where the received data will be stored.

- `length` (size_t): The maximum number of bytes to receive.

- `flags` (int): A set of flags that can modify the behavior of the `recv()` function.


## Return Value

- `recv()` returns the number of bytes received on success.

- It returns 0 if the remote side has closed the connection.

- In the event of a failure, `recv()` returns -1, and you can check the `errno` variable for the error code, which provides details about the encountered error.



## Code example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int clientSocket;
    char buffer[1024];

    // Receive data from a connected socket
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    } else if (bytesRead == 0) {
        printf("Connection closed by remote side.\n");
    } else {
        printf("Received %zd bytes: %s\n", bytesRead, buffer);
    }

    // Rest of the code...

    return 0;
}

```

## Description

The `listen()` function plays a critical role in network applications by preparing a socket to accept incoming connections. Its typical usage is on the server side of network applications, following these steps:

- First, create a socket using the `socket()` function.

- Next, bind the socket to a local address and port using the `bind()` function.

- Once these initial steps are completed, you're ready to employ the `listen()` function.

- After calling `listen()`, your socket is fully prepared to accept incoming connections, and you can utilize the `accept()` function for this purpose.

- A crucial aspect of `listen()` is the `backlog` parameter, which defines the maximum number of pending connections that can be queued up, awaiting acceptance.

By following this sequence of actions and understanding the role of the `listen()` function, you can effectively manage incoming connections in your network applications.


## Additional sources

[linux manual page](https://linux.die.net/man/2/recv)