#include <stdlib.h>
#include <stdio.h>

// It is recommended that when testing, the space character is
// replaced with something visible.

int main(int argc, char *argv[]) {
    int c, i, col, count, nextTabSize, currentTabSize;
    int m = 0, n = 8, cnt;
    char k;

    /* We must to walk through the arguments, looking for '-' */
    while(--argc > 0) {
        if((*++argv)[0] == '-') {
            /* Count letters after it */
            cnt = 1;
            while((k = *++argv[0]))
                switch(k) {
                    case 'n':
                        n = atoi(*(argv+cnt++));
                        break;
                    default:
                        ;
                }
        }
    }

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
                nextTabSize = (m != 0) ? m : n;

                if (m != 0)
                    m = 0;

                currentTabSize = nextTabSize - (col % nextTabSize);

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
