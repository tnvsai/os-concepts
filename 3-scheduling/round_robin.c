/**
 * 🎓 OS CONCEPTS: Round Robin (RR) Scheduling
 * 
 * DESCRIPTION:
 * Round Robin is designed for time-sharing systems. 
 * Every process gets a strict, brief slice of CPU time (the "Time Quantum").
 * If it doesn't finish in that time, it's kicked off and put at the back of the line.
 */

#include <stdio.h>

int main() {
    // Number of processes
    int n = 3;
    
    // Burst Times needed by P0, P1, P2
    int bt[] = {5, 3, 8};
    
    /* 
     * Remaining Time (rt):
     * Because a process might be kicked off the CPU before it finishes, 
     * we must keep track of how much time it STILL needs to finish.
     */
    int rt[3];
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i]; // Start by copying burst times into remaining times.
    }

    // The Time Quantum (Maximum time a process can use the CPU in one turn)
    int tq = 2; 

    // Current system time tracker
    int time = 0;

    printf("⏱️  Starting Round Robin Scheduling...\n");
    printf("Time Quantum: %d ms\n\n", tq);

    // Enter an infinite loop that represents the CPU constantly giving out turns
    while (1) {
        int done = 1; // Assume everything is finished until proven otherwise.

        // Loop through the "Ready Queue"
        for (int i = 0; i < n; i++) {
            
            // Does this process still need CPU time?
            if (rt[i] > 0) {
                done = 0; // The whole system is not done yet!

                if (rt[i] > tq) {
                    /*
                     * The process needs MORE time than the Quantum.
                     * 1. It takes a full Quantum slice of Time.
                     * 2. Its remaining time decreases by the Quantum.
                     */
                    time += tq;
                    rt[i] -= tq;
                    // printf("P%d ran for %d ms. (Remaining: %d ms)\n", i, tq, rt[i]);
                } 
                else {
                    /*
                     * The process needs LESS or EQUAL time to the Quantum.
                     * 1. It takes exactly the time it needs, then finishes!
                     * 2. Its remaining time becomes 0.
                     */
                    time += rt[i];
                    rt[i] = 0;
                    printf("✅ P%d completely finished at Time = %d ms\n", i, time);
                }
            }
        }

        // If 'done' is still 1, no process needed time in this pass. We are finished!
        if (done) {
            break;
        }
    }

    printf("\n🏁 All processes finished execution!\n");

    return 0;
}