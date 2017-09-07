#include <stdio.h>

/* example from Ch 4, Sec 4.10, Pg 87 */
/* printd: print n in decimal */
void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}
