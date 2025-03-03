#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * my() function
 * This functin transfers a file from a source path to a destination path.
 * It handles paths with spaces and checks if the file or path exists.
 * - The function uses fopen() and fread()/fwrite() to copy the file.
 * - If the source file or destination path does not exist, it prints an error.
 */
void my(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "my: missing source or destination path\n");
        return;
    }

    // Combine source path arguments
    char source[1024] = "";
    for (int i = 1; args[i] != NULL && strcmp(args[i], "to") != 0; i++) {
        strcat(source, args[i]);
        if (args[i + 1] != NULL && strcmp(args[i + 1], "to") != 0) {
            strcat(source, " ");
        }
    }

    // Combine destination path arguments
    char destination[1024] = "";
    int to_found = 0;
    for (int i = 1; args[i] != NULL; i++) {
        if (strcmp(args[i], "to") == 0) {
            to_found = 1;
            continue;
        }
        if (to_found) {
            strcat(destination, args[i]);
            if (args[i + 1] != NULL) {
                strcat(destination, " ");
            }
        }
    }

    if (!to_found) {
        fprintf(stderr, "my: missing 'to' keyword\n");
        return;
    }

    // Open source file
    FILE *src = fopen(source, "rb");
    if (src == NULL) {
        perror("my: source file");
        return;
    }

    // Open destination file
    FILE *dest = fopen(destination, "wb");
    if (dest == NULL) {
        perror("my: destination file");
        fclose(src);
        return;
    }

    // Copy file
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) {
        fwrite(buffer, 1, bytes, dest);
    }

    // Close files
    fclose(src);
    fclose(dest);

    printf("File transferred: %s -> %s\n", source, destination);
}

int main() {
    // Example usage
    char *input[] = {"my", "source file.txt", "to", "destination file.txt", NULL};
    my(input);
    return 0;
}