/* example from Ch 2, Sec 2.8, Pg 48 */
/* strcat: concatenate t to the end of s; s must be big enough */
void strcat(char s[], char t[]) {
    int i, j;

    i = j = 0;
    while (s[i] != '\0')    /* find end of s */
        i++;
    while ((s[i++] = t[j++]) != '\0') /* copy t */
        ;
}
