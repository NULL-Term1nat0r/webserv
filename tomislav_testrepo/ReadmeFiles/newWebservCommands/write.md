# `write(...)` Function

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

## Purpose
- `write()` is used to write data to a file descriptor, which can include regular files, pipes, sockets, or other output streams. It is commonly used to send data to file-like destinations.

## Usage
- Call `write()` to write data to a file descriptor. You specify the file descriptor (`fd`), a pointer to the data to be written (`buf`), and the number of bytes to write (`count`).

## Function Parameters
- `fd` (int): The file descriptor representing the destination where data is to be written.
- `buf` (const void *): A pointer to the data that you want to write.
- `count` (size_t): The number of bytes of data to write.

## Return Value
- `write()` returns the number of bytes written on success. This value may be less than `count` if not all the data could be written in a single operation.
- On failure, it returns `-1`, and you can check `errno` for the error code to determine the reason for the failure.

## Code example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fileDescriptor;
    const char *message = "Hello, File!";
    ssize_t bytesWritten;

    // Open a file or create it if it doesn't exist

    // Write data to the file descriptor
    bytesWritten = write(fileDescriptor, message, strlen(message));
    if (bytesWritten == -1) {
        perror("write");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }

    printf("Wrote %ld bytes: %s\n", bytesWritten, message);

    // Rest of the code...
    // Close the file descriptor and perform other operations as needed.

    return 0;
}
```

## Description
- In the code example, `write()` is used to write the message "Hello, File!" to a file descriptor, which represents a file or output stream. The `fd` parameter represents the file descriptor, `buf` points to the message, and `count` specifies the number of bytes to write.

- The function returns the number of bytes written, which may be less than the requested `count` if not all the data is written in a single operation.

- After writing data, the code can continue with other file operations or additional tasks as needed.

## Additional Resources

[linux manual page](https://linux.die.net/man/2/write)