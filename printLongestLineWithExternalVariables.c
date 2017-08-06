#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int max; /* maximum length seen so far */
char line[MAXLINE]; /* current input line */
char longest[MAXLINE]; /* longest line saved here */

/* In the book, this function is called 'getline' but due to
   conflicts with the 'getline' function in stdio.h, we
   prepend an underscore here. */
int _getline(void);
void copy(void);

/* print longest input line */
main() {
    int len; /* current line length */

    max = 0;
    while((len = _getline()) > 0)
        if (len > max) {
            max = len;
            copy();
        }

    if (max > 0) /* there was a line */
        printf("%s", longest);
    return 0;
}

/* getline: specialized version */
int _getline() {
    int c, i;
    extern char line[];

    for (i = 0; i < MAXLINE - 1
            && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';
    return i;
}

/* copy: specialized version */
void copy() {
    int i;
    extern char line[], longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
