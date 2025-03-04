#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wordCount(char **args) {
    // Check if the number of arguments is correct
    if (args == NULL || args[0] == NULL || args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "Usage: wc [-l|-w] <pathFile>\n");
        return;
    }

    // Extract the option and file path
    char *option = args[1];
    char *file_path = args[2];

    // Open the file in read mode
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        // If the file does not exist, do nothing
        return;
    }

    int count = 0;
    char line[1024];
    char *token;

    if (strcmp(option, "-l") == 0) {
        // Count lines
        while (fgets(line, sizeof(line), file)) {
            count++;
        }
    } else if (strcmp(option, "-w") == 0) {
        // Count words
        while (fgets(line, sizeof(line), file)) {
            token = strtok(line, " \t\n");
            while (token != NULL) {
                count++;
                token = strtok(NULL, " \t\n");
            }
        }
    } else {
        fprintf(stderr, "Invalid option. Use -l for lines or -w for words.\n");
        fclose(file);
        return;
    }

    // Print the result
    printf("%d\n", count);

    // Close the file
    fclose(file);
}

int main(int argc, char *argv[]) {
    // Simulate the command line arguments
    char *args[] = {"wc", "-l", "testFile"};
    wordCount(args);
    return 0;
}