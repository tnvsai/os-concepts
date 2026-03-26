/**
 * 🎓 OS CONCEPTS: I/O Redirection (Output)
 * 
 * DESCRIPTION:
 * Shows how to use `dup2()` to overwrite Standard Output (1).
 * This makes every single `printf()` in the program magically write 
 * into a text file instead of the screen, simulating the command `ls > output.txt`.
 */

#include <fcntl.h>  
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    
    // 1. Open (or completely create and clear out) a file to Write into.
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { 
        perror("File open failed");
        return 1;
    }

    /*
     * 2. THE MAGIC TRICK
     * dup2(old_fd, new_fd) copies old_fd directly OVER new_fd.
     * STDOUT_FILENO is exactly 1. 
     * So we overwrite the "Screen" file descriptor with our text file!
     */
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Redirection failed");
        return 1;
    }

    // 3. Use standard C library functions normally!
    // Because STDOUT was hi-jacked, this string goes straight into output.txt.
    // The screen remains completely blank.
    printf("--- Session Started ---\n");

    // Start an infinite loop reading from the actual keyboard
    // (Notice we did not hijack STDIN, so input still comes from the user)
    while (fgets(str, sizeof(str), stdin) != NULL) {
        
        // If the user just presses Enter continuously, exit the loop
        if (str[0] == '\n') break;

        // puts() automatically writes to STDOUT. Which goes to the file!
        puts(str);
        
        // This forces the C library to push the data to the hard drive immediately.
        fflush(stdout); 
    }

    printf("--- Session Ended ---\n");

    // Clean up
    close(fd);
    
    return 0;
}