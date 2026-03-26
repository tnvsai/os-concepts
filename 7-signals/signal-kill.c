/**
 * 🎓 OS CONCEPTS: Processes and the kill() command
 * 
 * DESCRIPTION:
 * This is a tiny "victim" program. It prints its own Process ID (PID)
 * and then goes into an infinite loop, doing absolutely nothing but sleeping.
 * 
 * It is meant to be run in the background so you can practice sending 
 * POSIX Signals to it from another terminal window using the `kill` command.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // 1. Print our PID so the user knows who to target!
    printf("🎯 Target Acquired! My PID is: %d\n", getpid());
    printf("I am going to sleep forever. Try to kill me from another terminal!\n");
    printf("Example commands to try:\n");
    printf("  kill -SIGSTOP %d   (Pauses me)\n", getpid());
    printf("  kill -SIGCONT %d   (Wakes me up)\n", getpid());
    printf("  kill -SIGTERM %d   (Politely asks me to exit)\n", getpid());
    printf("  kill -SIGKILL %d   (Violently murders me!)\n\n", getpid());

    // 2. The Infinite Sleep Loop
    while (1) {
        printf("💤 Still sleeping...\n");
        sleep(5); // Sleep for 5 seconds, wake up, print, and repeat.
    }

    return 0; // We will never reach this!
}