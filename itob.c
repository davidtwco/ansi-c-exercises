#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

void itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
    int normal = 14;
    char normalString[MAX_SIZE];

    itob(normal, normalString, 10);
    printf("%d (base 10) as string: %s\n", normal, normalString);

    itob(normal, normalString, 2);
    printf("%d (base 2) as string: %s\n", normal, normalString);

    itob(normal, normalString, 8);
    printf("%d (base 8) as string: %s\n", normal, normalString);

    itob(normal, normalString, 16);
    printf("%d (base 16) as string: %s\n", normal, normalString);

    signed largest = INT_MIN;
    char largestString[MAX_SIZE];

    itob(largest, largestString, 10);
    printf("%d (base 10) as string: %s\n", largest, largestString);

    itob(largest, largestString, 2);
    printf("%d (base 2) as string: %s\n", largest, largestString);

    itob(largest, largestString, 8);
    printf("%d (base 8) as string: %s\n", largest, largestString);

    itob(largest, largestString, 16);
    printf("%d (base 16) as string: %s\n", largest, largestString);

    return 0;
}

/* itob: convert n in base b to characters in s */
void itob(int n, char s[], int b) {
    int i, j, sign;
    sign = n;

    i = 0;
    do { /* generate digits in reverse order */
        j = abs(n % b); /* get next digit */
        s[i++] = j + ((j > 9) ? 'A' - 10 : '0');
    } while (n /= b); /* delete it */
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
