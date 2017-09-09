/* example from Ch 5, Sec 5.5, Pg 106 */

/* strcpy: copy t to s: pointer version 3 */
void strcpy(char *s, char *t) {
    while ((*s++ = *t++))
        ;
}
