# 🎓 OS Concepts: POSIX Signals

## Overview
A **Signal** is a software interrupt delivered to a process by the Operating System. It is the most primitive form of Inter-Process Communication (IPC). Signals tell a process that a specific event has occurred (like a user pressing Ctrl+C, a timer expiring, or a segmentation fault).

---

## Key Concepts

### 1. Asynchronous Execution
Signals can arrive at **absolutely any time** during a program's execution. It doesn't matter what line of C code the CPU is currently executing—if a signal arrives, the process drops everything immediately to handle it.

### 2. Default Actions
Every signal has a default action defined by the OS. The most common actions are:
- **Terminate**: The process is killed immediately.
- **Ignore**: Nothing happens.
- **Core Dump**: The process is killed and a memory snapshot is saved for debugging (e.g., `SIGSEGV` / Segmentation Fault).
- **Stop/Continue**: Pause or resume the process.

### 3. Custom Handlers (`signal()`)
A programmer can ask the OS to ignore the default action and instead run a custom function when a specific signal arrives. This is called "Catching" or "Handling" a signal.
- Note: You *cannot* catch or ignore `SIGKILL` (Signal 9). The OS guarantees that if you send a `SIGKILL`, the process dies instantly.

### 4. Sending Signals (`kill()`)
Despite its violent name, the `kill()` system call is just used to send **any** signal to **any** process. `kill(pid, SIGINT)` asks that process to interrupt itself, while `kill(pid, SIGSTOP)` pauses it.

---

## Common Signals
- `SIGINT` (2): Interrupt from keyboard (Ctrl+C). Default: Terminate.
- `SIGKILL` (9): Immediate kill signal. Cannot be caught or ignored!
- `SIGSEGV` (11): Invalid memory reference (Segmentation Fault). Default: Core dump.
- `SIGALRM` (14): Timer signal. Default: Terminate.
- `SIGTERM` (15): Polite termination signal. Default: Terminate.

---

## Programs in this Directory
- **`signal_basic.c`**: Demonstrates how to override the default action of Ctrl+C (`SIGINT`) to print a custom message instead of crashing the program.
- **`signal-kill.c`**: A very simple demonstration of one process sending a signal to another using the `kill()` function.
