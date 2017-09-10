#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int (*conv[2])(int) = { toupper, tolower };
    int func;
    char c;

    if (argc >= 1) {
        if (strcmp(argv[0], "./upper") == 0)
            func = 0;
        else if (strcmp(argv[0], "./lower") == 0)
            func = 1;
        else {
            printf("error: binary must be named upper or lower\n");
            return 1;
        }
    } else
        return 1;

    while ((c = getchar()) != EOF)
        putchar((conv[func])(c));

    return 0;
}
