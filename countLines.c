#include <stdio.h>

/* example from Ch 2, Sec 1.5.3, Pg 19 */
/* count lines in input */
main() {
    int c, nl;

    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);
}
