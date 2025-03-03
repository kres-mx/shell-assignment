#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * delete() function
 * This functin deletes a file at the specified path.
 * It handles paths with spaces by combinig all arguments into one string.
 * - The function uses remove() to delete the file.
 * - If the path contains spaces, it combines all arguments into one string.
 */
void delete(char **str) {
    if (str[1] == NULL) {
        fprintf(stderr, "delete: missing file path\n");
        return;
    }

    // Combine all arguments into one path (handles spaces)
    char path[1024] = "";
    for (int i = 1; str[i] != NULL; i++) {
        strcat(path, str[i]);
        if (str[i + 1] != NULL) {
            strcat(path, " ");
        }
    }

    // Delete the file
    if (remove(path) != 0) {
        perror("delete");
    } else {
        printf("File deleted: %s\n", path);
    }
}

int main() {
    // Example usage
    char *input[] = {"delete", "my file.txt", NULL};
    delete(input);
    return 0;
}