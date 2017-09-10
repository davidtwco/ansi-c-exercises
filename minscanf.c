#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...);

int main() {
    char *fmt = "%d";
    int i;

    minscanf(fmt, &i); /* scan integer from stdin */
    printf("scanned: %d\n", i); /* print scanning results to stdout */

    return 0;
}

/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...) {
    va_list ap; /* points to each unnamed arg in turn */
    char *p;
    int *ival;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */

    for (p = fmt; *p; p++) {
        /* Skip chars that aren't format conversions. */
        if (*p != '%')
            continue;

        switch(*++p) {
            case 'd':
                ival = va_arg(ap, int *); /* get integer pointer from args */
                scanf("%d", ival); /* read integer into int pointer */
                break;
            default:
                break;
        }
    }
    va_end(ap);
}
