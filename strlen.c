/* example from Ch 2, Sec 2.3, Pg 39 */
/* strlen: return length of s */
int strlen(char s[]) {
    int i;

    i = 0;
    while(s[i] != '\0')
        ++i;
    return i;
}
