/**
 * 🎓 OS CONCEPTS: Writing to Standard Output and Error
 * 
 * DESCRIPTION:
 * In Linux, "Everything is a file." Even your terminal screen is treated 
 * as a file by the Operating System!
 * 
 * Every program starts with 3 special files already opened for it:
 * 0: Standard Input  (STDIN)  - Your keyboard
 * 1: Standard Output (STDOUT) - Your screen (for regular text)
 * 2: Standard Error  (STDERR) - Your screen (for error messages)
 */

#include <unistd.h> // Provides the write() system call

int main() {
    
    /*
     * write(file_descriptor, string, length)
     */
    
    // Writing to File Descriptor 1 (STDOUT)
    // This goes to the terminal. It's the equivalent of printf("STDOUT\n");
    // We pass 7 because "STDOUT\n" is precisely 7 characters long.
    write(1, "STDOUT\n", 7);
    
    // Writing to File Descriptor 2 (STDERR)
    // This also goes to the terminal by default, but it's logically separate.
    // You can see the difference if you redirect output using the command line!
    // Try running: ./write-syscall 1> output.txt 2> error.txt
    write(2, "STDERR\n", 7);
    
    return 0;
}

/*
 * 🧑‍🔬 EXPERIMENT:
 * 1. Compile: gcc write-syscall.c -o write-syscall
 * 2. Normal run: ./write-syscall 
 *    (Both print to screen)
 * 3. Redirect STDOUT: ./write-syscall > output.txt
 *    (Only STDERR prints to screen. STDOUT went to the file!)
 * 4. Redirect STDERR: ./write-syscall 2> error.txt
 *    (Only STDOUT prints to screen. STDERR went to the file!)
 */