/**
 * 🎓 OS CONCEPTS: Basic Logical to Physical Paging Simulation
 * 
 * DESCRIPTION:
 * This acts as a vastly simplified demonstration of the "Paging" concept.
 * A program is broken into Pages, and they are blindly mapped into any 
 * available physical Frames.
 */

#include <stdio.h>

int main() {
    // The program requires 4 logical Pages
    int pages[] = {1, 2, 3, 4};
    
    // The system only grants 2 physical Frames to the process 
    int frames[2] = {-1, -1};

    printf("📦 Basic Paging Simulator Started\n\n");

    for (int i = 0; i < 4; i++) {
        
        // This simulates placing the Page into a Frame using simple Modular Arithmetic.
        // It blindly overwrites what was previously there (unlike strict LRU or FIFO tracking).
        int target_frame = i % 2;
        
        frames[target_frame] = pages[i];

        printf("Moved Logical Page %d -> Physical Frame %d\n", pages[i], target_frame);

        // --- Print RAM State ---
        printf("Current Frame States: [ ");
        for (int j = 0; j < 2; j++) {
            if (frames[j] == -1) printf("Empty ");
            else printf("%d ", frames[j]);
        }
        printf("]\n\n");
    }

    return 0;
}