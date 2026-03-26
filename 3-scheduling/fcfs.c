/**
 * 🎓 OS CONCEPTS: First-Come, First-Served (FCFS) Scheduling
 * 
 * DESCRIPTION:
 * FCFS is the simplest CPU scheduling algorithm. The process that requests 
 * the CPU first gets it first. It acts exactly like a queue at a grocery store.
 * 
 * This program calculates the Waiting Time (WT) and Turnaround Time (TAT)
 * for 3 processes, assuming they all arrived at the exact same time (Time 0),
 * but were placed in the queue in the order P0, P1, P2.
 */

#include <stdio.h>

int main() {
    // Number of processes
    int n = 3;
    
    // Burst Time (BT): How long each process needs the CPU to finish its job.
    // P0 needs 5ms, P1 needs 3ms, P2 needs 8ms.
    int bt[] = {5, 3, 8}; 

    // Arrays to store Waiting Time and Turnaround Time for each process
    int wt[n], tat[n];

    /*
     * 1. CALCULATE WAITING TIME (WT)
     * P0 is first in line, so it doesn't wait at all (0 ms).
     */
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        // A process must wait for the PREVIOUS process to finish.
        // So, Waiting Time = Previous Process's Waiting Time + Previous Process's Burst Time
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    /*
     * 2. CALCULATE TURNAROUND TIME (TAT)
     * Turnaround Time is the total time spent in the system.
     * Since Arrival Time = 0, TAT is simply: Time Spent Waiting + Time Spent Executing
     */
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    // --- Output Results ---
    printf("📊 FCFS Scheduling Results:\n");
    printf("----------------------------------------\n");
    printf("Process\tBurst(BT)\tWait(WT)\tTurnaround(TAT)\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t| %d\t\t| %d\t\t| %d\n", i, bt[i], wt[i], tat[i]);
    }
    
    printf("----------------------------------------\n");

    return 0;
}