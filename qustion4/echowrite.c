#include <stdio.h>
#include <stdlib.h>

void echowrite(char **args) {
    // Check if the number of arguments is correct
    if (args == NULL || args[0] == NULL || args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        fprintf(stderr, "Usage: echo <string> > <pathFile>\n");
        return;
    }

    // Extract the string to write and the file path
    char *string_to_write = args[1];
    char *file_path = args[3];

    // Open the file in write mode
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the string to the file
    fprintf(file, "%s\n", string_to_write);

    // Close the file
    fclose(file);
}

int main(int argc, char *argv[]) {
    // Simulate the command line arguments
    char *args[] = {"echo", "hello world", ">", "testFile"};
    echowrite(args);
    return 0;
}