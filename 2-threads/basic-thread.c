/**
 * 🎓 OS CONCEPTS: Basic POSIX Threads
 * 
 * DESCRIPTION:
 * This program demonstrates how to create a simple background thread.
 * It also shows a classic integration with "Signals" (like pressing Ctrl+C)
 * to gracefully shut down the background thread without crashing.
 */

#include <stdio.h>
#include <pthread.h> // The POSIX Threads library
#include <unistd.h>  // For sleep()
#include <signal.h>  // For signal handling

// A shared global variable. Both the main thread and background thread can see this!
// We use 'volatile' to tell the compiler not to over-optimize this variable, 
// since it can be changed at any moment by our signal handler.
volatile int flag = 1;

/*
 * ==========================================
 * 🧵 THE THREAD FUNCTION
 * ==========================================
 * Every thread must start executing a specific function.
 * This function MUST return void* and take a void* argument.
 */
void* task(void* arg)
{
    printf("🧵 Thread: Hello from the background thread!\n");
    
    // The thread will keep running as long as flag is 1.
    while (flag)
    {   
        printf("🧵 Thread: I am running...\n");
        sleep(1); // Sleep for 1 second to avoid spamming the console
    }
    
    printf("🧵 Thread: Flag is 0! I am shutting down gracefully.\n");
    return NULL; // A thread exits when its function returns.
}

/*
 * ==========================================
 * 🛑 THE SIGNAL HANDLER
 * ==========================================
 * This function is suddenly triggered by the OS if the user hits Ctrl+C.
 */
void signal_handler(int sig)
{
    printf("\n🛑 Signal Handler: Caught Ctrl+C (SIGINT). Telling thread to stop...\n");
    flag = 0; // Update the shared variable!
}

int main()
{
    // Tell the OS: "If the user presses Ctrl+C (SIGINT), don't kill the program. 
    // Instead, run my signal_handler function."
    signal(SIGINT, signal_handler);
    
    pthread_t t; // A variable to hold the Thread ID

    printf("👨 Main: Creating the background thread...\n");
    
    /*
     * pthread_create(&thread_id, attributes, function_to_run, arguments_for_function)
     * This physically spawns the new thread!
     */
    pthread_create(&t, NULL, task, NULL);
    
    printf("👨 Main: Thread created! Press Ctrl+C to stop it.\n");
    
    /*
     * pthread_join(thread_id, return_value_pointer)
     * 🛑 CRITICAL: The main function MUST pause and wait for the thread to finish.
     * If main() reached 'return 0', the OS would instantly murder the background thread!
     */
    pthread_join(t, NULL);
    
    printf("👨 Main: The thread has successfully finished. Goodbye!\n");
    return 0; 
}