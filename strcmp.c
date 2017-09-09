/* example from Ch 5, Sec 5.5, Pg 106 */
/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t: array subscript version */
int strcmp(char *s, char *t) {
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}
