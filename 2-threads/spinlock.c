/**
 * 🎓 OS CONCEPTS: Spinlocks
 * 
 * DESCRIPTION:
 * This program solves a Race Condition just like `mutex-fix.c`, 
 * but it uses a drastically different underlying mechanism: The Spinlock.
 * 
 * THE DIFFERENCE:
 * - Mutex: If the door is locked, the thread politely goes to sleep and 
 *   tells the OS to wake it up when the door opens. This saves CPU power 
 *   but wastes time putting the thread to sleep and waking it up (Context Switch).
 * - Spinlock: If the door is locked, the thread aggressively grabs the doorknob 
 *   and rattles it non-stop in an infinite `while()` loop, burning 100% CPU power 
 *   until the door opens. It is lightning-fast if the wait is only a microsecond,
 *   but catastrophic if the wait is long.
 */

#include <stdio.h>
#include <pthread.h>

// 1. Declare the Spinlock globally
pthread_spinlock_t lock;

// The shared variable
int counter = 0;

void* increment()
{
    for(int i = 0; i < 1000000; i++)
    {
        /*
         * 🔄 SPIN WAITING
         * If the lock is held by the other thread, this function does NOT 
         * yield the CPU. It violently loops right here checking the lock.
         */
        pthread_spin_lock(&lock);
        
        // --- CRITICAL SECTION START ---
        counter++;
        // --- CRITICAL SECTION END ---
        
        /*
         * 🔓 UNLOCK
         * Drop the spinlock so the other spinning thread can grab it instantly.
         */
        pthread_spin_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    
    printf("Starting the Spinlock Demo...\n");

    /*
     * 2. Initialize the spinlock before using it
     * PTHREAD_PROCESS_PRIVATE ensures the lock is only shared among threads 
     * inside this specific process, not globally across the entire OS.
     */
    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);

    // Spawn the threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for the threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Print the perfect result
    printf("Final counter value: %d ✅\n", counter);
    
    // 3. Destroy the spinlock to free resources
    pthread_spin_destroy(&lock);

    return 0;
}