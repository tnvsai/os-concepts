/**
 * 🎓 OS CONCEPTS: Priority Scheduling
 * 
 * DESCRIPTION:
 * In this algorithm, every process is assigned a "Priority" integer. 
 * The system sorts the Ready Queue so that the highest priority process goes first.
 * 
 * Note: In different OS implementations, sometimes a LOWER number means 
 * HIGHER priority (e.g. 1 is max priority). This code assumes a simple 
 * numerical sort to demonstrate the sorting logic itself.
 */

#include <stdio.h>

int main() {
    // Number of processes
    int n = 3;

    // Burst Time for P0, P1, P2
    int bt[] = {5, 3, 8};
    
    // Priorities assigned to P0, P1, P2
    // Here, P1 has priority 1, P0 has 2, P2 has 3.
    int priority[] = {2, 1, 3};
    
    // We will use an array to remember the original process IDs before sorting
    int temp_pid[] = {0, 1, 2};

    /*
     * The core of Priority Scheduling is simply SORTING the processes
     * based on their priority values before assigning them to the CPU.
     * Here we use a standard Bubble Sort.
     */
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            
            // Note: Adjust the ">" to "<" if you want lower numbers to mean higher priority.
            if (priority[i] > priority[j]) {
                
                // 1. Swap Priority values
                int temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                // 2. Swap the corresponding Burst Time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                
                // 3. Keep track of the Original PIDs so we know who is who!
                temp = temp_pid[i];
                temp_pid[i] = temp_pid[j];
                temp_pid[j] = temp;
            }
        }
    }

    // --- Output Results ---
    printf("👑 Process order after Priority Sorting:\n\n");

    for (int i = 0; i < n; i++) {
        printf("-> P%d executed (Priority: %d, Burst Time: %d)\n", temp_pid[i], priority[i], bt[i]);
    }

    return 0;
}