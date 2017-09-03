#include<stdio.h>

int htoi(char s[]);

int main() {
    printf("0x5F23 == %d\n", htoi("0x5F23"));
    printf("5F23 == %d\n", htoi("5F23"));

    return 0;
}

int htoi(char s[]) {
    int i, c, n, v;

    n = 0;
    for (i = 0; s[i] != '\0'; ++i)  {
        c = s[i];

        // We will use v to hold our numbers in decimal.
        //
        // If the value is x/X (from the 0x or 0X start)
        // then it will remain zero and not change the result.
        v = 0;

        // If between a/A and f/F then we take the lower
        // bound away to find the value between 0-5 that
        // corresponds to the a-f/A-F. Then we add 10 to
        // make it the decimal value.
        if (c >= 'a' && c <= 'f')
            v = 10 + (c - 'a');

        if (c >= 'A' && c <= 'F')
            v = 10 + (c - 'A');

        // We do not need to add 10 for the normal digits.
        if (c >= '0' && c <= '9')
            v = c - '0';

        n = (16 * n) + v;
    }
    return n;
}
