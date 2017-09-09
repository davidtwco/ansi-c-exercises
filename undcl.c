#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100
#define MAXPOINTERS 10

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char out[1000]; /* output string */

int getch(void);
void ungetch(int);

/* example from Ch 5, Sec 5.12, Pg 126 */

/* undcl: convert word description to declaration */
int main() {
    int type;
    int i, c, pcount;
    char temp[MAXTOKEN];
    /* We use p to store a string with all the * characters
     * that we will output. */
    char p[MAXPOINTERS];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            /* Extra parentheses are introduced when we are
             * dealing with * characters. */
            else if (type == '*') {
                /* Count the first character */
                pcount++;

                /* Count all the * characters */
                while ((c = getch()) == '*' || c == ' '){
                    if (c == '*'){
                        if (pcount < (MAXPOINTERS - 1))
                            pcount++;
                        else
                            break;
                    }
                }
                /* Put back the last character that wasn't
                 * a *. */
                ungetch(c);

                /* Build up our string of *s */
                for (i = 0; i < pcount; i++){
                    p[i] = '*';
                }
                p[i] = '\0';

                /* Reset the count for future pointers. */
                pcount = 0;

                sprintf(temp, "(%s%s)", p, out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        printf("%s\n", out);
    }
    return 0;
}

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }

    return tokentype = c;
}

#define BUFSIZE 100

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
