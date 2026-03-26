/**
 * 🎓 OS CONCEPTS: Catching Signals (Custom Handlers)
 * 
 * DESCRIPTION:
 * By default, pressing Ctrl+C sends `SIGINT` (Signal Interrupt) to a program.
 * The default action of `SIGINT` is to instantly kill the program. 
 * 
 * This program demonstrates how you can tell the OS: "When I get SIGINT, 
 * DON'T kill me! Instead, run my custom function."
 */

#include <stdio.h>
#include <signal.h>  // Provides the signal() function and SIGINT macro
#include <unistd.h>

// A global variable we use to keep the main loop running.
// We make it 'volatile' because it can be changed asynchronously 
// by the signal handler at absolutely any moment!
volatile int state = 1;

/*
 * ==========================================
 * 🎣 THE CUSTOM SIGNAL HANDLER
 * ==========================================
 * This function is sitting quietly in the background. It only executes 
 * when the OS specifically delivers the signal we tied it to.
 */
void signal_handler(int sig)
{
    // Note: 'sig' will contain the integer value of the signal (e.g., 2 for SIGINT)
    printf("\n🛡️  Intercepted Signal %d (SIGINT)! I refuse to crash!\n", sig);
    printf("Shutting down gracefully instead...\n");
    
    // Change the global state to allow the main loop to finish naturally
    state = 0;
}

int main()
{
    printf("Starting program. Press Ctrl+C to try and kill me!\n");

    /*
     * THE MAGIC BINDING
     * signal(signal_to_catch, function_to_run)
     * We ask the OS to intercept SIGINT and route it to our `signal_handler`.
     */
    signal(SIGINT, signal_handler);

    // The Main Execution Loop
    while (state)
    {
        printf("🏃 Running normally... \n");
        sleep(1);
    }   

    printf("👋 Exited cleanly. Goodbye!\n");
    return 0;
}