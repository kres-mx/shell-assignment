#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * splitArgument() function
 * This functin splits a string into an array of arguments based on spaces.
 * It handles edge cases like multiple spaces and returns a pointer to the array.
 * - strtok() is used to split the string into tokens.
 * - Dynamic memory allocation is used for the array of arguments.
 * - strdup() duplicates each token to store it in the array.
 * - The array is terminated with NULL to mark its end.
 * - Memory is freed after use to avoid leaks.
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

int main() {
    char input[] = "cd OneDrive - Ariel University";
    char** args = splitArgument(input);

    if (args) {
        for (int i = 0; args[i] != NULL; i++) {
            printf("Argument %d: %s\n", i, args[i]);
            free(args[i]); // Free each argument
        }
        free(args); // Free the array itself
    }

    return 0;
}