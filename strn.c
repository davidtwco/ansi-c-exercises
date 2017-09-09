#include <stdio.h>
#include <string.h>

void _strncpy(char *s, char *t, size_t n);
void _strncat(char *s, char *t, size_t n);
int _strncmp(char *s, char *t, size_t n);

int main() {
    char s[100];
    strcpy(s, "This is the start. ");

    char *t = "Only the first word.";

    printf("initial: %s\n", s);
    _strncpy(s, t, 4);
    printf("result: %s\n", s);

    printf("initial: %s\n", s);
    _strncat(s, s, 4);
    printf("result: %s\n", s);

    printf("comparison of first 4 chars: %d\n", _strncmp(s, t, 4));

    return 0;
}

/* strncpy: copy first n characters of t to s */
void _strncpy(char *s, char *t, size_t n) {
    char *end = t + n;
    while ((*s++ = *t++) && t <= end)
        ;
}

/* strncat: concatenate first n characters of t to the end of s; s must be big enough */
void _strncat(char *s, char *t, size_t n) {
    while(*s) /* find end of s */
        s++;
    strncpy(s, t, n);
    *(s + n) = '\0';
}

/* strncmp: compare first n characters of t with s */
int _strncmp(char *s, char *t, size_t n) {
    char *end = t + n;
    for (; *s == *t || t > end; s++, t++) {
        if (*s == '\0' || t > end)
            return 0;
    }
    return *s - *t;
}
