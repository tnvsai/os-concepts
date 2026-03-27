/**
 * 🎓 OS CONCEPTS: Virtual Filesystems (/proc)
 * 
 * DESCRIPTION:
 * Wait a second, why is this file in the Signals directory? 
 * This is actually a demonstration of File I/O and the Kernel!
 * 
 * Linux has a "Virtual Filesystem" mounted at `/proc`. The files inside 
 * there do not actually exist on your hard drive! They are illusions created 
 * by the OS Kernel in RAM. 
 * 
 * When you use `open()` and `read()` on files like `/proc/cpuinfo`, 
 * the Kernel intercepts your call and instantly generates a text report 
 * about the CPU state, feeding it back to you as if it were a real file.
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    printf("💻 Querying the Kernel for Live CPU Information using /proc/cpuinfo...\n\n");

    /*
     * 1. OPEN A VIRTUAL FILE
     * We open /proc/cpuinfo exactly as if it were a normal .txt file.
     */
    int fd = open("/proc/cpuinfo", O_RDONLY);
    if(fd < 0)
    {
        printf("❌ Unable to open the file. Are you on a Linux system?\n");
        return 1;
    }
    
    char buffer[1024];
    int cpy_bytes = 0;
    
    /*
     * 2. READ THE VIRTUAL FILE
     * The OS Kernel is dynamically generating this text data on the fly 
     * and writing it into our buffer.
     */
    while ((cpy_bytes = read(fd, buffer, sizeof(buffer))) > 0)
    {
        // 3. Dump the result directly to the screen (STDOUT_FILENO = 1)
        write(1, buffer, cpy_bytes);
    }
    
    close(fd);
    
    return 0;
}