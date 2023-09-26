#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 5;  // Set a timeout of 5 seconds
    timeout.tv_usec = 0;

    printf("Please type something within 5 seconds:\n");

    int readyDescriptors = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (readyDescriptors == -1) {
        perror("select");
        return 1;
    } else if (readyDescriptors == 0) {
        printf("No data received within the timeout.\n");
    } else {
        printf("Data is available to read from stdin.\n");

        // Read and print the user's input
        char inputBuffer[256];
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        printf("You typed: %s", inputBuffer);
    }

    return 0;
}