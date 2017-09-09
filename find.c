#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int _getline(char *line, int max);

/* example from Ch 5, Sec 5.10, Pg 116 */

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int found = 0;

    if (argc != 2)
        printf("Usage: find pattern\n");
    else
        while(_getline(line, MAXLINE) > 0)
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
    return found;
}

/* getline:  get line into s, return length */
int _getline(char *s, int lim)
{
    int c;
    char *o = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';

    return s - o;
}
