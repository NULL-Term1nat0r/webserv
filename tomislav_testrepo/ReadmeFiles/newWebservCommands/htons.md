# htons(...) Function

```c
#include <arpa/inet.h>

short unsigned htons(short unsigned port_number);

```

## Purpose
- `htons` is an essential networking function used to convert a 16-bit integer (e.g., a port number) from the host byte order to network byte order. This conversion is crucial when working with network protocols to ensure that data is consistently represented across different computer architectures.

## Usage
- Provide a 16-bit integer (e.g., a port number) as the function argument.
- The function checks if the host byte order is different from the network byte order (which is typically big-endian).
- If they are different, htons swaps the byte order to convert the value to network byte order.
- If they are the same (host byte order is already big-endian), htons may be a no-op (no change).

## Function Parameters
- `hostshort` (unsigned short): 
This parameter represents the 16-bit integer value that you want to convert from the host byte order to network byte order.



## Return Value
- unsigned short: The `htons` function returns the converted value in network byte order.

## Code example
```c
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    unsigned short hostPort = 12345;            // Host byte order
    unsigned short networkPort = htons(hostPort); // Convert to network byte order

    printf("Host byte order: %hu\n", hostPort);
    printf("Network byte order: %hu\n", networkPort);

    return 0;
}
```
## Additional sources

[linux manual page](https://linux.die.net/man/3/htons)