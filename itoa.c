#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

void itoa(int n, char s[]);
void reverse(char s[]);

/* original version of itoa did not work with the largest
 * two's complement number as:
 *
 * two's complement uses the first bit for indicating whether
 * the number is negative or not.
 *
 * The result of this is that the largest negative number
 * that can be represented (in say, eight bits) is:
 *
 * -128 = 1000_0000
 *
 * whereas the largest positive is:
 *
 * 127 = 0111_1111
 *
 * Therefore the absolute value of the largest negative number
 * cannot be stored in the same signed type. */

int main() {
    signed largest = INT_MIN;
    char largestString[MAX_SIZE];

    itoa(largest, largestString);
    printf("%d as string: %s\n", largest, largestString);

    return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
    int i, sign;
    sign = n;

    i = 0;
    do { /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0'; /* get next digit */
    } while (n /= 10); /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* taken from example in Ch 3, Sec 3.5, Pg 62 */
/* reverse: reverse string s in place */
void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
