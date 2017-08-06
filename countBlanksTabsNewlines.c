#include <stdio.h>

/* count blanks, tabs and newlines in input */
main() {
    int c, nl, nb, nt;

    nl = 0;
    nt = 0;
    nb = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n')
            ++nl;
        if (c == '\t')
            ++nt;
        if (c == ' ')
            ++nb;
    }
    printf("Newlines: %d\tTabs: %d\tBlanks: %d\n", nl, nt, nb);
}
