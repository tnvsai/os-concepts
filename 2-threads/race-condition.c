/**
 * 🎓 OS CONCEPTS: The Race Condition
 * 
 * DESCRIPTION:
 * This program intentionally demonstrates a "Race Condition".
 * Two concurrent threads share a single variable ('counter') and try to 
 * increment it simultaneously without giving each other turns. 
 * 
 * The expected output is 200,000. 
 * BUT YOU WILL ALMOST NEVER GET 200,000! You will get random, incorrect numbers.
 */

#include <stdio.h>
#include <pthread.h>

// Shared global variable
int counter = 0;

/*
 * THE CRITICAL SECTION
 * When multiple threads access and modify shared data, that code block
 * is called a "Critical Section".
 */
void* increment()
{
    for(int i = 0; i < 100000; i++)
    {
        /*
         * 💥 WHY DOES IT FAIL?
         * In C, "counter++" looks like one action. But to the CPU, it's THREE actions:
         * 1. READ counter from memory into the CPU register
         * 2. ADD 1 to the register
         * 3. WRITE the register back to memory
         * 
         * If Thread A is interrupted by the OS right after Step 1, Thread B might 
         * jump in, do all 3 steps, and write to memory. Then Thread A wakes up, 
         * finishes Step 2 & 3, and overwrites Thread B's hard work with stale data!
         */
        counter++; 
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    
    printf("Starting the Race Condition demo...\n");
    printf("Expected result: 200000\n");

    // Spawn two threads hitting the same exact function and variable
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for both to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Print the corrupted result
    printf("Actual counter value: %d\n", counter);

    return 0;
}