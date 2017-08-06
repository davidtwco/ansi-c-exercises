#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

/* In the book, this function is called 'getline' but due to
   conflicts with the 'getline' function in stdio.h, we
   prepend an underscore here. */
int _getline(char line[], int maxline);
void reverse(char line[], int len);

/* reverse input lines */
main() {
    int len; /* current line length */
    char line[MAXLINE]; /* current input line */

    while((len = _getline(line, MAXLINE)) > 0) {
        reverse(line, len);
        printf("%s\n", line);
    }

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

/* reverse: reverse a line */
void reverse(char line[], int length) {
    int a, b, i;

    for (i = 0; i < length / 2; i++) {
        a = line[i];
        b = line[length-i-1];

        line[i] = b;
        line[length-i-1] = a;
    }
}
