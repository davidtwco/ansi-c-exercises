#include <string.h>

/* example from Ch 3, Sec 3.7, Pg 65 */
/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[]) {
    int n;

    for (n = strlen(s)-1; n >= 0; n--)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
    return n;
}
