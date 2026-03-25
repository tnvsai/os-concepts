/**
 * 🎓 OS CONCEPTS: The Basics of fork()
 * 
 * DESCRIPTION:
 * This program demonstrates the most fundamental usage of the fork() 
 * system call. It shows how a single program duplicates itself into 
 * two separate but identical processes.
 */

#include <stdio.h>
#include <unistd.h> // Required for fork(), getpid(), and sleep()

int main() {
    printf("--- Original Program Started (PID: %d) ---\n", getpid());

    /*
     * 🧠 WHAT HAPPENS HERE:
     * fork() creates an exact clone of this process.
     * The OS assigns a new Process ID (PID) to the clone.
     * Both processes will resume execution on the very next line.
     */
    pid_t pid = fork();

    /*
     * 🧠 HOW TO TELL THEM APART:
     * We use the return value of fork() to figure out "who am I?"
     * 
     * If pid == 0:  The current process is the newly created CHILD.
     * If pid > 0:   The current process is the original PARENT.
     * If pid < 0:   The system failed to create a child (rare, but possible).
     */

    if (pid < 0) {
        // This is error handling code.
        fprintf(stderr, "Fatal error: failed to fork!\n");
        return 1;
    } 
    else if (pid == 0) {
        // ==========================================
        //         THIS IS THE CHILD'S CODE
        // ==========================================
        // The child process receives '0' from fork.
        // getpid() gives us the child's own ID.
        printf("👶 I am the CHILD process! My PID is %d\n", getpid());
    } 
    else {
        // ==========================================
        //        THIS IS THE PARENT'S CODE
        // ==========================================
        // The parent process receives the actual positive PID of the child.
        // getpid() gives us the parent's ID.
        printf("👨 I am the PARENT process! My PID is %d. I just gave birth to child %d\n", getpid(), pid);
    }

    // Both processes will eventually reach this line!
    // But they will each print their own separate PID here.
    printf("🏁 Process with PID %d is exiting...\n", getpid());

    return 0;
}

/*
 * 🧑‍🔬 EXPERIMENT:
 * 1. Compile this program: gcc fork-basic.c -o fork-basic
 * 2. Run it multiple times: ./fork-basic
 * 3. Notice that sometimes the Child prints first, and sometimes the Parent prints first!
 *    (This is because the OS scheduler decides who gets the CPU next).
 */
