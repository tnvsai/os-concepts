/**
 * 🎓 OS CONCEPTS: Least Recently Used (LRU) Page Replacement
 * 
 * DESCRIPTION:
 * Instead of evicting the oldest page (FIFO), LRU evicts the page 
 * that hasn't been accessed for the longest time. 
 * 
 * It assumes that if a page was just used recently, it will probably 
 * be used again soon. If you haven't touched a page in a long time, 
 * you probably don't need it right now.
 */

#include <stdio.h>

int main() {
    // The sequence of pages the CPU wants to access
    int pages[] = {1, 2, 3, 1, 4, 5};
    int total_pages = 6;
    
    // RAM Frames
    int frames[3] = {-1, -1, -1};
    int total_frames = 3;
    
    /* 
     * We need a way to track "Time".
     * time[] array stores the 'counter' value when a Frame was LAST ACCESSED.
     */
    int time[3] = {0};
    int counter = 0; // Represents our logical system clock
    
    int faults = 0;

    printf("🧠 Starting LRU Page Replacement Simulation...\n\n");

    for (int i = 0; i < total_pages; i++) {
        int found = 0;
        
        printf("➡️  CPU requests Page %d... ", pages[i]);

        // Step 1: Check if the Page is already in RAM
        for (int j = 0; j < total_frames; j++) {
            if (frames[j] == pages[i]) {
                // PAGE HIT! 
                // CRITICAL DIFFERENCE FROM FIFO: We UPDATE its last accessed time!
                time[j] = counter++;
                found = 1;
                break;
            }
        }

        // Step 2: PAGE FAULT! The page is not in RAM.
        if (!found) {
            printf("[❌ PAGE FAULT] ");
            
            // We must find the Least Recently Used frame. 
            // This is just a basic search for the absolutely lowest number in the time[] array.
            int min_index = 0;
            for (int j = 1; j < total_frames; j++) {
                if (time[j] < time[min_index]) {
                    min_index = j;
                }
            }

            // Evict the LRU page and load the new page into that exact frame.
            frames[min_index] = pages[i];
            
            // Record the exact "time" this new page was placed in memory.
            time[min_index] = counter++;
            
            faults++;
        } else {
            printf("[✅ PAGE HIT]   ");
        }

        // --- Print Current RAM State ---
        printf("RAM State: [");
        for (int j = 0; j < total_frames; j++) {
            if (frames[j] == -1) printf(" Empty ");
            else printf(" %d ", frames[j]);
        }
        printf("]\n");
    }

    printf("\n📉 Total Page Faults: %d\n", faults);

    return 0;
}