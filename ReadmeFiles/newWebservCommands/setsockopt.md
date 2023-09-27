# setsockopt(...) Function

```c
#include <sys/socket.h>

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

```

## Purpose
- `setsockopt()`  is used to set various options on a socket. These options can control various aspects of socket behavior, such as socket-level properties and behaviors.

## Usage
- Call `setsockopt()` to configure the behavior of a socket. You specify the socket descriptor, the option level, the option name, and the option value as function arguments. The option level and name determine which socket property you are configuring, and the option value is the value you want to set for that property.

## Function Parameters

- `sockfd` (int): The socket descriptor for the socket you want to configure.
- `level` (int): The option level, which specifies the scope or category of the option. Common levels include `SOL_SOCKET` for socket-level options and protocol-specific levels like `IPPROTO_TCP` for TCP-specific options.
- `optname` (int): The option name, which specifies the specific option you want to set or modify. The meaning of `optname` depends on the `level` and may include options like `SO_REUSEADDR`, `SO_KEEPALIVE`, `TCP_NODELAY`, and more.
- `optval` (const void *): A pointer to the value you want to set for the specified option. This value should be of the appropriate data type for the option being set.
- `optlen` (socklen_t): The size of the `optval` buffer in bytes.

## Return Value

- `setsockopt()` returns 0 on success.
- On failure, it returns -1, and you can check `errno` for the error code to determine the reason for the failure.

## Code example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int main() {
    int serverSocket;
    int reuse = 1; // Enable socket reuse

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set the SO_REUSEADDR socket option
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        perror("setsockopt");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Rest of the code...
    // Bind, listen, accept, and handle incoming connections and data.

    // Close the socket when done
    close(serverSocket);

    return 0;
}

```
## Description

- In the code example, `setsockopt()` is used to enable the `SO_REUSEADDR` socket option, which allows the socket to reuse a local address that is still in use by another socket. This option is often used to avoid the "Address already in use" error when binding to a port that was used by a previous instance of a program.

- The `level` parameter is set to `SOL_SOCKET`, indicating that we are configuring a socket-level option. The `optname` parameter is set to `SO_REUSEADDR`, specifying the specific option to enable. The `optval` parameter is a pointer to the `reuse` variable, which contains the value `1` to enable the option. The `optlen` parameter is set to `sizeof(reuse)` to specify the size of the `reuse` variable.

A- fter configuring socket options, the code can proceed to bind the socket, listen for incoming connections, accept them, and handle them as needed.


## Additional sources

[linux manual page](https://linux.die.net/man/2/setsockopt)
