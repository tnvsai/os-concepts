/**
 * 🎓 OS CONCEPTS: Waiting for Children and Collecting Status
 * 
 * DESCRIPTION:
 * This program demonstrates why and how a parent must wait 
 * for its child to finish execution using the wait() system call.
 */

#include <stdio.h>
#include <unistd.h>     // Required for fork(), sleep(), etc.
#include <sys/types.h>  // Required for pid_t
#include <sys/wait.h>   // Required for wait() and status macros (WIFEXITED, etc)

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        // ==========================================
        //         THIS IS THE CHILD'S CODE
        // ==========================================
        printf("👶 Child: I'm starting a 3-second task...\n");
        sleep(3); // Simulate some hard work
        printf("👶 Child: Task done. Exiting now to send my exit code.\n");
        
        /* 
         * The return value of main() (or exit()) is the "Exit Status".
         * 0 usually denotes absolute success. 
         * Anything else (like 42 here) implies a specific condition or error.
         */
        return 42; 
    } 
    else {
        // ==========================================
        //        THIS IS THE PARENT'S CODE
        // ==========================================
        int status; // This integer will hold the child's exit information.

        printf("👨 Parent: Waiting for my child (PID %d) to finish...\n", pid);
        
        /*
         * 🛑 THE WAIT CALL 🛑
         * wait() blocks (suspends) the parent until any child terminates.
         * When the child terminates, the OS fills the 'status' variable
         * with information about how the child died.
         */
        wait(&status); 

        // At this point, the child is guaranteed to be dead and cleaned up (not a zombie).

        /*
         * We use special MACROS provided by <sys/wait.h> to decode the 'status' integer.
         * WIFEXITED checks if the child terminated normally (via return or exit).
         */
        if (WIFEXITED(status)) {
            // If it exited normally, WEXITSTATUS gets the actual return code (e.g., 42).
            printf("👨 Parent: Child is gone. It returned status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            // This triggers if the child crashed or was killed by a signal (like Ctrl+C).
            printf("👨 Parent: Child was killed by an external signal!\n");
        }

        printf("👨 Parent: Now I can safely finish my own work and exit.\n");
    }

    return 0;
}