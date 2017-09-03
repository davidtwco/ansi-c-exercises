#include <stdio.h>

/* example from Ch 1, Sec 1.5.1, Pg 16, 17 */
/* copy input to output; 2nd edition */
main () {
    int c;

    while ((c = getchar()) != EOF)
        putchar(c);
}
