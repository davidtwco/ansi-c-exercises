#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main() {
    char *fmt = "%d %i %c %u %o %x %X %e %f %g %s other\n";
    minprintf(fmt, 10, 12, 'a', 19, 12, 14, 15, 5.4, 4.5, 6.4, "alphabet");
    return 0;
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
    va_list ap; /* points to each unnamed argument in turn */
    char *p, *sval;
    int ival;
    double dval;
    unsigned uval;

    va_start(ap, fmt); /* make ap point to first unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch (*++p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'c':
                ival = va_arg(ap, int);
                putchar(ival);
                break;
            case 'u':
                uval = va_arg(ap, unsigned int);
                printf("%u", uval);
                break;
            case 'o':
                uval = va_arg(ap, unsigned int);
                printf("%o", uval);
                break;
            case 'x':
                uval = va_arg(ap, unsigned int);
                printf("%x", uval);
                break;
            case 'X':
                uval = va_arg(ap, unsigned int);
                printf("%X", uval);
                break;
            case 'e':
                dval = va_arg(ap, double);
                printf("%e", dval);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 'g':
                dval = va_arg(ap, double);
                printf("%g", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); /* clean up when done */
}
