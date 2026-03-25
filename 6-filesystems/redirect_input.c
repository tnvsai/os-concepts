#include <fcntl.h>  
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main()
{
    int fd = open("output.txt", O_RDONLY);
       if (fd < 0) {
        perror("open failed");
        return 1;
    }

    dup2(fd, STDIN_FILENO);
    char buffer[100];

         // Now reading from file instead of keyboard
    int n = read(0, buffer, sizeof(buffer));

    write(1, buffer, n);

   
    close(fd);

    return 0;
}