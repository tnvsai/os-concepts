# 🎓 OS Concepts: Memory Management

## Overview
Memory Management is the function of the OS that handles the primary memory (RAM). It keeps track of every byte of memory, decides which processes get memory and when, and simulates more memory than physically exists using a concept called **Virtual Memory**.

---

## Key Concepts

### 1. Paging
- Modern operating systems divide physical memory (RAM) into fixed-size blocks called **Frames**.
- They divide a process's logical memory (the program's code and data) into blocks of the exact same size called **Pages**.
- Because Pages and Frames are the same size, any Page can be placed into any available Frame. This completely eliminates external fragmentation (where memory is wasted in tiny unusable chunks between programs).

### 2. Page Faults
- A process does not need all of its Pages in RAM at once to run. The OS only loads the Pages that are actively being used. The rest stay safely on the hard drive (in the Swap file).
- Every time a process tries to access a Page that is NOT currently loaded in a RAM Frame, the CPU triggers a **Page Fault**. 
- The OS pauses the process, finds an empty Frame, loads the missing Page from the hard drive into RAM, and then restarts the process's instruction.

### 3. Page Replacement
- What happens if a Page Fault occurs, but the RAM is completely full (there are no empty Frames)? 
- The OS must evict (kick out) an old Page from RAM to make room for the new one. This is exactly what **Page Replacement Algorithms** decide! The goal is to minimize total Page Faults by smartly guessing which Pages we won't need anytime soon.

---

## Page Replacement Algorithms in this Directory

### 1. First-In, First-Out (FIFO) (`fifo.c`)
- **Concept**: The OS keeps track of when each Page was brought into memory. When an eviction is forced, the OLDEST page is universally chosen and kicked out.
- **Pros**: Incredibly simple to implement (just a queue).
- **Cons**: "Belady's Anomaly." Sometimes, giving a process MORE memory frames actually causes MORE page faults, because FIFO ignores how often a page is being actively used. 

### 2. Least Recently Used (LRU) (`lru.c`)
- **Concept**: The OS keeps track of the exact time each Page was last mathematically accessed. When eviction is forced, the page that hasn't been touched for the longest time is kicked out. 
- **Pros**: Excellent performance in the real world. Acknowledges that if a page was just used, it will likely be used again soon.
- **Cons**: Requires complex hardware support or expensive overhead to track the "last access time" of every single byte of memory.

### 3. Paging Simulator (`paging_sim.c`)
- **Concept**: A simple demonstration of reading a logical Page number, and multiplying it by the Page Size to find its physical location in memory.
