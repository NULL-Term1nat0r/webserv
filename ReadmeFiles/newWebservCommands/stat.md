# Stat

```c
#include <sys/stat.h>

int stat(const char *path, struct stat *buf);
```

## Purpose
The stat function in C/C++ is used to retrieve information about a file, such as its size, permissions, modification timestamp, and more.
It allows you to query various attributes of a file on the filesystem.

## Function Parameters
- `const char *path`: This parameter is a pointer to a null-terminated string that represents the path to the file you want to query.
The path argument is a file system path that can be either an absolute path or a relative path from the current working directory.
It should point to the file whose attributes you want to retrieve.

- `struct stat *buf`: This parameter is a pointer to a struct stat variable where the file's attributes will be stored.
The struct stat type is defined in the <sys/stat.h> header and contains various fields to hold information about the file, such as its size, permissions, timestamps, and more.
You need to declare a struct stat variable in your code, and then pass a pointer to that variable as the buf argument to stat.
After calling stat, you can access the file attributes using the fields within the struct stat variable.

## Return Value


## Code example
```c

```
## Description


## Additional sources

[linux manual page](https://linux.die.net/man/2/stat)
