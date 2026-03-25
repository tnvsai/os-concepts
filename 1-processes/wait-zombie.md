# 🧟‍♂️ Process Status: `wait()` and Zombies

> **🎯 Learning Objective:** Understand the lifecycle of a process, how a parent monitors its children to prevent system resource leaks, and what "Zombie" and "Orphan" processes are.

---

## 1. Introduction

When a process creates a child using `fork()`, both processes run independently. However, the parent often needs to:
*   Wait for the child to finish a specific task before continuing.
*   Check if the child succeeded or failed (reading its exit status).

To do this, the parent process uses the **`wait()`** system call.

---

## 2. The Concept of a "Zombie" Process 🧟

In the real world, when someone dies, they leave behind a body that needs to be properly handled. Operating systems work the exact same way.

When a child process finishes execution (by calling `exit()` or returning from `main()`), it dies. However, it doesn't immediately vanish from the system. It enters a state called a **Zombie Process** (or "Defunct"). 

### Why do Zombies exist?
The OS keeps the "corpse" of the process in the system's Process Table so that the parent has the opportunity to ask, *"How did my child die? Was it successful? Did it crash?"* 

The zombie holds a tiny bit of system memory containing its exit code. It will stay a zombie **forever** until the parent process formally acknowledges its death.

---

## 3. The `wait()` System Call: The Undertaker 🪦

The `wait()` system call is how a parent acknowledges a child's death and reads its exit status. 

When a parent calls `wait()`:
1.  **If the child is still running:** The parent pauses (blocks) and goes to sleep until the child finishes.
2.  **If the child is already dead (a Zombie):** The parent instantly reads the exit status, and the OS completely removes the zombie from the system.

> **⚠️ Crucial Rule:** A parent MUST `wait()` for its children. If a parent creates a child and then does a bunch of other work without ever calling `wait()`, the child becomes a zombie. If you create too many zombies, you fill up the Process Table and the computers crashes (cannot start new programs).

---

## 4. The Anatomy of `wait()` (C Code)

```c
#include <stdio.h>
#include <sys/wait.h> // Required for wait()
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: I am doing some work...\n");
        sleep(2); // Simulate work
        printf("Child: I am done.\n");
        return 0; // Child dies here
    } else {
        printf("Parent: I am waiting for my child...\n");
        
        int status;
        // The parent halts here until the child finishes
        wait(&status); 
        
        printf("Parent: My child is dead. I have collected its status.\n");
    }
    return 0;
}
```

### What is `int status`?
When you pass the address of an integer (`&status`) to `wait()`, the OS fills that integer with the child's exit code. You can use special macros like `WIFEXITED(status)` to check if the child died normally, or if it was killed by an external signal.

---

## 5. Orphan Processes 🧸

What happens if the **Parent dies FIRST** before the child finishes?

The child becomes an **Orphan**. But the OS hates orphans and hates unmanaged processes. In Linux, a system process called `init` (or `systemd` on modern systems, which is always PID 1) will automatically "adopt" the orphan.
`init` has a simple job: it sits in an infinite loop constantly calling `wait()`, ensuring that all orphans are properly cleaned up when they eventually die, preventing them from becoming permanent zombies.

---

## 6. Summary Comparison

| Term | Condition | Resolution |
| :--- | :--- | :--- |
| **Zombie** | Child is dead, but Parent is still alive and hasn't called `wait()`. | Parent must call `wait()`. |
| **Orphan** | Parent is dead, but Child is still alive. | System automatically adopts it (PID 1) and will `wait()` for it. |

---

## 7. Common Interview Questions

1.  **Do Zombie processes consume CPU?**
    *   *No. They are dead and use zero CPU. They only consume a slot in the operating system's process table.*
2.  **How do you kill a Zombie process?**
    *   *You can't kill a zombie (it's already dead!). You either make the parent call `wait()`, or you kill the parent process (which makes the zombie an orphan, which is then adopted and cleaned up by `init`).*
3.  **What is the difference between `wait()` and `waitpid()`?**
    *   *`wait()` waits for **any** child to finish. `waitpid()` allows the parent to wait for one **specific** child by providing its PID.*

---

👉 **Next Step:** Go look at `1-processes/wait.c` to see how exit statuses are captured!
