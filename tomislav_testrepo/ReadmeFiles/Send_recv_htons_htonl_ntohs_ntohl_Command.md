## Send
The send function is used to send data over a socket, typically in socket programming scenarios where you need to transmit data from one endpoint to another.
```bash
#include <sys/socket.h>

ssize_t send(int socket, const void *data, size_t length, int flags);
```
socket: This parameter is the socket descriptor returned by the socket function when you create a socket and establish a connection.

data: It is a pointer to the data you want to send. The data should be stored in memory, and you provide a pointer to this memory location.

length: Specifies the length of the data to send, typically the number of bytes in the data buffer.

flags: The flags parameter is an optional parameter that allows you to specify additional options or behaviors for the send operation. Commonly used flags include 0 (for standard behavior) and flags like MSG_NOSIGNAL (to prevent the generation of a SIGPIPE signal on errors).

The send function returns the number of bytes sent on success or -1 if an error occurs.

## Recv
The recv function is used to receive data from a socket. It's commonly used to retrieve data that has been sent to your application.
```bash
#include <sys/socket.h>

ssize_t recv(int socket, void *buffer, size_t length, int flags);
```
socket: This parameter is the socket descriptor returned by the socket function when you create a socket and establish a connection.

buffer: It is a pointer to the memory buffer where the received data will be stored. You should allocate sufficient memory for the data to be received.

length: Specifies the maximum number of bytes to receive and the size of the buffer you've provided.

flags: The flags parameter is an optional parameter that allows you to specify additional options or behaviors for the recv operation. Commonly used flags include 0 (for standard behavior) and flags like MSG_WAITALL (to block until the full requested data is received).

The recv function returns the number of bytes received on success, 0 if the other side has closed the connection (in a graceful manner), or -1 if an error occurs.

## Htons and Htonl
```bash
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
```
htons "host to network short"
It is used to convert a 16-bit integer from the host byte order to the network byte order.
This function is primarily used for converting port numbers in network-related code.

htonl "host to network long"
It is used to convert a 32-bit integer from the host byte order to the network byte order.
This function is commonly used for converting IP addresses and other 32-bit values.


## Ntohs and Ntohl
```bash
#include <arpa/inet.h>

uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```
ntohs "network to host short"
It is used to convert a 16-bit integer from the network byte order to the host byte order.
This function is used to interpret port numbers received from the network.

ntohl "network to host long"
It is used to convert a 32-bit integer from the network byte order to the host byte order.
This function is used to interpret IP addresses and other 32-bit values received from the network.
