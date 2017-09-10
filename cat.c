#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "unistd.h"

void filecopy(int from, int to);

/* cat: concatenate files, version 2 */
int main(int argc, char *argv[]) {
    int fd1;
    char *prog = argv[0]; /* program name for errors */

    if (argc == 1) /* no args; copy standard input */
        filecopy(0, 1);
    else
        while (--argc > 0)
            if ((fd1 = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "%s: can't open %s\n",
                        prog, *argv);
                exit(1);
            } else {
                filecopy(fd1, 1);
                close(fd1);
            }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}

/* filecopy: copy file ifp to file ofp */
void filecopy(int from, int to) {
    int n;
    char buf[BUFSIZ];

    while((n=read(from, buf, BUFSIZ)) > 0 )
        write(to, buf, n);
}
