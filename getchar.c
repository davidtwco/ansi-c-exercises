#include <stdio.h>
#include "unistd.h"

/* example from Ch 8, Sec 8.2, Pg 171 */

/* getchar: unbuffered single character input */
int getchar(void) {
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}
