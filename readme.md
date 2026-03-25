# 🚀 OS Concepts Journey

Welcome to the **OS Concepts** repository! This project serves as a practical, code-first guide to understanding how modern Operating Systems (like Linux) work under the hood.

Here you will find explanations, analogies, and heavily commented C programs to help you learn and retain core OS concepts.

---

## 📚 Learning Path

Navigate through the folders in the following order to build your understanding step-by-step:

### 1. Processes (`1-processes/`)
Processes are the fundamental unit of execution. Learn how they are born, how they run, and how they die.
- **Concepts**: `fork()`, `exec()`, Process IDs (PIDs), Parent/Child relationships.
- **Status Issues**: Zombies, Orphans, `wait()`.
- **Start Here**: Read [`1-processes/all.md`](1-processes/all.md) for a high-level overview, then explore the `.c` files.

### 2. Threads (`2-threads/`) *[Coming Soon]*
Lighter than processes, threads share memory. Learn how to achieve concurrency within a single application.

### 3. Scheduling (`3-scheduling/`) *[Coming Soon]*
How does the OS decide which process gets the CPU? Learn about scheduling algorithms.

### 4. Memory (`4-memory/`) *[Coming Soon]*
Paging, Virtual Memory, and how processes share physical RAM safely.

### 5. IPC (Inter-Process Communication) (`5-ipc/`) *[Coming Soon]*
How processes talk to each other safely using pipes, shared memory, and message queues.

### 6. Filesystems (`6-filesystems/`)
How does the OS interact with disks and files?
- **Concepts**: File Descriptors, `open()`, `read()`, `write()`.
- **Explore**: Start with the `.c` files to see low-level I/O in action.

### 7. Signals (`7-signals/`) *[Coming Soon]*
Software interrupts used for asynchronous communication between processes.

### 8. Kernel (`8-kernal/`) *[Coming Soon]*
Diving deeper into the absolute core of the operating system.

---

## 💻 How to Run the Code

All examples are written in standard C and use POSIX system calls. They are designed to run on a Linux or macOS environment.

1.  **Open your terminal.**
2.  **Navigate** to the specific folder (e.g., `cd 1-processes`).
3.  **Compile** the C program using `gcc` (the GNU C Compiler). We recommend using the `-Wall` flag to see all warnings:
    ```bash
    gcc -Wall fork-basic.c -o fork-basic
    ```
4.  **Run** the compiled executable:
    ```bash
    ./fork-basic
    ```

## 🧠 Philosophy

*   **Read the comments**: The C code is heavily commented specifically to explain *why* something is being done, not just *what* it is doing.
*   **Tinker**: Don't just run the code. Change a `sleep()` timer, comment out a `wait()` call, and see exactly how it breaks! That's the best way to learn OS operations.
