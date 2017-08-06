#include <stdio.h>

#define IN 1
#define OUT 0

main() {
    int c, state;

    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t')
            state =  OUT;
        else if (state == OUT) {
            state = IN;
            putchar('\n');
        }

        putchar(c);
    }
}
