# ntohs(...) Function

```c
#include <arpa/inet.h>

unsigned short ntohs(unsigned short netshort);

```

## Purpose
- `ntohs`  is a crucial networking function used to convert a 16-bit integer (e.g., a port number) from network byte order to the host byte order.

## Usage
- Provide a 16-bit integer (e.g., a port number) in network byte order as the function argument.
- The function checks if the host byte order is different from the network byte order (which is typically big-endian).
- If they are different, ntohs swaps the byte order to convert the value to host byte order.
- If they are the same (host byte order is already big-endian), ntohs may be a no-op (no change).

## Function Parameters
- `netshort` (unsigned short):
This parameter represents the 16-bit integer value in network byte order that you want to convert to host byte order.

## Return Value
- `unsigned short`: The ntohs function returns the converted value in host byte order.

## Code example
```c
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    unsigned short networkPort = 0x3039;            // Network byte order (port 12345 in hexadecimal)
    unsigned short hostPort = ntohs(networkPort);    // Convert to host byte order

    printf("Network byte order: %hu\n", networkPort);
    printf("Host byte order: %hu\n", hostPort);

    return 0;
}
```

## What is the differnce to htonl ?
In summary, `ntohs` is used when receiving data from the network and converting it to the local machine's byte order, while `htons` is used when preparing data for network transmission by converting it to network byte order. They serve complementary roles in ensuring proper data representation when dealing with network communication.

## Additional sources

[linux manual page](https://linux.die.net/man/3/ntohs)