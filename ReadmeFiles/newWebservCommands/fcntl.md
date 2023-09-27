# Fcntl

```c
#include <fcntl.h>

int fcntl(int file_descriptor, int command, ... /* optional argument */);
```

## Purpose
The fcntl function is a system call that stands for file control.
It is used to perform various operations on file descriptors, such as setting file status flags, changing file descriptor properties, and performing advisory file locking. 

## Usage
1. Changing File Descriptor Properties: Setting Flags: You can use fcntl to set or modify various file descriptor flags.
For example, you can set flags like O_NONBLOCK to make a file descriptor non-blocking or O_CLOEXEC to close the descriptor automatically when a new program is executed using exec.
Getting Flags: You can retrieve the current flags associated with a file descriptor using fcntl with F_GETFD (for file descriptor flags) or F_GETFL (for file status flags).

2. File Locking: fcntl can be used to establish advisory file locks using F_SETLK, F_SETLKW, and to check for locks with F_GETLK.
These locks help prevent multiple processes from simultaneously modifying the same data in a file.

3. Duplicating File Descriptors: You can use fcntl to duplicate a file descriptor with a new file descriptor value using F_DUPFD or F_DUPFD_CLOEXEC.
This is useful for creating additional references to the same open file or socket.

4. Other Control Operations: fcntl also provides various other control operations, which can be used for specific purposes.
 For example, on some systems, you can use F_SETSIG to set a signal to be sent when data becomes available for reading on a file descriptor.

## Function Parameters
`file_descriptor`: This is the integer file descriptor on which you want to perform the operation.
It can be a file descriptor for a regular file, socket, pipe, or other I/O device.

`command`: This is an integer value that specifies the operation you want to perform on the file descriptor.
It can take various values, and each value corresponds to a different operation. Some common commands include:

F_DUPFD: Duplicate the file descriptor.
F_GETFD: Get file descriptor flags.
F_SETFD: Set file descriptor flags.
F_GETFL: Get file status flags.
F_SETFL: Set file status flags.
F_GETLK: Get record lock information.
F_SETLK: Set or clear record lock.
F_SETLKW: Set or clear record lock, and block if blocked by another process.

`Optional Argument`: Depending on the specific command used, there may be an optional third argument associated with it.
For example, if you're setting a file status flag using F_SETFD or F_SETFL, you would provide an additional argument with the flag value.

## Return Value
When the fcntl operation succeeds without any errors, it typically returns 0 to indicate success.
If an error occurs during the fcntl operation, it returns -1, indicating that the operation failed.

Other Values: In some cases, when using specific commands (e.g., F_DUPFD_CLOEXEC), fcntl may return a value other than 0 or -1, which may represent success or an error condition.
The exact meaning of these values depends on the specific cmd and system-specific behavior.


## Code example
```c
//Setting a File Descriptor to Non-blocking Mode
#include <fcntl.h>  // For fcntl function and flag constants (e.g., O_NONBLOCK)
#include <unistd.h> // For open function
#include <iostream> // For error handling (optional)

int flags = fcntl(fd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(fd, F_SETFL, flags);

//File Locking
#include <fcntl.h>  // For fcntl function and lock-related constants (e.g., F_SETLK)
#include <unistd.h> // For file descriptor operations

struct flock lock;
lock.l_type = F_WRLCK;   // Write lock
lock.l_whence = SEEK_SET;
lock.l_start = 0;
lock.l_len = 100;         // Lock the first 100 bytes of the file

if (fcntl(fd, F_SETLK, &lock) == -1) {
    // Handle lock failure
}

//Duplicating File Descriptors
#include <fcntl.h>  // For fcntl function and flag constants (e.g., F_DUPFD)

int new_fd = fcntl(fd, F_DUPFD, 0);
```

## Additional sources

[linux manual page](https://linux.die.net/man/3/fcntl)
