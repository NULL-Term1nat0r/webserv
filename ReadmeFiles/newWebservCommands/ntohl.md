# ntohl(...) Function

```c
#include <arpa/inet.h>

unsigned long ntohl(unsigned long netlong);

```

## Purpose
- `ntohl`  is a crucial networking function used to convert a 32-bit integer (e.g., an IP address) from network byte order to the host byte order.

## Usage
- Provide a 32-bit integer (e.g., an IP address) in network byte order as the function argument.
- The function checks if the host byte order is different from the network byte order (which is typically big-endian).
- If they are different, ntohl swaps the byte order to convert the value to the host byte order.
- If they are the same (host byte order is already big-endian), ntohl may be a no-op (no change).

## Function Parameters
- `netlong` (unsigned long):
This parameter represents the 32-bit integer value in network byte order that you want to convert to host byte order.

## Return Value
- `unsigned long`: 
The ntohl function returns the converted value in host byte order.

## Code example
```c
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    unsigned long networkIP = 0x0101A8C0;        // Network byte order (192.168.1.1 in hexadecimal)
    unsigned long hostIP = ntohl(networkIP);      // Convert to host byte order

    printf("Network byte order: %u\n", networkIP);
    printf("Host byte order: %u\n", hostIP);

    return 0;
}
```

## Additional sources

[linux manual page](https://linux.die.net/man/3/ntohl)