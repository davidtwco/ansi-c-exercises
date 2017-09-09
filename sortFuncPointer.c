#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 /* max lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to the text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right,
           int (*comp)(void*, void*));
int numcmp(const char *s1, const char *s2);

/* example from Ch 5, Sec 5.11, Pg 119 */

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        printf("\nsorted:\n\n");
        _qsort((void **) lineptr, 0, nlines - 1,
               (int (*)(void*,void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int numcmp(const char *s1, const char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void* lineptr[], int i, int j);

void _qsort(void *lineptr[], int left, int right,
           int (*comp)(void*, void*)) {
    int i, last;

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than two elements */
    swap(lineptr, left, (left + right)/2); /* move partition elem */
    last = left;                     /* to v[0] */
    for (i = left+1; i <= right; i++) /* partition */
        if ((*comp)(lineptr[i], lineptr[left]) < 0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last); /* restore partition elem */
    _qsort(lineptr, left, last - 1, comp);
    _qsort(lineptr, last + 1, right, comp);
}

/* swap: interchange lineptr[i] and v[j] */
void swap(void* lineptr[], int i, int j) {
    void *temp;
    temp = lineptr[i];
    lineptr[i] = lineptr[j];
    lineptr[j] = temp;
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
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
