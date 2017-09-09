/* example from Ch 5, Sec 5.4, Pg 103 */
/* strlen: return length of s */
int strlen(char *s) {
    char *p = s;

    while (*p != '\0')
        p++;
    return p - s;
}
