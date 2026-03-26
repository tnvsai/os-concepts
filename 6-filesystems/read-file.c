/**
 * 🎓 OS CONCEPTS: Lowest-Level File Reading
 * 
 * DESCRIPTION:
 * This program bypasses standard C library functions like `fopen` or `fgets` 
 * and talks directly to the Operating System Kernel using the `open()`, 
 * `read()`, and `write()` system calls.
 */

#include <fcntl.h>  // Provides the O_RDONLY file control flag
#include <unistd.h> // Provides the POSIX system calls: read, write, close
#include <stdio.h>

int main()
{
    printf("📖 Attempting to read 'test.txt' using basic system calls...\n\n");

    /*
     * 1. OPEN THE FILE
     * open(filename, flags) asks the OS to find the file and prepare it for reading.
     * It returns a "File Descriptor" (fd) - an integer representing the open file.
     */
    int fd = open("test.txt", O_RDONLY);
    
    if (fd < 0) {
        printf("❌ Failed to open test.txt. Please create it first in this directory!\n");
        return 1;
    }

    /*
     * 2. PREPARE A RAM BUFFER
     * Data from the hard drive must be temporarily stored in RAM.
     */
    char buffer[100];

    /*
     * 3. THE READ SYSTEM CALL
     * read(file_descriptor, buffer_pointer, maximum_bytes_to_read)
     * The OS pulls bytes from the file on disk into our buffer.
     * 'bytes_read' will hold exactly how many bytes were successfully pulled.
     */
    int bytes_read = read(fd, buffer, sizeof(buffer));

    if (bytes_read > 0) {
        /*
         * 4. THE WRITE SYSTEM CALL
         * write(file_descriptor, buffer, bytes_to_write)
         * 
         * Notice the first argument is '1'. 
         * By universal Unix convention, File Descriptor 1 is Standard Output (the screen).
         * This line does exactly what printf() does!
         */
        write(1, buffer, bytes_read);
    } else {
        printf("⚠️ The file was completely empty!\n");
    }

    // 5. CLEANUP
    // Always give the file descriptor back to the OS when done.
    close(fd);

    printf("\n\n✅ Done reading.\n");
    return 0;
}