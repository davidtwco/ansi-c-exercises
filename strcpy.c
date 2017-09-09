/* example from Ch 5, Sec 5.5, Pg 105 */

/* strcpy: copy t to s: pointer version 2 */
void strcpy(char *s, char *t) {
    while ((*s++ = *t++) != '\0')
        ;
}
