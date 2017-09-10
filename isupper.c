/* This is the answer to Ch 7, Ex 9 */

/* The following version of isupper saves space, not requiring a
 * lookup table or macro expansion. */
int isupper(int c) {
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

/* The following version of isupper saves time, as there is no
 * overhead of a function call. However, it will not save space,
 * as the macro will be expanded in-line when invoked. */
#define isupper(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

/* However, the above version will not work when called as below:
 *      isupper(p++)
 * as it will increment twice. */
