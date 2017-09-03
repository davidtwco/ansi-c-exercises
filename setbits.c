#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main() {
    unsigned x = 23587; /* 0101_1100_0010_0011 */
    unsigned y = 54635; /* 1101_0101_0110_1011 */
    int p = 8, n = 3;

    unsigned result = setbits(x, p, n, y);
    printf("result: %u\n", result);

    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    // This takes a number with one in all bits, and shifts
    // it n to the right, leaving n zeros on the rightmost
    // side. It then inverts it again, leaving n ones on the
    // rightmost side.
    int rightmostN = ~(~0 << n);

    // This gets a number representing n digits at the desired
    // position. We need to increment p by one because p is
    // zero-indexed while n is not.
    int nDigits = (p+1-n);

    // We can shift along our ones to the desired position then
    // invert to create only zeros at the desired position.
    int m = ~(rightmostN << nDigits);

    int a, b;

    // We can apply the mask to x to ensure that the
    // desired destination is all zeros.
    a = x & m;

    // Zero out all but the rightmost n bits we need.
    b = y & rightmostN;

    // Shift along until the rightmost n bits are now
    // in the correct position.
    b = b << nDigits;

    return a | b;
}
