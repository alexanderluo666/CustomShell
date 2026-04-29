#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void parse_input(char *line, char **args) {
    int i = 0;
    char *token = strtok(line, " \t\r\n");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (!fgets(line, MAX_LINE, stdin)) {
            break; // Ctrl+D
        }

        parse_input(line, args);

        if (args[0] == NULL) {
            continue;
        }

        // EXIT
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // CD (must run in parent)
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd failed");
                }
            }
            continue;
        }

        pid_t pid = fork();

        if (pid == 0) {
            // child
            if (execvp(args[0], args) == -1) {
                perror("command failed");
            }
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // parent
            wait(NULL);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}