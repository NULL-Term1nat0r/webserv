# htonl(...) Function

```c
#include <arpa/inet.h>

unsigned long htons(unisgned long port_number);

```

## Purpose
- `htonl` is a crucial networking function used to convert a 32-bit integer (e.g., an IP address) from the host byte order to network byte order.

## Usage
- Provide a 32-bit integer (e.g., a port number) as the function argument.
- The function checks if the host byte order is different from the network byte order (which is typically big-endian).
- If they are different, htons swaps the byte order to convert the value to network byte order.
- If they are the same (host byte order is already big-endian), htons may be a no-op (no change).

## Function Parameters
- `hostlong` (unsigned long): 
This parameter represents the 16-bit integer value that you want to convert from the host byte order to network byte order.

## Return Value
- unsigned long: The `htonl` function returns the converted value in network byte order.

## Code example
```c
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    unsigned long hostIP = 0xC0A80101;            // Host byte order (192.168.1.1 in hexadecimal)
    unsigned long networkIP = htonl(hostIP);       // Convert to network byte order

    printf("Host byte order: %u\n", hostIP);
    printf("Network byte order: %u\n", networkIP);

    return 0;
}
```
## Additional sources

[linux manual page](https://linux.die.net/man/3/htonl)