#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

void itoa(int n, char s[]);

int main() {
    signed largest = INT_MIN;
    char largestString[MAX_SIZE];

    itoa(largest, largestString);
    printf("%d as string: %s\n", largest, largestString);

    return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
    static int i;
    static int sign = 0;

    if (sign == 0) {
        sign = (n < 0) ? -1 : 1;
        i = 0;
    }

    if (n / 10)
        itoa(n / 10, s);

    if (sign != 0) {
        if (sign < 0)
            s[i++] = '-';
        sign = 0;
    }

    s[i++] = abs(n % 10) + '0'; /* get next digit */
    s[i] = '\0';
}
