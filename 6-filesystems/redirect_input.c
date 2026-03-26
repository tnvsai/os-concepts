/**
 * 🎓 OS CONCEPTS: I/O Redirection (Input)
 * 
 * DESCRIPTION:
 * Shows how to use `dup2()` to overwrite Standard Input (0).
 * This makes the program read from a file instead of waiting for 
 * you to type on the keyboard, simulating the command `cat < input.txt`.
 */

#include <fcntl.h>  
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    // 1. Open a file to read from
    int fd = open("output.txt", O_RDONLY);
    
    if (fd < 0) {
        perror("Failed to open output.txt");
        return 1;
    }

    /*
     * 2. THE MAGIC TRICK
     * dup2(old_fd, new_fd) copies old_fd directly OVER new_fd.
     * STDIN_FILENO is exactly 0. 
     * So we overwrite the "Keyboard" file descriptor with our text file!
     */
    dup2(fd, STDIN_FILENO);
    
    char buffer[100];

    // 3. READ THE "KEYBOARD"
    // We are reading from fd 0 (STDIN). Because of dup2, this will 
    // actually pull data directly from output.txt!
    int n = read(0, buffer, sizeof(buffer));

    if (n > 0) {
        // Write whatever we got out to the screen
        write(1, "\n--- Read from redirected STDIN ---\n", 36);
        write(1, buffer, n);
    }

    // Always clean up!
    close(fd);

    return 0;
}