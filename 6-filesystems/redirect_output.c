#include <fcntl.h>  
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    
    // 1. Open the file
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { // Changed to < 0 (0 is valid for stdin)
        perror("File open failed");
        return 1;
    }

    // 2. Redirect STDOUT (1) to our file descriptor (fd)
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Redirection failed");
        return 1;
    }

    // This goes into output.txt immediately
    printf("--- Session Started ---\n");

    // 3. Safe Loop
    while (fgets(str, sizeof(str), stdin) != NULL) {
        // If the user just presses Enter on an empty line, let's exit
        if (str[0] == '\n') break;

        // puts() now writes to the file!
        puts(str);
        
        // Optional: Ensure data is written to disk immediately
        fflush(stdout); 
    }

    printf("--- Session Ended ---\n");

    // 4. Cleanup
    close(fd);
    return 0;
}