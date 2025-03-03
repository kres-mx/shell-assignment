#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * mypipe() function
 * This functin implements a pipe between two programs.
 * - It takes two arrays of arguments: argv1 and argv2.
 * - The output of argv1 is passed as input to argv2.
 * - The function uses fork(), pipe(), and execvp() to achieve this.
 */
void mypipe(char **argv1, char **argv2) {
    int pipefd[2];
    pid_t pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process (argv1)
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // Close write end

        // Execute argv1
        if (execvp(argv1[0], argv1) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process (argv2)
        close(pipefd[1]); // Close write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipefd[0]); // Close read end

        // Execute argv2
        if (execvp(argv2[0], argv2) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    // Example usage
    char *argv1[] = {"ls", "-l", NULL};
    char *argv2[] = {"grep", "g", NULL};
    mypipe(argv1, argv2);
    return 0;
}