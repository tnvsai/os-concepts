# 🎓 OS Concepts: Threads and Concurrency

## Overview
A **thread** is a lightweight process. Unlike processes (which have their own completely separate memory space), multiple threads created by the same process **share** the same memory space (data, code, and heap). Because they share memory, threads can communicate with each other much faster and easier than processes, but this sharing introduces complex challenges like **Race Conditions**.

---

## Core POSIX Threads (pthreads) Functions

### 1. `pthread_create()`
- **Purpose**: Spawns a new thread that begins executing a specific function.
- **Key Concept**: Instead of cloning the entire program from top to bottom (like `fork()`), `pthread_create` just tells the OS: *"Start running this specific function concurrently in the background."*

### 2. `pthread_join()`
- **Purpose**: Makes the main program wait until a specific thread finishes its task.
- **Key Concept**: This is the thread equivalent of `wait()` for processes. If the main program (main thread) exits before the other threads finish, the OS will violently kill all running threads and end the program.

---

## Concurrency Problems & Solutions

### The Race Condition
When multiple threads try to read from and write to the same shared memory variable at the exact same time, the final value can be unpredictable and wrong. This happens because high-level operations like `counter++` are actually multiple low-level machine instructions (Read, Add, Write), and threads can be interrupted halfway through.

### The Mutex (Mutual Exclusion)
A Mutex acts like a lock with a single key. 
When a thread wants to modify shared data (entering the "Critical Section"):
1. It calls **`pthread_mutex_lock()`** to grab the key.
2. If another thread already has the key, it is put to sleep until the key is returned.
3. It modifies the data safely.
4. It calls **`pthread_mutex_unlock()`** to return the key for others to use.

### Semaphores
A Semaphore is like a bouncer at a club. It is an integer counter that tracks how many identical resources are available. It allows a specific maximum number of threads (e.g., 2) into a critical section simultaneously. If the limit is reached, the next thread must gracefully wait for a spot (`sem_wait`).

### Producer-Consumer Problem
A classic synchronization challenge where a "Producer" thread generates data into a fixed-size buffer, and a "Consumer" thread simultaneously removes it. They must be carefully synchronized using Mutexes and Semaphores so the Producer sleeps if the buffer is entirely **full**, the Consumer sleeps if it's entirely **empty**, and they never corrupt the buffer.

---

## Programs in this Directory
- **`basic-thread.c`**: Demonstrates how to create a simple thread and join it, alongside signal handling to gracefully exit an infinite loop.
- **`thread-argument.c`**: Shows how to pass variables to a thread using generic `void*` pointers.
- **`race-condition.c`**: A broken program! Demonstrates what happens when two threads violently increment a shared counter at the same time without giving each other turns. It will output an unpredictable number.
- **`mutex-fix.c`**: The corrected version. Uses a Mutex lock to ensure only one thread can increment the counter at a time, guaranteeing the correct final result!
- **`semaphore_basic.c`**: Demonstrates exactly how a basic POSIX Semaphore stringently limits the maximum number of threads (e.g. 2 instances) allowed into a critical section.
- **`producer-consumer.c`**: Implements the classic bounded-buffer Producer-Consumer algorithm using Mutexes and Semaphores to coordinate data sharing completely safely.

*Tip: When compiling POSIX thread programs, you must link the pthread library by adding `-pthread` to your compile command:*
```bash
gcc program_name.c -o program_name -pthread
```
