#include <ctype.h>
#include <stdio.h>
#define NUMBER 'N' /* signal that a number was found */

int getch(void);

/* based on original getop function */
int getop(char *s)
{
    int c;
    static int buf = EOF;

    if (buf != EOF && buf != ' ' && buf != '\t'
            && !isdigit(buf) && buf != '.') {
        c = buf;
        buf = EOF;
        return c;
    }
    if (buf == EOF || buf == ' ' || buf == '\t')
        while ((*s = c = getch()) == ' ' || c == '\t')
            ;
    else
        *s = c = buf;

    buf = EOF;
    *(s + 1) = '\0';

    if (!isdigit(c) && c != '.')
        return c;       /* not a number */

    if (isdigit(c))     /* collect integer part */
        while (isdigit(*++s = c = getch()))
            ;

    if (c == '.')       /* collect fraction part */
        while (isdigit(*++s = c = getch()))
            ;

    *++s = '\0';
    buf = c;
    return NUMBER;
}
