#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[]) {
    char* prog = argv[0];
    FILE *fp1, *fp2;
    unsigned long line;
    char *fn1, *fn2;
    char *fr1, *fr2;
    char line1[MAXLINE], line2[MAXLINE];

    if (argc != 3) {
        fprintf(stderr, "%s: must provide two files as inputs\n", prog);
        exit(1);
    }

    fn1 = *++argv;
    if ((fp1 = fopen(fn1, "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", prog, fn1);
        exit(2);
    }

    fn2 = *++argv;
    if ((fp2 = fopen(fn2, "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", prog, fn2);
        exit(2);
    }

    line = 1;
    for (;; line++) {
        fr1 = fgets(line1, MAXLINE, fp1);
        fr2 = fgets(line2, MAXLINE, fp2);


        if (fr1 == NULL || fr2 == NULL)
            break;
        if (strcmp(line1, line2) != 0)
            break;
    }

    /* If they both ended with NULL then they finished at the same time. */
    if (fr1 == NULL && fr2 == NULL) {
        printf("files match\n");
        exit(0);
    }

    if (fr1 == NULL || fr2 == NULL) {
        printf("file %s ended before file %s\n",
               (fr1 == NULL) ? fn1 : fn2,
               (fr1 == NULL) ? fn2 : fn1);
    } else {
        /* If anything else caused the loop to end, then there was a mismatch. */
        printf("mismatch on line %ld:\n%s:\n%s\n%s:\n%s\n",
               line, fn1, line1, fn2, line2);
    }

    exit(3);
}
