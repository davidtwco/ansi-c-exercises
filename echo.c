#include <stdio.h>

/* example from Ch 5, Sec 5.10, Pg 115 */

/* echo command line arguments; 2st version */
int main(int argc, char *argv[]) {
    while(--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");
    printf("\n");
    return 0;
}
