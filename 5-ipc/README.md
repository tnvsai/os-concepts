# 🎓 OS Concepts: Inter-Process Communication (IPC)

## Overview
Because operating systems isolate processes in their own private memory spaces for security and stability, two different processes cannot normally talk to each other or share variables. **Inter-Process Communication (IPC)** refers to the specific mechanisms the OS provides to allow processes to safely exchange data.

---

## The Pipe (`|`) Mechanism

### What is a Pipe?
A Pipe is the oldest and most fundamental IPC mechanism in Unix-like systems. It acts as a one-way (unidirectional) data channel between two related processes (usually a parent and its hijacked child). 
Data written to the "write end" of the pipe can be safely read from the "read end".

### Key System Calls
1. **`pipe(int fd[2])`**: Creates the pipe in the OS kernel and returns two File Descriptors:
    - `fd[0]`: The Read End.
    - `fd[1]`: The Write End.
2. **`dup2(old_fd, new_fd)`**: Duplicates a file descriptor, violently overwriting the target. It is used to trick a program into reading from/writing to a pipe instead of the keyboard/screen! 

### How the Linux Command Line uses Pipes
When you type a command like `ls -l | grep ".txt"` in Bash:
1. The Shell creates a `pipe()`.
2. The Shell `fork()`s twice to create Process A (`ls`) and Process B (`grep`).
3. Inside Process A: It uses `dup2()` to replace its Standard Output (screen) with `fd[1]` (the write end of the pipe).
4. Inside Process B: It uses `dup2()` to replace its Standard Input (keyboard) with `fd[0]` (the read end of the pipe).
5. The kernel acts as the secure middleman, funneling bytes from A's output directly into B's input!

---

## Programs in this Directory
- **`pipe-shell.c`**: An absolute classic. It simulates exactly what the Bash shell does when you type `ls | wc -l`. It creates a pipe, forks two children, wires their standard input/output directly to the pipe, and forces them to work together.
