#include <stdio.h>

/* example from Ch 1, Sec 1.5.2, Pg 18 */
/* count characters in input; 2nd version */
main() {
    double nc;

    for (nc = 0; getchar() != EOF; ++nc)
        ;
    printf("%.0f\n", nc);
}
