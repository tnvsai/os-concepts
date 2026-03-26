/**
 * 🎓 OS CONCEPTS: Mutex Locks
 * 
 * DESCRIPTION:
 * This is the fixed version of `race-condition.c`.
 * We use a "Mutual Exclusion" lock (Mutex) to protect the shared variable.
 * A mutex guarantees that only ONE thread can enter the "Critical Section" at a time.
 */

#include <stdio.h>
#include <pthread.h>

// 1. Declare the Mutex Lock globally so all threads can see it
pthread_mutex_t lock;

// The shared variable
int counter = 0;

void* increment()
{
    for(int i = 0; i < 1000000; i++)
    {
        /*
         * 🔒 LOCK THE DOOR
         * If the lock is available, the thread grabs it and continues.
         * If another thread ALREADY has the lock, the OS puts this thread 
         * to sleep right here until the other thread drops the lock.
         */
        pthread_mutex_lock(&lock);
        
        // --- CRITICAL SECTION START ---
        
        // Now it is 100% physically impossible for two threads to execute this line at the same time.
        counter++;
        
        // --- CRITICAL SECTION END ---
        
        /*
         * 🔓 UNLOCK THE DOOR
         * We finished our work. Drop the lock so other sleeping threads can wake up and take their turn.
         * DON'T FORGET THIS, OR YOUR PROGRAM WILL FREEZE FOREVER! (Deadlock)
         */
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    
    // 2. Initialize the mutex lock before using it
    pthread_mutex_init(&lock, NULL);

    printf("Starting the Mutex Fixed demo...\n");
    printf("Expected result: 2000000\n"); // 1M loops + 1M loops

    // Spawn the threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for the threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Print the perfect result
    printf("Actual counter value: %d ✅\n", counter);
    
    // 3. Destroy the mutex to free OS resources
    pthread_mutex_destroy(&lock);

    return 0;
}