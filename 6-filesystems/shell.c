/**
 * 🎓 OS CONCEPTS: Shell with Output Redirection
 * 
 * DESCRIPTION:
 * This program implements a miniature Bash shell that looks for the 
 * '>' character in a command string and uses `dup2` to redirect that 
 * command's output directly into a file.
 * 
 * E.g., `ls -l > list.txt`
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_CMD_LEN 100

int main() {
    char cmd[MAX_CMD_LEN];

    printf("Welcome to the Redirect Shell! Try typing: date > time.txt\n\n");

    while (1) {
        printf("my_shell> ");

        if (fgets(cmd, sizeof(cmd), stdin) == NULL) break;
        cmd[strcspn(cmd, "\n")] = 0; // Strip newline

        if (strcmp(cmd, "exit") == 0) break;
        if (strlen(cmd) == 0) continue;

        char *args[10];
        char *token;
        int i = 0;

        // 1. Break command into tokens
        token = strtok(cmd, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Arrays passed to exec() must end with NULL

        // 2. Scan the tokens for the redirection operator '>'
        int redirect = 0;
        char *outfile = NULL;

        for (int j = 0; j < i; j++) {
            if (strcmp(args[j], ">") == 0) {
                redirect = 1;
                outfile = args[j + 1]; // The file name immediately follows the '>'
                
                // IMPORTANT: We must chop the array here! 
                // We don't want to accidentally pass ">" and "time.txt" as arguments 
                // to a program like `date` because `date` doesn't know what they mean. 
                // The SHELL handles redirection!
                args[j] = NULL; 
                break;
            }
        }

        // 3. FORK
        pid_t pid = fork();

        if (pid == 0) {
            // === CHILD PROCESS ===

            // If a redirect was requested, hijack STDOUT before calling exec!
            if (redirect && outfile != NULL) {
                // Open the file for writing, creating it if necessary
                int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open failed");
                    exit(1);
                }

                // Redirect Output
                dup2(fd, STDOUT_FILENO);
                close(fd); // Remember to close the original FD!
            }

            // Execute the program. If STDOUT was hijacked, the program's 
            // output writes to the file. The program itself has NO idea!
            execvp(args[0], args);

            // This only runs if the program failed to execute
            perror("exec failed (command not found)");
            exit(1);
        } else {
            // === PARENT PROCESS ===
            // The shell simply waits for the child to finish.
            wait(NULL);
        }
    }

    return 0;
}