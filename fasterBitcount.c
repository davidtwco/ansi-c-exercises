/* x &= (x-1) deletes the rightmost 1-bit when using two's compliment
 * because:
 *
 * When x is odd, (x-1) will remove the rightmost bit (since in odd numbers,
 * the bit in the rightmost position is what makes it odd) - the rest of
 * the number remains the same. Then, doing an ADD with the original value,
 * which only differs by the rightmost bit, will remove the rightmost bit.
 *
 * When x is even, (x-1) will change the rightmost zeroes to ones and the
 * rightmost one to a zero. Therefore, doing an AND will clear all the
 * bits that have changed, ie. the rightmost one and zeros - removing
 * the rightmost one from x.
 *
 * */
int bitcount(unsigned x) {
    int b = 0;

    for (b =0; x != 0; x &= (x-1))
        ++b;
    return b;
}
