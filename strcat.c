#include <stdio.h>
#include <string.h>

void _strcat(char s[], char t[]);

int main() {
    char buf[1000];
    char *s = "Knock knock. ";
    char *t = "Who's there? ";
    char *u = "Jim.";
    strcpy(buf, s);

    printf("initial value:\n\t%s\n", buf);
    _strcat(buf, t);
    printf("result of adding \"%s\":\n\t%s\n", t, buf);
    _strcat(buf, u);
    printf("result of adding \"%s\":\n\t%s\n", u, buf);

    return 0;
}

/* strcat: concatenate t to the end of s; s must be big enough */
void _strcat(char *s, char *t) {

    while(*s) /* find end of s */
        s++;
    strcpy(s, t);
}
