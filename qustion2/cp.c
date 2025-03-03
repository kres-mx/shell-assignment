#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * cp() function
 * This functin copies files from a source path to a destination path.
 * It handles paths with spaces and special cases.
 * - If the paths contain spaces, they are combined into one string.
 * - The function uses fopen() and fread()/fwrite() to copy the file.
 */
void cp(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "cp: missing source or destination path\n");
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
        fprintf(stderr, "cp: missing 'to' keyword\n");
        return;
    }

    // Copy file
    FILE *src = fopen(source, "rb");
    if (src == NULL) {
        perror("cp: source file");
        return;
    }

    FILE *dest = fopen(destination, "wb");
    if (dest == NULL) {
        perror("cp: destination file");
        fclose(src);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);
}

int main() {
    // Example usage
    char *input[] = {"cp", "source file.txt", "to", "destination file.txt", NULL};
    cp(input);
    return 0;
}