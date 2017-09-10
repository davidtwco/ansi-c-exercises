#include<stdio.h>
#include<ctype.h>

#define MAXLINE 100 /* maximum number of chars in one line */

int incrementColumn(int, int);

/* print arbitrary input in a sensible way */
int main(void) {
    int c, col;

    col = 0; /* position in the line */
    while ((c=getchar()) != EOF)
        /* Use std function to check for non-printable char. */
        if (iscntrl(c) || c == ' ') {
            col = incrementColumn(col, 6); /* increment by length of octal val */
            printf("\\%03o", c);

            /* If newline, reset col count. */
            if(c == '\n')
                col = 0;

            putchar('\n');
        }
        else {
            /* Printable character */
            col = incrementColumn(col, 1);
            putchar(c);
        }
    return 0;
}

/* inc : increment position counter for output */
int incrementColumn(int col, int n) {
    if (col + n < MAXLINE)
        return col + n;
    else {
        putchar('\n');
        return n;
    }
}
