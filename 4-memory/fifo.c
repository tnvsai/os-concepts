/**
 * 🎓 OS CONCEPTS: First-In, First-Out (FIFO) Page Replacement
 * 
 * DESCRIPTION:
 * When a process needs to load a Page from the hard drive into RAM, 
 * but the RAM (Frames) is completely full, the OS must evict an old 
 * Page. FIFO is the simplest policy: The oldest Page in memory is 
 * always the one kicked out!
 */

#include <stdio.h>

int main() {
    // A sequence of logical pages the program is asking to access over time.
    int pages[] = {1, 2, 3, 1, 4, 5};
    int total_pages = 6;
    
    // Physical RAM is divided into 3 Frames in this simulation.
    // -1 means the Frame is currently empty.
    int frames[3] = {-1, -1, -1};
    int total_frames = 3;
    
    // 'index' acts as the FIFO pointer. It always points to the OLDEST frame.
    int index = 0;
    
    // Tracks how many times we had to go to the Hard Drive to fetch a page.
    int faults = 0;

    printf("🔄 Starting FIFO Page Replacement Simulation...\n\n");

    for (int i = 0; i < total_pages; i++) {
        int found = 0;

        printf("➡️  Accessing Page %d... ", pages[i]);

        // Step 1: Check if the required page is ALREADY stored in one of the RAM Frames.
        for (int j = 0; j < total_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1; // It's a Page Hit!
                break;
            }
        }

        // Step 2: PAGE FAULT! It wasn't in RAM. We must load it.
        if (!found) {
            printf("[❌ Page Fault] ");
            
            // Replace the oldest page (at the current FIFO 'index') with the new page.
            frames[index] = pages[i];
            
            // Move the FIFO pointer to the next oldest frame. 
            // The modulo operator (%) makes it wrap around: 0 -> 1 -> 2 -> 0 -> 1...
            index = (index + 1) % total_frames;
            
            faults++;
        } else {
            printf("[✅ Page Hit]   ");
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