# 🎓 OS Concepts: The Kernel

## Overview
The Kernel is the core, central component of an Operating System. It is the first program loaded into memory when the computer boots, and it stays in memory until the computer is shut down.

It acts as the essential bridge between the physical hardware (CPU, Memory, Disks, Keyboards, Network Cards) and the software applications (Web Browsers, Shells, Games).

---

## User Space vs. Kernel Space

Modern Operating Systems aggressively separate the computer's memory and execution permissions into two distinct zones to guarantee stability and security:

### 1. User Space (Ring 3)
- This is where ALL normal applications run (your terminal, browser, Python scripts, and the C programs in this repository).
- Programs here have **severely restricted privileges**. 
- They CANNOT directly touch hardware. They CANNOT read another process's memory. They CANNOT create a new process on their own.

### 2. Kernel Space (Ring 0)
- This is where the core OS code runs.
- The Kernel has **absolute, unrestricted privileges**.
- It can execute any mathematical CPU instruction, directly read/write physical RAM addresses, and control all hardware devices.

---

## The System Call (Syscall)
If a User Space program acts in a restricted sandbox, how does it ever manage to write a file to the hard drive, print to the screen, or allocate memory?

It must politely ask the Kernel to do it on its behalf using a **System Call**.

1. **The Request**: Your C program calls a function like `write()` or `fork()`.
2. **The Context Switch**: The CPU triggers a "software interrupt" (a trap). It instantly pauses your program, saves its state, and elevates its privilege level to Ring 0 (Kernel Mode).
3. **The Execution**: The OS Kernel safely performs the requested action (like spinning the hard drive to write data).
4. **The Return**: The CPU drops privileges back down to Ring 3 (User Mode) and returns control, along with the result, right back to your C program.

*Tip: Almost every topic covered in the previous directories (Processes, Scheduling, Memory Management, File I/O, IPC) are entirely orchestrated by the Kernel through system calls!*
