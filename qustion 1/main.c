#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * getLocation() function
 * Displays the current working directory, username, and terminal name.
 * Uses ANSI escape codes for colors and highlighting.
 */
void getLocation() {
    char cwd[1024];
    char *username = getlogin();

    if (getcwd(cwd, sizeof(cwd))) {
        printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m$ ", username, "RA", cwd);
    } else {
        perror("getcwd() error");
    }
}

/*
 * splitArgument() function
 * Splits a string into an array of arguments based on spaces.
 * Handles edge cases like multiple spaces and returns a pointer to the array.
 */
char** splitArgument(char* str) {
    int capacity = 10; // Initial capacity for the array
    char** args = (char**)malloc(capacity * sizeof(char*));
    if (!args) {
        perror("malloc() failed");
        return NULL;
    }

    int count = 0;
    char* token = strtok(str, " ");
    while (token != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            args = (char**)realloc(args, capacity * sizeof(char*));
            if (!args) {
                perror("realloc() failed");
                return NULL;
            }
        }
        args[count] = strdup(token); // Duplicate the token
        if (!args[count]) {
            perror("strdup() failed");
            return NULL;
        }
        count++;
        token = strtok(NULL, " ");
    }

    // Add NULL at the end to mark the end of the array
    args = (char**)realloc(args, (count + 1) * sizeof(char*));
    if (!args) {
        perror("realloc() failed");
        return NULL;
    }
    args[count] = NULL;

    return args;
}

/*
 * Main function
 * This is the entry point of the program.
 * It simulates a shell-like environment where the user can enter commands.
 * - getLocation() is called to display the prompt.
 * - fgets() is used to read user input.
 * - splitArgument() is used to split the input into arguments.
 * - The arguments are printed and memory is freed after use.
 */
int main() {
    char input[1024];

    while (1) {
        getLocation();
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // Remove newline
            char** args = splitArgument(input);

            if (args) {
                for (int i = 0; args[i] != NULL; i++) {
                    printf("Argument %d: %s\n", i, args[i]);
                    free(args[i]);
                }
                free(args);
            }
        } else {
            break;
        }
    }

    return 0;
}