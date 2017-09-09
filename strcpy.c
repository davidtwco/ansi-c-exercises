/* example from Ch 5, Sec 5.5, Pg 105 */

/* strcpy: copy t to s: array subscript version */
void strcpy(char *s, char *t) {
    int i;

    i = 0;
    while((s[i] = t[i]) != '\0')
        i++;
}
