#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * logout() function
 * This functin handles exiting the terminal while printing a message.
 * It also frees any allocated memory to avoid leaks.
 * - The input string can have spaces before/after "exit" or additional text.
 * - We check if the first word is "exit" and ignore the rest.
 * - If memory was allocated, it is freed before exiting.
 */
void logout(char **str) {
    // Check if the first word is "exit"
    if (str[0] != NULL && strcmp(str[0], "exit") == 0) {
        printf("Logging out... Goodbye!\n");

        // Free allocated memory (if any)
        for (int i = 0; str[i] != NULL; i++) {
            free(str[i]);
        }
        free(str);

        exit(0); // Exit the program
    } else {
        printf("Error: Invalid logout command.\n");
    }
}

int main() {
    // Example usage
    char *input[] = {"exit", " ", "extra", "text", NULL};
    logout(input);
    return 0;
}