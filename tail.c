#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 /* max lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to the text lines */

int readlines(char *lineptr[], int nlines);

/* example from Ch 5, Sec 5.6, Pg 110 */

/* tail input lines */
int main(int argc, char *argv[]) {
    int nlines, fi, i, cnt; /* number of input lines read */
    int n = 10;
    char *f, c;

    /* We must to walk through the arguments, looking for '-' */
    while(--argc > 0) {
        if((*++argv)[0] == '-') {
            /* Count letters after it */
            cnt = 1;
            while((c = *++argv[0]))
                switch(c) {
                    case 'n':
                        n = atoi(*(argv+cnt++));
                        break;
                    default:
                        ;
                }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        printf("\nlast %d:\n\n", n);
        fi = nlines - n;
        if (fi < 0)
            fi = 0;

        for (i = fi; i < nlines; i++) {
            f = lineptr[i];
            printf("%s\n", f);
        }
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */

int _getline(char *s, int lim);
char *alloc(int n);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

#define ALLOCSIZE 1000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

/* example from Ch 5, Sec 5.4, Pg 101 */

char *alloc(int n) { /* return pointer to n characters */
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else /* not enough room */
        return 0;
}

void afree(char *p) { /* free storage pointed to by p */
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

/* getline:  get line into s, return length */
int _getline(char *s, int lim) {
    int c;
    char *o = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';

    return s - o;
}
