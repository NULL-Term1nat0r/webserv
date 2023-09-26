# Poll(...) Function

```c
#include <poll.h>

int poll(struct pollfd fds[], nfds_t nfds, int timeout);
```

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
        }

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

