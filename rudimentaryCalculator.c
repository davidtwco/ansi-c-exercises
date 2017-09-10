#include <stdio.h>

/* example from Ch 7, Sec 7.4, Pg 158 */

int main() { /* rudimentary calculator */
    double sum, v;

    sum = 0;
    while (scanf("%lf", &v) == 1)
        printf("\t%.2f\n", sum += v);
    return 0;
}
