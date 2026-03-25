/**
 * 🎓 OS CONCEPTS: Exponential Process Creation
 * 
 * DESCRIPTION:
 * Calling fork() multiple times in a row without conditional logic (if statements)
 * leads to exponential process creation. Every existing process creates a clone.
 */

#include <stdio.h>
#include <unistd.h>

int main() {
    // A static variable retains its value across function calls, 
    // but here it is simply initialized once.
    static int i = 0;
    i++;
    
    printf("Starting program... (Original PID: %d)\n", getpid());

    /*
     * 🧠 THE PROCESS TREE:
     * Let "P" be the original process.
     * 
     * fork() #1: 
     * P creates C1. 
     * Total processes: 2 (P, C1)
     */
    fork();

    /*
     * fork() #2: 
     * Both P and C1 hit this line!
     * P creates C2.
     * C1 creates C1a.
     * Total processes: 4 (P, C1, C2, C1a)
     */
    fork();

    /*
     * fork() #3:
     * All 4 processes hit this line!
     * P creates C3.
     * C1 creates C1b.
     * C2 creates C2a.
     * C1a creates C1a1.
     * Total processes: 8!
     */
    fork();

    // Since there are 2^3 = 8 processes, this line will be printed 8 times!
    // Notice that 'i' is always 1, because the child gets a copy of 'i' 
    // as it was at the time of the fork (which was 1).
    printf("Process PID %d saying: %d: Hello\n", getpid(), i);

    return 0;
}

/*
 * 🧑‍🔬 EXPERIMENT:
 * 1. Count how many "Hello" messages you see. (Should be 8).
 * 2. Try adding a 4th fork() right above the printf. Recompile and run. 
 *    You should see 16 messages (2^4 = 16).
 */