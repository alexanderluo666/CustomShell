#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "engine.h"

/* ================= FILE COMMANDS ================= */

void cmd_pwd(char *output) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    strcat(output, cwd);
    strcat(output, "\n");
}

void cmd_ls(char *output) {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (!dp) {
        strcat(output, "ls failed\n");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_name[0] != '.') {
            strcat(output, entry->d_name);
            strcat(output, "  ");
        }
    }

    strcat(output, "\n");
    closedir(dp);
}

void cmd_cat(char *file, char *output) {
    FILE *f = fopen(file, "r");

    if (!f) {
        strcat(output, "cat failed\n");
        return;
    }

    char c;
    while ((c = fgetc(f)) != EOF) {
        int len = strlen(output);
        output[len] = c;
        output[len + 1] = '\0';
    }

    fclose(f);
}

/* ================= DISPATCHER ================= */

void execute_command(const char *input, char *output) {
    char cmd[128], arg[128];
    sscanf(input, "%s %s", cmd, arg);

    if (strcmp(cmd, "pwd") == 0) {
        cmd_pwd(output);
    }
    else if (strcmp(cmd, "ls") == 0) {
        cmd_ls(output);
    }
    else if (strcmp(cmd, "cat") == 0) {
        cmd_cat(arg, output);
    }
    else if (strcmp(cmd, "cd") == 0) {
        if (chdir(arg) != 0) {
            strcat(output, "cd failed\n");
        }
    }
    else {
        strcat(output, "Unknown command\n");
    }
}
