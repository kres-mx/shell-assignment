#include <stdio.h>
#include <unistd.h>

/*
 * getLocation() function
 * This functin displays the current workin directory, username, and terminal name.
 * It uses ANSI escape codes to add colors and highlightin to make it look like a real terminal.
 * - getcwd() is used to get the current workin directory.
 * - getlogin() is used to get the username.
 * - The terminal name is hardcoded as "RA".
 * - ANSI codes like \033[1;32m are used for bold green and \033[1;34m for bold blue.
 */
void getLocation() {
    char cwd[1024];
    char *username = getlogin();

    if (getcwd(cwd, sizeof(cwd))) {
        printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m$ ", username, "RA", cwd);
    } else {
        perror("getcwd() error");
    }
}

int main() {
    getLocation();
    return 0;
}
