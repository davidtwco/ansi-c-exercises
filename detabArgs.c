#include <stdlib.h>
#include <stdio.h>

#define SIZE_OF_TAB 8 /* size of tabs in spaces */

int main(int argc, char *argv[]) {
    int c, i, r, n, t;

    i = 0;
    while((c = getchar()) != EOF) {
        if (c == '\t') {
            t = (--argc > 0) ? atoi(*++argv) : SIZE_OF_TAB;
            r = i % t;
            n = t - r;

            putchar(n);

            for (r = 0; r < n; ++r) {
                putchar(' ');
                ++i;
            }
        } else {
            ++i;
            putchar(c);
        }

        if (c == '\n')
            i = 0;
    }

    return 0;
}
