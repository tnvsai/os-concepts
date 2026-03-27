/**
 * 🎓 OS CONCEPTS: POSIX Semaphores
 * 
 * DESCRIPTION:
 * A Mutex allows exactly ONE thread into a critical section. 
 * But what if you have 3 printers, and you want to allow up to 
 * THREE threads to print at exactly the same time, but block the 4th?
 * 
 * Enter the Semaphore! A semaphore is an integer counter. 
 * - sem_wait() decreases the counter. If the counter hits 0, the thread goes to sleep.
 * - sem_post() increases the counter and wakes up a sleeping thread.
 * 
 * This program demonstrates a Semaphore initialized to 2, meaning 
 * exactly 2 threads are allowed inside the critical section simultaneously!
 */

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h> // POSIX Semaphores
#include <pthread.h>

// Declare the Semaphore globally
sem_t sem;

void* task(void* arg)
{
    /*
     * 🚦 SEMAPHORE WAIT
     * If the semaphore is > 0, decrement it by 1 and proceed immediately!
     * If the semaphore is exactly 0, go to sleep until someone calls sem_post.
     */
    sem_wait(&sem);

    // --- CRITICAL SECTION ---
    // Only 2 threads will ever be inside here at the exact same moment.
    printf("🟢 Thread %ld entering the critical section!\n", pthread_self());
    sleep(1); // Simulate hard work
    printf("🔴 Thread %ld leaving the critical section!\n", pthread_self());
    // --- END CRITICAL SECTION ---

    /*
     * 🚦 SEMAPHORE POST
     * Increment the semaphore by 1. 
     * If there are other threads sleeping on a sem_wait, the OS wakes one of them up!
     */
    sem_post(&sem);

    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;
    
    printf("Starting Semaphore Demo. Max 2 threads allowed at once...\n\n");

    /*
     * INIT SEMAPHORE
     * sem_init(&semaphore, shared_between_processes, initial_value)
     * We initialize it to 2!
     */
    sem_init(&sem, 0, 2);

    // Fire off 3 threads! 
    // Threads 1 and 2 will enter immediately. Thread 3 will be forced to wait.
    pthread_create(&t1, NULL, task, NULL);
    pthread_create(&t2, NULL, task, NULL);
    pthread_create(&t3, NULL, task, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Clean up
    sem_destroy(&sem);
    
    return 0;
}