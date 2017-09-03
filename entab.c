#include <stdio.h>

#define SIZE_OF_TAB 8 /* size of tabs in spaces */

// It is recommended that when testing, the space character is
// replaced with something visible.

main() {
    int c, i, col, count, currentTabSize;

    count = 0;
    col = 0;
    while((c = getchar()) != EOF) {
        if (c == ' ') {
            ++count;
        } else {
            while (count != 0) {
                // We need to keep track of what size the tab
                // will be when we print it - this will vary
                // depending on the distance to the tab stop.
                currentTabSize = SIZE_OF_TAB - (col % SIZE_OF_TAB);

                if (count >= currentTabSize) {
                    putchar('\t');

                    col = 0;
                    count -= currentTabSize;
                } else {
                    for (i = 0; i < count; ++i) {
                        putchar(' ');

                        count -= 1;
                        ++col;
                    }
                }
            }

            putchar(c);
            count = 0;
            ++col;
        }

        if (c == '\n')
            col = 0;
    }

    return 0;
}
