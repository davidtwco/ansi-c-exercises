#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */
#define PRINT_AFTER 80

/* In the book, this function is called 'getline' but due to
   conflicts with the 'getline' function in stdio.h, we
   prepend an underscore here. */
int _getline(char line[], int maxline);

/* print input lines greater than 80 characters */
main() {
    int len; /* current line length */
    char line[MAXLINE]; /* current input line */

    while((len = _getline(line, MAXLINE)) > 0)
        if (len > PRINT_AFTER)
            printf("%s", line);

    return 0;
}

/* getline: read a line into s, return length */
int _getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}
