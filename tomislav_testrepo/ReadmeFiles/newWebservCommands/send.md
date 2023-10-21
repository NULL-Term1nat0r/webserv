# send(...) Function

```c
#include <sys/socket.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

## Purpose
- `send()`  is used to send data over a connected socket. It is typically used in network programming to transmit data from the sender to the receiver.

## Usage
- Call `send()` to send data on a connected socket. You specify the socket descriptor, a pointer to the data to be sent (`buf`), the length of the data (`len`), and optional flags that control the behavior of the send operation.

## Function Parameters
- `sockfd` (int): The socket descriptor representing the connected socket over which data is to be sent.
- `buf` (const void *): A pointer to the data that you want to send.
- `len` (size_t): The length of the data to be sent, in bytes.
- `flags` (int): Optional flags that control the behavior of the send operation. Common flags include `0` for default behavior or flags like `MSG_DONTWAIT` for non-blocking sends.


## Return Value
- `send()` returns the number of bytes sent on success. This value may be less than `len` if not all the data could be sent in a single operation.
- On failure, it returns `-1`, and you can check `errno` for the error code to determine the reason for the failure.


## Code example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int main() {
    int clientSocket;
    const char *message = "Hello, Server!";
    ssize_t bytesSent;

    // Create a socket and establish a connection

    // Send data over the socket
    bytesSent = send(clientSocket, message, strlen(message), 0);
    if (bytesSent == -1) {
        perror("send");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    printf("Sent %ld bytes: %s\n", bytesSent, message);

    // Rest of the code...
    // Receive data and perform other socket operations.

    // Close the socket when done
    close(clientSocket);

    return 0;
}

```
## Description
- In the code example, `send()` is used to send the message "Hello, Server!" over a connected socket. The `sockfd` parameter represents the connected socket, `buf` points to the message, `len` specifies the length of the message, and `flags` is set to `0` for default behavior.

- The function returns the number of bytes sent, which may be less than the message length if not all the data is sent in a single operation.

- After sending data, the code can continue with other socket operations, such as receiving data or performing further communication.


## Additional sources

[linux manual page](https://linux.die.net/man/2/send)
