# Socket(...) Function

```c
#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);

```

## Parameters of poll function
- `domain` (int): 
Specifies the communication domain or family, defining the addressing structure to be used (e.g., AF_INET for IPv4, AF_INET6 for IPv6, AF_UNIX for local sockets).

- `type` (int): 
Specifies the socket type, determining the communication semantics (e.g., SOCK_STREAM for TCP, SOCK_DGRAM for UDP, SOCK_RAW for raw sockets).

- `protocol` (int): 
Specifies the specific protocol to use, with 0 indicating the system should choose based on `domain` and `type`.

## Return Value
- The `socket` function returns a file descriptor (an integer) referring to the created socket on success, or -1 on failure.

## Commonly used flags
- `AF_INET`: Address family for IPv4.
- `AF_INET6`: Address family for IPv6.
- `AF_UNIX` or `AF_LOCAL`: Address family for local (Unix domain) sockets.
- `SOCK_STREAM`: Socket type for TCP communication.
- `SOCK_DGRAM`: Socket type for UDP communication.
- `SOCK_RAW`: Socket type for raw network protocol access.
- `IPPROTO_TCP`: Protocol for TCP.
- `IPPROTO_UDP`: Protocol for UDP.
- `IPPROTO_SCTP`: Protocol for SCTP (Stream Control Transmission Protocol).

## Code example
```c
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int sockfd;

    // Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("TCP socket created successfully!\n");

    // Close the socket when done
    close(sockfd);

    return 0;
}
```
## Additional sources

[linux manual page](https://man7.org/linux/man-pages/man2/socket.2.html)

