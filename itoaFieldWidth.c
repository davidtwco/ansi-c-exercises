#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

void itoa(int n, char s[], int fw);
void reverse(char s[]);

int main() {
    signed normal = -283819;
    char normalString[MAX_SIZE];

    itoa(normal, normalString, 24);
    printf("%d as string: %s\n", normal, normalString);

    return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int fw) {
    int i, j, req, sign;
    sign = n;

    i = 0;
    do { /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0'; /* get next digit */
    } while (n /= 10); /* delete it */

    /* Before we add a sign, add any required padding characters.
     * After reversal, will end up on the left, as required. */
    req = fw - i - ((sign < 0) ? 1 : 0);
    for(j = 0; j < req; j++)
        s[i++] = '0';

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
