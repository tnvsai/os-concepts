/**
 * 🎓 OS CONCEPTS: Low-Level File I/O (Copying a File)
 * 
 * DESCRIPTION:
 * This program demonstrates how to copy a file byte-by-byte (or chunk-by-chunk) 
 * using the fundamental operating system calls: open(), read(), write(), and close().
 * It bypasses standard C library functions like fopen() or fread(), 
 * interacting directly with the Linux kernel.
 */

#include <fcntl.h>  // Contains file control options like O_RDONLY, O_WRONLY
#include <unistd.h> // Contains POSIX standard functions like read, write, close
#include <stdio.h>

int main(int argc, char *argv[])
{
    /*
     * 1. VALIDATE COMMAND LINE ARGUMENTS
     * argc (argument count) holds the number of things typed on the command line.
     * argv (argument vector) holds the actual strings typed.
     * Example: ./copy-file source.txt dest.txt
     *   -> argc = 3
     *   -> argv[0] = "./copy-file"
     *   -> argv[1] = "source.txt"
     *   -> argv[2] = "dest.txt"
     */
    if (argc != 3)
    {
        printf("❌ Invalid format! Follow this pattern: %s <source_file> <dest_file>\n", argv[0]);
        return 1;
    }

    // ==========================================
    // 2. OPEN THE SOURCE FILE (Reading)
    // ==========================================
    
    /*
     * open() asks the OS to provide access to a file.
     * It returns a "File Descriptor" (fd) - a small integer the OS uses to keep track of the file.
     * O_RDONLY means "Read Only" mode.
     */
    int src_fd = open(argv[1], O_RDONLY);
    
    if (src_fd < 0)
    {
        printf("❌ Error opening source file '%s'. Does it exist?\n", argv[1]);
        return 1;
    }

    // ==========================================
    // 3. OPEN THE DESTINATION FILE (Writing)
    // ==========================================
    
    /*
     * opening the destination file requires more flags:
     * - O_WRONLY: Write Only mode.
     * - O_CREAT: If the file doesn't exist, create it!
     * - O_TRUNC: If the file DOES exist, truncate it (empty it out) to 0 bytes first.
     * 
     * The third argument (0644) sets the permissions if the file is created:
     * - Owner: Read (4) + Write (2) = 6
     * - Group: Read (4) = 4
     * - Others: Read (4) = 4
     */
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (dest_fd < 0)
    {
        printf("❌ Error opening destination file '%s'. Permission denied?\n", argv[2]);
        close(src_fd);
        return 1;
    }

    // ==========================================
    // 4. THE COPY LOOP (read / write)
    // ==========================================
    
    char buffer[100];      // An array in memory to hold chunks of data temporarily.
    int bytes_read = 0;    // Keeps track of how many bytes we actually got from the file.

    /*
     * read(file_descriptor, buffer, max_bytes_to_read)
     * - Asks the OS to read up to 100 bytes from the source file.
     * - The OS copies data from the hard drive into our 'buffer'.
     * - Returns the NUMBER of bytes successfully read.
     * - Returns 0 if it hits the "End of File" (EOF).
     */
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        /*
         * write(file_descriptor, buffer, bytes_to_write)
         * - Asks the OS to write data from our 'buffer' onto the hard drive.
         * - We MUST tell it exactly how many bytes to write (bytes_read). 
         *   If we just said 100, we might write leftover garbage data at the end of the file!
         */
        write(dest_fd, buffer, bytes_read);
    }
    
    // ==========================================
    // 5. CLEANUP
    // ==========================================
    
    // Always close file descriptors to give resources back to the OS!
    close(src_fd);
    close(dest_fd);
    
    printf("✅ Successfully copied '%s' to '%s'!\n", argv[1], argv[2]);

    return 0;
}