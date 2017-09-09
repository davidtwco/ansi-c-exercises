#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int c, i, r, v, t;
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

    i = 0;
    while((c = getchar()) != EOF) {
        if (c == '\t') {
            t = (m != 0) ? m : n;

            if (m != 0)
                m = 0;

            r = i % t;
            v = t - r;

            putchar(v);

            for (r = 0; r < v; ++r) {
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
