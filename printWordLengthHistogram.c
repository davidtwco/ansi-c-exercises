#include <stdio.h>

#define MAX_WORD_LENGTH 15
#define MAX_HISTOGRAM_WIDTH 12
#define IN 1
#define OUT 0

main() {
    int c, i, j;
    int numChars, numOverflowing, normalizedLength, state;
    float maxLength;
    int wordLengths[MAX_WORD_LENGTH];

    for (i = 0; i < MAX_WORD_LENGTH; ++i)
        wordLengths[i] = 0;

    state = OUT;
    numOverflowing = numChars = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            state = OUT;

            if (numChars > MAX_WORD_LENGTH)
                ++numOverflowing;
            else if (numChars > 0)
                ++wordLengths[numChars];
        } else if (state == OUT) {
            state = IN;
            numChars = 1;
        } else
            ++numChars;
    }

    maxLength = 0;
    for (i = 0; i < MAX_WORD_LENGTH; ++i)
        if (wordLengths[i] > maxLength)
            maxLength = wordLengths[i];

    printf("overflowing words: %d", numOverflowing);
    if (maxLength == 0) {
        printf("no non-overflowing words");
        return 0;
    }

    for (i = 0; i < MAX_WORD_LENGTH; ++i) {
        printf("\n%3d: ", i);

        normalizedLength = (wordLengths[i] / maxLength) * MAX_HISTOGRAM_WIDTH;

        for (j = 0; j < normalizedLength; ++j)
            printf("*");
    }

}
