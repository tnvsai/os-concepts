# 🎓 OS Concepts: Filesystems & Low-Level I/O

## Overview
A filesystem is the methods and data structures that an operating system uses to keep track of files on a disk or partition. It provides the mechanism for data to be retrieved quickly and securely.

When you write a C program, you often use high-level standard library functions like `fopen()`, `fprintf()`, and `fread()`. However, these are just wrappers around the actual **low-level POSIX System Calls** directly provided by the OS Kernel.

---

## File Descriptors
Everything in Unix is a file! When the OS opens a file (or a pipe, or a network socket, or a hardware device), it gives the process a small integer called a **File Descriptor (FD)** to keep track of it.

By default, every newly started process has three standard File Descriptors automatically opened for it:
- **0 - Standard Input (`STDIN_FILENO`)**: The keyboard.
- **1 - Standard Output (`STDOUT_FILENO`)**: The screen output.
- **2 - Standard Error (`STDERR_FILENO`)**: The screen error output.

## Core POSIX I/O System Calls

### 1. `open(char *filename, int flags, int mode)`
- Asks the OS to establish a connection to a file.
- **Flags**: `O_RDONLY` (Read Only), `O_WRONLY` (Write Only), `O_CREAT` (Create if missing), `O_TRUNC` (Empty the file first), `O_APPEND` (Add to the end).
- **Return**: A new File Descriptor (e.g., `3`), or `-1` if failed.

### 2. `read(int fd, void *buffer, size_t count)`
- Asks the OS to pull `count` bytes of data from the hard drive (via `fd`) into the provided RAM `buffer`.
- **Return**: The exact number of bytes successfully read. Returning `0` means End Of File (EOF).

### 3. `write(int fd, void *buffer, size_t count)`
- Asks the OS to write `count` bytes from the RAM `buffer` onto the hard drive (via `fd`).

### 4. `close(int fd)`
- Tells the kernel to break the connection to the file and free up the integer ID.

---

## Programs in this Directory
- **`copy-file.c`**: Demonstrates the classic `read()`/`write()` loop used by commands like `cp` to copy binary data chunk-by-chunk.
- **`read-file.c`**: Very simple demonstration of `open()` and `read()`.
- **`write-syscall.c`**: Very simple demonstration of writing strings to a file using pure system calls (no `fprintf`).
- **`redirect_output.c` / `redirect_input.c`**: Demonstrates how you can use `dup2()` to overwrite `STDOUT_FILENO` (1) with a regular file descriptor. This is exactly how the Bash shell implements `ls > output.txt` and `wc < input.txt`.
- **`shell.c`**: An implementation combining process execution with I/O redirection.
