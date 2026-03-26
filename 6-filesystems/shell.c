#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX 100

int main() {
    char cmd[MAX];

    while (1) {
        printf("my_shell> ");

        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcmp(cmd, "exit") == 0)
            break;

        char *args[10];
        char *token;
        int i = 0;

        // Parse command
        token = strtok(cmd, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Check for '>'
        int redirect = 0;
        char *outfile = NULL;

        for (int j = 0; j < i; j++) {
            if (strcmp(args[j], ">") == 0) {
                redirect = 1;
                outfile = args[j + 1];
                args[j] = NULL; // split command
                break;
            }
        }

        pid_t pid = fork();

        if (pid == 0) {
            // CHILD

            if (redirect) {
                int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open failed");
                    exit(1);
                }

                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            execvp(args[0], args);

            perror("exec failed");
            exit(1);
        } else {
            // PARENT
            wait(NULL);
        }
    }

    return 0;
}