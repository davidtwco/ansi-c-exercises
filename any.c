#include<stdio.h>

int any(char s1[], char s2[]);

int main() {

    printf("First character from '%s' in '%s' is at: %d\n",
           "r", "abcdefghijklmnopqrstuvwxyz",
           any("abcdefghijklmnopqrstuvwxyz", "r"));

    printf("First character from '%s' in '%s' is at: %d\n",
           "&", "abcdefghijklmnopqrstuvwxyz",
           any("abcdefghijklmnopqrstuvwxyz", "&"));

    return 0;
}

int any(char s1[], char s2[]) {
    int i, j;

    for (i = 0; s1[i] != '\0'; ++i)
        for (j = 0; s2[j] != '\0'; ++j)
            if (s1[i] == s2[j])
                return i;

    return -1;
}
