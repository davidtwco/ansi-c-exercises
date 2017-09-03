#include <stdio.h>

#define FOLD_COLUMN 60
#define BREAK_WORD_AFTER 63
#define TAB_SIZE 8

main() {
    int c, col;

    col = 0;
    while ((c = getchar()) != EOF) {
        if (col < FOLD_COLUMN) {
            putchar(c);

            if (c == '\t')
                col += TAB_SIZE;
            else
                ++col;

            continue;
        }

        if (col >= BREAK_WORD_AFTER) {
            putchar('-');
            putchar('\n');

            if (c != ' ') {
                putchar(c);
                col = 1;
            } else {
                col = 0;
            }

            continue;
        }

        if (c == ' ') {
            putchar('\n');
            col = 0;
            continue;
        }

        putchar(c);
        ++col;
    }
}
