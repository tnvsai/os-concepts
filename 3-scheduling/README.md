# 🎓 OS Concepts: CPU Scheduling

## Overview
CPU Scheduling is the process by which an operating system decides which process in the "Ready Queue" should get to execute on the CPU next. The goal of a scheduling algorithm is usually to maximize efficiency, minimize wait times, or ensure all processes get a fair share of the CPU.

---

## Key Terms Explained

1. **Burst Time (BT)**: The exact amount of time (in milliseconds) a process needs the CPU to complete its entire task.
2. **Arrival Time (AT)**: The time at which a process arrives in the system's "Ready Queue" asking for the CPU. (Note: Many basic examples assume AT = 0 for all processes).
3. **Completion Time (CT)**: The exact system time when the process finally finishes executing.
4. **Turnaround Time (TAT)**: The total time a process spends in the system from arrival to completion. `TAT = Completion Time - Arrival Time`. (If AT is 0, then TAT = CT).
5. **Waiting Time (WT)**: The total time a process spends sitting in the "Ready Queue" doing nothing, waiting for its turn. `WT = Turnaround Time - Burst Time`.
6. **Time Quantum**: A fixed slice of time explicitly used in the "Round Robin" algorithm.

---

## Scheduling Algorithms in this Directory

### 1. First-Come, First-Served (FCFS) (`fcfs.c`)
- **Concept**: The simplest algorithm. The process that arrives first gets to execute first until it finishes.
- **Pros**: Easy to implement.
- **Cons**: "Convoy Effect". A very long process at the front of the line will drastically delay all the short, fast processes behind it.

### 2. Priority Scheduling (`priority.c`)
- **Concept**: Each process is assigned a "Priority" number. The process with the highest priority gets the CPU next.
- **Pros**: Important tasks get done immediately.
- **Cons**: "Starvation". A very low-priority process might sit in the queue forever if high-priority processes keep arriving. (Fixed with "Aging", gradually increasing priority over time).

### 3. Round Robin (`round_robin.c`)
- **Concept**: Designed for Time-Sharing systems. Each process is given a tiny "Time Quantum" (e.g., 2ms). If a process isn't finished in 2ms, it is violently kicked off the CPU and put at the back of the queue, and the next process gets 2ms.
- **Pros**: Extremely fair. No process starves. Great responsiveness for interactive tasks.
- **Cons**: A lot of overhead from constantly switching between processes ("Context Switching").

*Tip: These programs simulate the scheduling algorithms logically. They calculate the math behind Waiting Time and Turnaround Time using hardcoded process arrays.*
