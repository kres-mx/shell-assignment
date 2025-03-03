#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * cd() function
 * This functin changes the current workin directory.
 * It handles paths with spaces and special cases like dashes.
 * - If the path contains spaces, it combines all arguments into one string.
 * - If the path starts with a dash, it handles it as a special case.
 * - The function uses chdir() to change the directory.
 */
void cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }

    // Combine all arguments into one path (handles spaces)
    char path[1024] = "";
    for (int i = 1; args[i] != NULL; i++) {
        strcat(path, args[i]);
        if (args[i + 1] != NULL) {
            strcat(path, " ");
        }
    }

    // Handle special cases (e.g., paths starting with a dash)
    if (path[0] == '-') {
        // Handle dash case (e.g., cd -)
        fprintf(stderr, "cd: special case for dash not implemented\n");
        return;
    }

    // Change directory
    if (chdir(path) != 0) {
        perror("cd");
    }
}

int main() {
    // Example usage
    char *input[] = {"cd", "oneDrive", "Ariel", "University", NULL};
    cd(input);
    return 0;
}