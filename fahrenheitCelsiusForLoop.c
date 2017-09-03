#include <stdio.h>

#define    LOWER   0    /* lower limit of the table */
#define    UPPER   300  /* upper limit */
#define    STEP    20   /* step size */

/* example from Ch 1, Sec 1.3, Pg 13 */
/* print Fahrenheit-Celsius table */
main() {
    int fahr;

    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
