# Poll(...) Function

```c
#include <poll.h>

int poll(struct pollfd fds[], nfds_t nfds, int timeout);
```

## Purpose

The `poll()` function is used to wait for one or more file descriptors to become ready for I/O operations. It allows you to efficiently monitor multiple file descriptors in a single call.

## Usage

- Call `poll()` to monitor multiple file descriptors for events.
- `fds` is an array of `struct pollfd` structures, where each structure specifies the file descriptor to monitor and the events to watch for.
- `nfds` is the number of elements in the `fds` array.
- `timeout` is the maximum amount of time (in milliseconds) to wait for an event to occur. A value of -1 means wait indefinitely, while 0 means return immediately, and a positive value specifies a timeout.

## Parameters of poll function
fds:            An array of struct pollfd structures, each representing a file descriptor to monitor.
nfds:           The number of elements in the fds array.
timeout:        The timeout value in milliseconds. It specifies how long poll should wait for events to occur. A value of -1    
                means indefinitely, 0 means return immediately, and a positive value represents the maximum time to wait.

The struct pollfd structure is defined as follows:
```c
struct pollfd {
    int fd;       // The file descriptor to monitor.
    short events; // The events to monitor (e.g., POLLIN for read, POLLOUT for write).
    short revents; // The events that occurred (set by poll).
};
```

## Event flags for poll function
The poll function in C allows you to pass several event flags (variables) besides `POLLIN` to monitor different types of events on file descriptors. Here are some of the most commonly used event flags:

`POLLIN` : Indicates that you want to monitor the file descriptor for readability, i.e., you want to know when data is available to be read.

`POLLOUT`: Indicates that you want to monitor the file descriptor for writability, i.e., you want to know when you can write data to the file descriptor without it being full.

`POLLERR`: Indicates that you want to monitor the file descriptor for exceptional conditions, such as errors or hang-ups.

`POLLPRI`: Indicates that you want to monitor the file descriptor for urgent data.

`POLLHUP`: Indicates that you want to monitor the file descriptor for a hang-up condition, typically used for detecting when a connection is closed.

`POLLNVAL`: Indicates that you want to monitor the file descriptor for an invalid request. This is used when the file descriptor is not open or not valid for some reason.

You can combine these flags using bitwise `OR (|)` to monitor multiple events simultaneously. For example, if you want to monitor both read and write availability, you can use `POLLIN | POLLOUT`.

Here's an example of how you can set up a struct pollfd structure to monitor multiple events:
```c
struct pollfd fds[1];
fds[0].fd = your_file_descriptor;
fds[0].events = POLLIN | POLLOUT | POLLERR;
```
This struct pollfd will monitor the specified file descriptor for read, write, and error events. Depending on your application's requirements, you can choose which events to monitor and handle them accordingly when the poll function returns.

## Code example
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

int main() {
    struct pollfd fds[1];
    char buffer[256];
    
    int fd = STDIN_FILENO; // Monitor standard input (keyboard).

    fds[0].fd = fd;
    fds[0].events = POLLIN; // Monitor for read events.

    while (1) {
        int ready = poll(fds, 1, -1); // Wait indefinitely for an event.

        if (ready == -1) {
            perror("poll");
            exit(1);

        if (fds[0].revents & POLLIN) {
            // Data is available to read from stdin.
            ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                printf("Read: %s", buffer);
            } else if (bytes_read == 0) {
                printf("End of input.\n");
                break;
            } else {
                perror("read");
                exit(1);
            }
        }
    }

    return 0;
}
```
## Additional sources
[Linux manual page](https://man7.org/linux/man-pages/man2/poll.2.html)

[Video explanation and coding example](https://www.youtube.com/watch?app=desktop&v=O-yMs3T0APU&ab_channel=Johannes4GNU_Linux)

