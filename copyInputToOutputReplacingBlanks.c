#include <stdio.h>

main() {
    int lastCharWasBlank;
    int c;

    lastCharWasBlank = 0;
    while((c = getchar()) != EOF) {
        if (c == ' ' && lastCharWasBlank)
            continue;

        putchar(c);
        lastCharWasBlank = c == ' ';
    }
}
