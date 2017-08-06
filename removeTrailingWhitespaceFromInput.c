#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

/* In the book, this function is called 'getline' but due to
   conflicts with the 'getline' function in stdio.h, we
   prepend an underscore here. */
int _getline(char line[], int maxline);

/* print input lines without trailing whitespace */
main() {
    int len; /* current line length */
    char line[MAXLINE]; /* current input line */

    while((len = _getline(line, MAXLINE)) > 0)
        printf("%s", line);

    return 0;
}

/* getline: read a line into s, return length */
int _getline(char s[], int lim) {
    int c, i;
    int consecutiveWhitespaceChars;

    consecutiveWhitespaceChars = 0;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        if (c == ' ' || c == '\t')
            ++consecutiveWhitespaceChars;
        else
        consecutiveWhitespaceChars = 0;

        s[i] = c;
    }

    if (c == '\n') {
        s[i-consecutiveWhitespaceChars] = c;
        ++i;
    }

    s[i-consecutiveWhitespaceChars] = '\0';

    return i;
}
