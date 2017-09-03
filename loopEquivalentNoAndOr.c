#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int _getline(char line[], int maxline);

main() {
    char s[MAXLINE];

    _getline(s, MAXLINE);
    printf("%s\n", s);
}

int _getline(char s[], int lim) {
    int i, c;

    /* Equivalent to:
     * for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
     *     s[i] = c;
     *  without && or ||
     */

    for (i = 0; i < lim - 1; ++i) {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;

        s[i] = c;
    }

    s[++i] = '\0';
}
