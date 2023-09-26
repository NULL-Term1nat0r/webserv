# select(...) Function

```c
#include <sys/select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

```

## Purpose
- `select` function is a crucial system call used for I/O multiplexing in network and file I/O operations. It allows a program to monitor multiple file descriptors for various I/O events and efficiently manage them.

## Usage
The `select` function is used for I/O multiplexing in network and file I/O operations. Its primary purpose is to monitor multiple file descriptors simultaneously and efficiently determine when I/O operations are possible or when exceptional conditions occur. Below are some common use cases and the usage of the `select` function:

**Handling Multiple I/O Channels**

One of the primary use cases of `select` is to handle multiple I/O channels within a single thread. It allows a program to monitor multiple sockets or file descriptors for read, write, or exception events without the need for separate threads for each channel.

**Socket Programming**

In network programming, `select` is often used to manage multiple network connections. For example, a server that needs to handle multiple client connections can use `select` to determine when data is available to read from or write to each connected socket.

**Non-blocking I/O**

`select` is commonly used with non-blocking sockets or file descriptors. By monitoring write availability with `writefds`, you can avoid blocking when writing data to sockets or files.

**Implementing Timeouts**

`select` allows you to specify a timeout using the `timeout` parameter. This is useful when you want to wait for I/O events for a limited duration and then proceed with other tasks if no events occur within the specified time.

**Handling Exceptional Conditions**

The `exceptfds` parameter allows you to monitor for exceptional conditions, such as out-of-band data or socket errors. This is valuable in scenarios where you need to react to unusual events on file descriptors.

**Resource Efficiency**

`select` is efficient in terms of resource usage compared to creating multiple threads or processes to handle I/O. It can efficiently manage a large number of file descriptors with a single thread.

**Cross-Platform Compatibility**

`select` is a standard system call available on various platforms, making it a portable solution for managing I/O multiplexing in network and file I/O operations.

Overall, the `select` function is a versatile and widely used tool for managing I/O events and making efficient use of system resources in applications involving multiple I/O channels, such as servers, network daemons, and interactive applications.

## Function Parameters
- `nfds` (int):
  - Purpose: The highest-numbered file descriptor in any of the sets plus 1.
  - Description: This parameter represents the upper bound of the file descriptors to be monitored. It defines the range of file descriptors that `select` will consider for monitoring.

- `readfds` (fd_set*):
  - Purpose: A set of file descriptors to monitor for readable data.
  - Description: This is a pointer to a set of file descriptors that you want to monitor for the availability of data to be read. When data is available for reading on any of the file descriptors in this set, `select` will return.

- `writefds` (fd_set*):
  - Purpose: A set of file descriptors to monitor for write availability.
  - Description: This is a pointer to a set of file descriptors that you want to monitor for the ability to write data. When it's possible to write data to any of the file descriptors in this set without blocking, `select` will return.

- `exceptfds` (fd_set*):
  - Purpose: A set of file descriptors to monitor for exceptional conditions.
  - Description: This is a pointer to a set of file descriptors for which you want to monitor exceptional conditions. Exceptional conditions can include errors on the file descriptors. If any of the file descriptors in this set experience an exceptional condition, `select` will return.

- `timeout` (struct timeval*):
  - Purpose: A pointer to a struct specifying the maximum time for the function to block, or NULL for blocking indefinitely.
  - Description: This parameter allows you to set a timeout for the `select` call. If you pass a non-NULL `timeout` value, `select` will block for the specified amount of time, and if no events occur within the specified time, it will return. If you pass a NULL `timeout`, `select` will block indefinitely until an event occurs.

## Return Value
- `int`:
The `select` function returns the total number of file descriptors that are ready for I/O (i.e., the number of file descriptors in the sets that have events pending). If an error occurs, it returns -1.

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