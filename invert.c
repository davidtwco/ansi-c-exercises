#include<stdio.h>

unsigned invert(unsigned x, int p, int n);

int main() {
    unsigned x = 23587; /* 0101_1100_0010_0011 */
    int p = 9, n = 3;

    unsigned result = invert(x, p, n);
    printf("result: %u\n", result);

    return 0;
}

unsigned invert(unsigned x, int p, int n) {
    // This takes a number with one in all bits, and shifts
    // it n to the right, leaving n zeros on the rightmost
    // side. It then inverts it again, leaving n ones on the
    // rightmost side.
    int rightmostN = ~(~0 << n);

    // This gets a number representing n digits at the desired
    // position. We need to increment p by one because p is
    // zero-indexed while n is not.
    int nDigits = (p+1-n);

    // We can shift along our ones to the desired position.
    int m = rightmostN << nDigits;

    // We can do x & m to get only the bits that would be inverted.
    int inverted = x & m;
    // We can then invert those bits.
    inverted = ~inverted;
    // If we perform the mask again, we keep only our inverted bits.
    inverted = inverted & m;

    // Using the same mask, we can zero out the destination.
    int zeroed = x & ~m;

    // Using OR we can place the inverted bits in the destination.
    return zeroed | inverted;
}
