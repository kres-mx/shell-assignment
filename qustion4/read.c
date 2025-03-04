#include <stdio.h>
#include <stdlib.h>

void read(char **args) {
    // Check if the number of arguments is correct
    if (args == NULL || args[0] == NULL || args[1] == NULL) {
        fprintf(stderr, "Usage: read <pathFile>\n");
        return;
    }

    // Extract the file path
    char *file_path = args[1];

    // Open the file in read mode
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        // If the file does not exist, do nothing
        return;
    }

    // Buffer to hold each line of the file
    char line[1024];

    // Read the file line by line and print to the screen
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    // Close the file
    fclose(file);
}

int main(int argc, char *argv[]) {
    // Simulate the command line arguments
    char *args[] = {"read", "testFile"};
    read(args);
    return 0;
}