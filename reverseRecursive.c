#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main() {
    char test[] = "abcdefghijklmnopqrstuvwxyz";

    printf("normal: %s\n", test);
    reverse(test);
    printf("reversed: %s\n", test);

    return 0;
}

/* reverse: reverse string s in place recursively */
void _reverse(char s[], int i, int j);

void reverse(char s[]) {
    _reverse(s, 0, strlen(s) - 1);
}

void _reverse(char s[], int i, int j) {
    if (i > j)
        return;

    int temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    _reverse(s, ++i, --j);
}
