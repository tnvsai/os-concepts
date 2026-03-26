# 🎓 OS Concepts: Processes

## Overview
A process is a program in execution. It is the fundamental unit of work in modern operating systems. When you run an executable file, the OS creates a process, allocates memory, assigns a unique Process ID (PID), and schedules it to run on the CPU.

In Unix-like systems, processes are created and managed using a specific set of system calls.

---

## Key System Calls

### 1. `fork()`
- **Purpose**: Creates a new process by duplicating the calling process. The new process is called the "child", and the original process is the "parent".
- **Return Values**:
  - `> 0`: Retuned to the parent. The value is the PID of the newly created child.
  - `== 0`: Returned to the newly created child.
  - `< 0`: Fork failed (e.g., out of memory or process limit reached).
- **Key Concept**: The child inherits copies of the parent's memory, file descriptors, and registers, but it gets a different PID and its own separate memory space after the fork.

### 2. `exec()` Family (e.g., `execlp`)
- **Purpose**: Replaces the current process's memory space and program with a completely new program.
- **Key Concept**: Typical process creation involves a `fork()` followed immediately by an `exec()`. `fork()` makes the clone, and `exec()` tells the clone to stop running the same code and start running a specific executable (like `ls` or `grep`).

### 3. `wait()`
- **Purpose**: Suspends the execution of the calling process (usually the parent) until one of its children terminates.
- **Key Concept**: It is crucial for parents to wait for their children to collect their "exit status". If a parent does not wait, it can create "Zombie" processes.

---

## Important Process States

- **Running**: The process is actively executing instructions on the CPU.
- **Sleeping/Blocked**: The process is waiting for something (like I/O, user input, or a child to finish via `wait()`).
- **Zombie**: A process that has terminated, but its parent has not yet called `wait()` to collect its exit status. The process is dead, but its entry remains in the OS process table.
- **Orphan**: A process whose parent has terminated while the child is still running. In Linux, orphan processes are usually adopted by the `init` process (PID 1), which will automatically `wait()` on them when they die.

---

## Programs in this Directory
- **`fork-basic.c`**: Demonstrates the absolute basics of the `fork()` system call, printing different messages based on the return value.
- **`fork-multiple.c`**: Demonstrates the exponential growth of processes when `fork()` is called multiple times in a sequence.
- **`wait.c`**: Shows the correct way for a parent to wait for a child and collect its exit status.
- **`exec-basic.c`**: Demonstrates combining `fork()` and `exec()` to launch an external command (`ls -l`) from within a C program.

*Tip: Compile the C programs using `gcc program_name.c` and execute the generated `./a.out` to see the outputs.*
