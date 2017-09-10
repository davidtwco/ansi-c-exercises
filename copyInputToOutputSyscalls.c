#include <stdio.h>
#include "unistd.h"

/* example from Ch 8, Sec 8.2, Pg 171 */

int main() { /* copy input to output */
    char buf[BUFSIZ];
    int n;

    while ((n = read(0, buf, BUFSIZ)) > 0)
        write(1, buf, n);
    return 0;
}
