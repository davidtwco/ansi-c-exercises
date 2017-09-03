#include<stdio.h>

/* This solution assumes usage with only 16 bit numbers.
 * But it is enough to demonstrate ability to perform
 * the operation. */

unsigned rightrot(unsigned x, int n);

int main() {
    unsigned x = 23587; /* 0101_1100_0010_0011 */
    int n = 3;

    unsigned result = rightrot(x, n);
    printf("result: %u\n", result);

    return 0;
}

unsigned rightrot(unsigned x, int n) {
    // This takes a number with one in all bits, and shifts
    // it n to the right, leaving n zeros on the rightmost
    // side. It then inverts it again, leaving n ones on the
    // rightmost side.
    int rightmostN = ~(~0 << n);

    // We can AND by our rightmost n bits to get those that
    // would be lost.
    int captured = x & rightmostN;

    // We can shift those bits along to their new destination position.
    int captured_shifted = captured << (16 - n);

    // We can shift our original value along, losing the rightmost n
    // and creating n zeroed bits at the left.
    int shifted = x >> n;

    // We can OR to place our captured bits in the leftmost n positions.
    return shifted | captured_shifted;
}
