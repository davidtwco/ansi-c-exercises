#include<stdio.h>

void squeeze(char s1[], char s2[]);
int contains(char s[], char c);

int main() {
    char a[] = "abcdefghijklmnopqrstuvwxyz";
    squeeze(a, "aeiou");
    printf("%s without characters from %s: %s\n",
           "abcdefghijklmnopqrstuvwxyz",
           "aeiou", a);
}

/* squeeze: delete all characters in s1 that are in s2 */
void squeeze(char s1[], char s2[]) {
    int i, j;

    for (i = j = 0; s1[i] != '\0'; i++)
        if (!contains(s2, s1[i]))
            s1[j++] = s1[i];
    s1[j] = '\0';
}

int contains(char s[], char c) {
    int i;

    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == c)
            return 1;

    return 0;
}
