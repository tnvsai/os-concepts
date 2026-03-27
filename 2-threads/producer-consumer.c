/**
 * 🎓 OS CONCEPTS: Bounded-Buffer / Producer-Consumer Problem
 * 
 * DESCRIPTION:
 * This is the classic Producer-Consumer synchronization problem!
 * - A "Producer" thread generates data and puts it into a shared buffer.
 * - A "Consumer" thread takes data out of the buffer and processes it.
 * 
 * THE CHALLENGE:
 * 1. The Producer must pause if the buffer is FULL.
 * 2. The Consumer must pause if the buffer is EMPTY.
 * 3. They must never modify the buffer simultaneously (Mutex needed!).
 * 
 * We solve this beautifully using POSIX Semaphores and a Mutex!
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5

// --- GLOBAL SHARED VARIABLES ---

// Semaphores to track empty and full slots in the buffer
sem_t empty; 
sem_t full;  

// Mutex to protect the buffer from simultaneous modification
pthread_mutex_t lock;

// The shared buffer (a Circular Queue)
int data[SIZE];
int in = 0;  // Where the producer writes next
int out = 0; // Where the consumer reads next

/*
 * ==========================================
 * 📦 THE PRODUCER THREAD
 * ==========================================
 */
void* produce(void* arg)
{
    for(int i = 0; i < SIZE; i++)
    {
        /*
         * 1. Check if there are ANY EMPTY SLOTS left.
         * If `empty` is 0, the Producer goes to sleep here until the Consumer 
         * takes something out and calls sem_post(&empty).
         */
        sem_wait(&empty);
        
        // 2. Lock the buffer so the consumer can't touch it right now.
        pthread_mutex_lock(&lock);
        
        // 3. Produce data into the buffer!
        data[in] = i;
        printf("📦 Producer: Uploaded item %d to slot %d\n", data[in], in);
        in = (in + 1) % SIZE; // Move to the next slot in the circular queue
        
        // 4. Unlock the buffer.
        pthread_mutex_unlock(&lock);
        
        /*
         * 5. Signal the Consumer!
         * sem_post adds 1 to the `full` semaphore, waking up the Consumer 
         * if it was sleeping.
         */
        sem_post(&full);
        
        sleep(1); // Simulate slow production
    }
    return NULL;
}

/*
 * ==========================================
 * 🛒 THE CONSUMER THREAD
 * ==========================================
 */
void* consume(void* arg)
{
    for(int i = 0; i < SIZE; i++)
    {
        /*
         * 1. Check if there are ANY FULL SLOTS available.
         * If `full` is 0, the buffer is perfectly empty, so the Consumer 
         * goes to sleep here until the Producer makes something!
         */
        sem_wait(&full);
        
        // 2. Lock the buffer safely
        pthread_mutex_lock(&lock);
        
        // 3. Consume the data
        printf("🛒 Consumer: Downloaded item %d from slot %d\n", data[out], out);
        out = (out + 1) % SIZE;
        
        // 4. Unlock the buffer
        pthread_mutex_unlock(&lock);
        
        /*
         * 5. Signal the Producer!
         * sem_post adds 1 to the `empty` semaphore, indicating one more slot is free.
         */
        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    printf("Starting Producer-Consumer Simulator...\n\n");

    // Initialize the Mutex
    pthread_mutex_init(&lock, NULL);

    /*
     * INITIALIZE SEMAPHORES
     * sem_init(&sem, pshared, value)
     * - 'empty' starts at 5 (all slots are empty).
     * - 'full' starts at 0 (no slots are currently full).
     */
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    // Spawn the threads
    pthread_create(&t1, NULL, produce, NULL);
    pthread_create(&t2, NULL, consume, NULL);

    // Wait for everyone to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Clean up OS utilities
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    return 0;
}