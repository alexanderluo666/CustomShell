#include <stdio.h>
#include <string.h>
#include "../core/engine.h"

int main() {
    char input[256];
    char output[2048];

    while (1) {
        printf("CustomShell> ");
        fgets(input, sizeof(input), stdin);
        #include <stdio.h>
        #include <string.h>
        #include "../core/engine.h"

        int main() {
            char input[256];
            char output[2048];

            while (1) {
                printf("CustomShell> ");
                fgets(input, sizeof(input), stdin);

                input[strcspn(input, "\n")] = 0;

                if (strcmp(input, "exit") == 0)
                    break;

                output[0] = '\0';
                execute_command(input, output);

                printf("%s", output);
            }

            return 0;
        }
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0)
            break;

        output[0] = '\0';
        execute_command(input, output);

        printf("%s", output);
    }

    return 0;
}
