/* example from Ch 2, Sec 2.10, Pg 50 */
/* bitcount: count 1 bits in x */
int bitcount(unsigned x) {
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}
