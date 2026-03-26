/**
 * 🎓 OS CONCEPTS: Thread Arguments
 * 
 * DESCRIPTION:
 * This demonstrates how to pass variables to a newly created thread.
 * Because a thread function only accepts a `void*` (a pointer to "anything"),
 * you must cast your variable to a `void*` when passing it, and then cast 
 * it back to its original type inside the thread.
 */

#include <stdio.h>
#include <pthread.h>

/*
 * The thread task.
 * Notice the argument is a generic `void*`.
 */
void* task(void* arg) 
{
    // 1. Cast the void pointer back to an integer pointer: (int*)arg
    // 2. Dereference it to get the actual integer value: *
    int num = *(int*)arg;
    
    printf("🧵 Thread: I successfully received the value: %d\n", num);
    return NULL;
}

int main() 
{
    pthread_t t;
    
    // The variable we want to send to the thread
    int value = 42;

    printf("👨 Main: Creating thread and passing the value %d to it...\n", value);

    /*
     * The 4th argument of pthread_create is naturally a void*.
     * We pass the memory address of our `value` variable (&value).
     */
    pthread_create(&t, NULL, task, &value);
    
    // Wait for the thread to finish
    pthread_join(t, NULL);

    return 0;
}