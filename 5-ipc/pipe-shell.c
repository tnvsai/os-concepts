/**
 * 🎓 OS CONCEPTS: Inter-Process Communication (Pipes & dup2)
 * 
 * DESCRIPTION:
 * This program implements a miniature Bash shell that actually supports the 
 * pipe operator `|`. For example, it can execute `ls -l | grep ".c"`.
 * 
 * To achieve this, the shell must:
 * 1. Create a `pipe()` which acts as an invisible data tunnel in memory.
 * 2. Fork TWO children processes (one for the left command, one for the right).
 * 3. Use `dup2()` to secretly disconnect Process 1's standard output (screen) 
 *    and plug it into the pipe.
 * 4. Use `dup2()` to secretly disconnect Process 2's standard input (keyboard) 
 *    and plug it into the other end of the same pipe.
 */

#include <stdio.h>
#include <unistd.h>     // For fork(), pipe(), dup2(), execvp()
#include <string.h>     // For strtok()
#include <sys/wait.h>   // For wait()
#include <stdlib.h>     // For exit()

#define MAX_CMD_LEN 100
#define MAX_ARGS 10

int main() {
    char cmd[MAX_CMD_LEN];

    printf("Welcome to the Pipe Shell! Try typing: ls | wc -l\n\n");

    while (1) {
        printf("my_shell> ");
        
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) break;
        cmd[strcspn(cmd, "\n")] = 0; // Strip newline

        if (strlen(cmd) == 0) continue;
        if (strcmp(cmd, "exit") == 0) break;

        /*
         * 1. PARSE THE INPUT
         * We look for a '|' character to split the input into two separate commands.
         */
        char *cmd1_str = strtok(cmd, "|");
        char *cmd2_str = strtok(NULL, "|");

        if (cmd2_str == NULL) {
            // ==========================================
            // NORMAL COMMAND (No Pipe)
            // ==========================================
            char *args[MAX_ARGS];
            int i = 0;

            char *token = strtok(cmd1_str, " ");
            while (token != NULL) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL); // Parent waits for the single child
            }
        } 
        else {
            // ==========================================
            // PIPED COMMAND (e.g., "ls | wc -l")
            // ==========================================
            
            /* 
             * fd[0] will be the READ end of the pipe.
             * fd[1] will be the WRITE end of the pipe.
             */
            int fd[2];
            if (pipe(fd) == -1) {
                perror("pipe failed");
                continue;
            }

            // --- SPAWN PROCESS 1 (The Left Side of | ) ---
            pid_t pid1 = fork();

            if (pid1 == 0) {
                /*
                 * 🎩 THE MAGIC TRICK (Write to Pipe)
                 * STDOUT_FILENO (usually 1) points to the computer monitor.
                 * dup2(fd[1], STDOUT_FILENO) forces STDOUT_FILENO to point to the pipe's write-end instead!
                 * Now, any `printf` or standard output from this program goes directly into the pipe.
                 */
                dup2(fd[1], STDOUT_FILENO); 
                
                // We MUST close the original file descriptors, or the pipe will hang!
                close(fd[0]);
                close(fd[1]);

                // Parse and execute Left Command
                char *args1[MAX_ARGS];
                int i = 0;
                char *token = strtok(cmd1_str, " ");
                while (token != NULL) {
                    args1[i++] = token;
                    token = strtok(NULL, " ");
                }
                args1[i] = NULL;

                execvp(args1[0], args1);
                perror("exec1 failed");
                exit(1);
            }

            // --- SPAWN PROCESS 2 (The Right Side of | ) ---
            pid_t pid2 = fork();

            if (pid2 == 0) {
                /*
                 * 🎩 THE MAGIC TRICK (Read from Pipe)
                 * STDIN_FILENO (usually 0) points to the keyboard.
                 * dup2(fd[0], STDIN_FILENO) forces STDIN_FILENO to point to the pipe's read-end instead!
                 * Now, if this program asks for user input, it automatically reads data coming out of the pipe.
                 */
                dup2(fd[0], STDIN_FILENO); 
                
                close(fd[1]);
                close(fd[0]);

                // Parse and execute Right Command
                char *args2[MAX_ARGS];
                int i = 0;
                char *token = strtok(cmd2_str, " ");
                while (token != NULL) {
                    args2[i++] = token;
                    token = strtok(NULL, " ");
                }
                args2[i] = NULL;

                execvp(args2[0], args2);
                perror("exec2 failed");
                exit(1);
            }

            // --- SHELL PARENT PROCESS ---
            
            // The shell itself doesn't need to read or write to this particular pipe, 
            // so it must close both ends. If the parent leaves the write-end open, 
            // the second process will wait forever for more data because it thinks 
            // a writer is still alive!
            close(fd[0]);
            close(fd[1]);

            // The shell must wait for BOTH children to finish their piped conversation.
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }

    printf("Exiting Pipe Shell...\n");
    return 0;
}