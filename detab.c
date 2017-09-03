#include <stdio.h>

#define SIZE_OF_TAB 6 /* size of tabs in spaces */

main() {
    int c, i, r, n;

    i = 0;
    while((c = getchar()) != EOF) {
        if (c == '\t') {
            r = i % SIZE_OF_TAB;
            n = SIZE_OF_TAB - r;

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
