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