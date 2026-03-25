/**
 * 🎓 OS CONCEPTS: The Exec Family (Replacing a Process)
 * 
 * DESCRIPTION:
 * fork() clones a process, but what if you want to run a completely DIFFERENT program?
 * You use the `exec()` family of system calls. `exec` completely overwrites the 
 * calling process's memory (code, data, stack) with a new executable program from disk.
 * 
 * This file creates a very basic "Shell" (like bash or zsh) to demonstrate the 
 * classic "Fork-Exec-Wait" loop used to run most programs.
 */

#include <stdio.h>
#include <unistd.h>    // For fork() and execvp()
#include <string.h>    // For string manipulation (strcspn, strtok, strcmp)
#include <sys/wait.h>  // For wait()
#include <stdlib.h>    // For exit()

#define MAX_CMD_LEN 100
#define MAX_ARGS 10

int main()
{
    char cmd[MAX_CMD_LEN];     // Buffer to hold the user's raw input
    char *args[MAX_ARGS];      // Array of strings to be passed as arguments to execvp

    printf("Welcome to my basic shell! Type a command like 'ls -l' or 'date', or 'exit' to quit.\n\n");

    // The infinite loop of a Shell: Read, Parse, Execute, Wait.
    while (1)
    {
        // 1. PRINT SHELL PROMPT
        printf("my_shell> ");

        // 2. READ INPUT line from the user. (fgets is safer than scanf).
        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
            break;

        // 3. CLEAN INPUT: Remove the trailing newline character '\n' added when the user pressed Enter.
        cmd[strcspn(cmd, "\n")] = 0;

        // 4. Handle empty input (user just pressed enter)
        if (strlen(cmd) == 0)
            continue;

        // 5. BUILT-IN COMMANDS: These must be executed by the shell itself, not a child!
        if (strcmp(cmd, "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }

        // 6. PARSE INPUT: Split the string by spaces into an array of arguments using strtok.
        int i = 0;
        args[i] = strtok(cmd, " "); // The first word is the command itself (e.g., "ls")

        while (args[i] != NULL && i < MAX_ARGS - 1)
        {
            i++;
            args[i] = strtok(NULL, " "); // Get the next word (e.g., "-l")
        }
        
        // execvp() absolutely requires that the array of arguments ends with a NULL pointer!
        args[i] = NULL;  

        // ==========================================
        // 7. THE FORK-EXEC-WAIT PATTERN HAPPENS HERE
        // ==========================================
        
        // Step A: Clone the shell
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            continue;
        }
        else if (pid == 0)
        {
            // === CHILD PROCESS ===
            // Step B: Replace the clone with the new program

            /*
             * execvp(file, arguments)
             * - 'file': The name of the file to execute (e.g., "ls"). Uses the PATH environment variable.
             * - 'arguments': The array of arguments, starting with the command name itself.
             */
            execvp(args[0], args);

            /*
             * ⚠️ CRITICAL KNOWLEDGE:
             * If execvp is successful, IT NEVER RETURNS. The child's code is entirely destroyed
             * and replaced by the new program. 
             * Therefore, any code written BELOW exec() will ONLY run if exec() FAILED.
             */
            perror("exec failed (command not found)");

            // If exec fails, the child must immediately die. We don't want a clone of the 
            // shell living on and taking command inputs!
            exit(1);
        }
        else
        {
            // === PARENT PROCESS (The Shell) ===
            // Step C: Wait for the new program to finish before asking for the next command.
            
            int status;
            wait(&status);

            // Optional: You can check how the child program exited.
            if (WIFEXITED(status))
            {
                int exit_code = WEXITSTATUS(status);
                // printf("[Debug] Program exited with code: %d\n", exit_code);
            }
        }
    }

    return 0;
}