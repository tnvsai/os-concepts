/**
 * 🎓 OS CONCEPTS: The Simplest Read
 * 
 * DESCRIPTION:
 * A bare-bones example of using the lowest-level 'read' and 'write' 
 * system calls to read a small text file and print it to the screen.
 */

#include <fcntl.h>  // Provides the O_RDONLY flag
#include <unistd.h> // Provides read(), write(), close()
#include <stdio.h>

int main()
{
    // 1. OPEN: Ask the OS to access "test.txt" in Read-Only mode.
    // Ensure you create a file named "test.txt" first, or this will fail!
    int fd = open("test.txt", O_RDONLY);
    
    if (fd < 0) {
        printf("Failed to open test.txt. Did you create it?\n");
        return 1;
    }

    // 2. BUFFER: Reserve 100 bytes of memory to hold the data as it comes off the disk.
    char buffer[100];

    // 3. READ: Ask the OS to fill the buffer with up to 100 bytes of data.
    // 'bytes_read' holds the actual number of letters pulled from the file.
    int bytes_read = read(fd, buffer, sizeof(buffer));

    // 4. WRITE TO SCREEN
    // Wait, why are we writing to "1"? 
    // In Linux, '1' is the File Descriptor for Standard Output (the terminal screen).
    // Writing to 1 is exactly what printf() does secretly behind the scenes!
    write(1, buffer, bytes_read);

    // 5. CLOSE: Free the file descriptor back to the operating system.
    close(fd);

    return 0;
}