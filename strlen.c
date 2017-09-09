/* example from Ch 5, Sec 5.3, Pg 99 */
/* strlen: return length of s */
int strlen(char *s) {
    int n;

    for (n = 0; *s != '\0'; s++)
        ++n;
    return n;
}
