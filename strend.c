#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main() {
    char *s = "Start. End.";
    char *t = "End.";

    printf("'%s' at the end of '%s'?: %d\n", t, s, strend(s, t));

    return 0;
}

int strend(char *s, char *t) {
    unsigned long tLength = strlen(t);

    /* If t is bigger than s then s definitely does
     * not end in t */
    if (tLength > strlen(s))
        return 0;

    /* If the strings are equal then s ends in t */
    if (strcmp(s, t) == 0)
        return 1;

    /* While we're still in s and there is enough
     * characters left to fit t */
    while (*s && strlen(s) >= tLength) {
        s++;

        if (strcmp(s, t) == 0)
            return 1;
    }
    return 0;
}
