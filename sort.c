#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max lines to be sorted */
#define MAXSTORE 5000 /* max lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to the text lines */

int readlines(char *lineptr[], int maxlines, char *linestore);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* example from Ch 5, Sec 5.6, Pg 110 */

/* sort input lines */
int main() {
    int nlines; /* number of input lines read */
    char linestore[MAXSTORE]; /* storage for lines */

    if ((nlines = readlines(lineptr, MAXLINES, linestore)) >= 0) {
        printf("\nsorted:\n\n");
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

void swap(char* lineptr[], int i, int j);

void qsort(char *lineptr[], int left, int right) {
    int i, last;

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than two elements */
    swap(lineptr, left, (left + right)/2); /* move partition elem */
    last = left;                     /* to v[0] */
    for (i = left+1; i <= right; i++) /* partition */
        if (strcmp(lineptr[i], lineptr[left]) < 0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last); /* restore partition elem */
    qsort(lineptr, left, last - 1);
    qsort(lineptr, last + 1, right);
}

/* swap: interchange lineptr[i] and v[j] */
void swap(char* lineptr[], int i, int j) {
    char *temp;
    temp = lineptr[i];
    lineptr[i] = lineptr[j];
    lineptr[j] = temp;
}

#define MAXLEN 1000 /* max length of any input line */

int _getline(char *s, int lim);
char *alloc(int n);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *linestore) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    p = linestore + strlen(linestore); /* first empty position */
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (strlen(linestore) + len) > MAXSTORE)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
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
