#include <stdio.h>

#define MAX_HISTOGRAM_WIDTH 12
#define MIN 33
#define LENGTH 95

main() {
    int c, i, j;
    int numOverflowing, normalizedLength;
    float maxLength;
    int characterFrequencies[LENGTH];

    for (i = 0; i < LENGTH; ++i)
        characterFrequencies[i] = 0;

    numOverflowing = 0;
    while ((c = getchar()) != EOF) {
        if (c >= 33 && c <= MIN + LENGTH)
            ++characterFrequencies[c - MIN];
        else
            numOverflowing = 0;
    }

    maxLength = 0;
    for (i = 0; i < LENGTH; ++i)
        if (characterFrequencies[i] > maxLength)
            maxLength = characterFrequencies[i];

    printf("overflowing: %d", numOverflowing);
    if (maxLength == 0) {
        printf("no non-overflowing characters");
        return 0;
    }

    for (i = 0; i < LENGTH; ++i) {
        printf("\n%2c: ", i + MIN);

        normalizedLength = (characterFrequencies[i] / maxLength) * MAX_HISTOGRAM_WIDTH;

        for (j = 0; j < normalizedLength; j++)
            printf("*");
    }
}
