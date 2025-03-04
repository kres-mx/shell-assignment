#include <stdio.h>
#include <stdlib.h>

void echopend(char **args) {
    // Check if the number of arguments is correct
    if (args == NULL || args[0] == NULL || args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        fprintf(stderr, "Usage: echo <string> >> <pathFile>\n");
        return;
    }

    // Extract the string to append and the file path
    char *string_to_append = args[1];
    char *file_path = args[3];

    // Open the file in append mode
    FILE *file = fopen(file_path, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the string to the file
    fprintf(file, "%s\n", string_to_append);

    // Close the file
    fclose(file);
}

int main(int argc, char *argv[]) {
    // Simulate the command line arguments
    char *args[] = {"echo", "hello world", ">>", "testFile"};
    echopend(args);
    return 0;
}