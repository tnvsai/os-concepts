/**
 * 🎓 OS CONCEPTS: Standard File Descriptors
 * 
 * DESCRIPTION:
 * This program demonstrates the profound Unix philosophy: "Everything is a file."
 * Even the terminal screen you are looking at is treated as a file you can write to.
 * 
 * The OS automatically opens 3 File Descriptors for EVERY program:
 * 0: Standard Input (STDIN)    -> Reads from the keyboard
 * 1: Standard Output (STDOUT)  -> Writes normal text to the screen
 * 2: Standard Error (STDERR)   -> Writes error messages to the screen
 */

#include <unistd.h> // Provides the write() system call

int main() {
    
    /*
     * write(file_descriptor, string, length)
     * We don't need to open() these descriptors, the OS already did.
     */
    
    // Write 25 characters to File Descriptor 1 (STDOUT)
    // This is fundamentally what printf() calls behind the scenes.
    write(1, "Regular STDOUT Message.\n", 24);
    
    // Write 23 characters to File Descriptor 2 (STDERR)
    // By default, this also goes to the screen. 
    write(2, "Urgent STDERR Message!\n", 23);
    
    return 0;
}

/*
 * 🧑‍🔬 EXPERIMENT - How to tell the difference:
 * 1. Compile: gcc write-syscall.c -o write-syscall
 * 2. Normal run: ./write-syscall 
 *    (Both messages print to screen)
 * 3. Redirect STDOUT to a file: ./write-syscall 1> output.txt
 *    (Only the STDERR message prints to screen. The STDOUT text went into output.txt!)
 * 4. Redirect STDERR to a file: ./write-syscall 2> error.txt
 *    (Only the STDOUT message prints to screen. The STDERR text went into error.txt!)
 */