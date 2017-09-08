#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

int getfloat(double *pn);

int main() {
    double r = 0;
    getfloat(&r);

    printf("result: %f\n", r);

    return 0;
}

int getch(void);
void ungetch(int);

/* example from Ch 5, Sec 5.3, Pg 97 */
/* getint: get next integer from input into *pn */
int getfloat(double *pn) {
    int c, i, s, wasSign, sign;

    while(isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if ((wasSign = (c == '+' || c == '-')))
        c = getch();

    if (!isdigit(c)) {
        ungetch(c);
        if (wasSign)
            ungetch((sign == -1) ? '-' : '+');
        return 0;
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    if (c == '.')
        c = getch();

    s = 0;
    for (; isdigit(c); c = getch(), s++)
        *pn = 10 * *pn + (c - '0');

    for (i = 0; i < s; ++i)
        *pn /= 10;

    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) { /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
