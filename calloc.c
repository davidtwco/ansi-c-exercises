#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
   Decided to re-use malloc for this because if the implementation of
   malloc and the memory management layer changes, this will be OK.
*/
void *callocx(size_t nmemb, size_t size) {
    void *result = NULL;

    /* use malloc to get the memory */
    result = malloc(nmemb * size);

    /* and clear the memory on successful allocation */
    if (NULL != result)
        memset(result, 0x00, nmemb * size);

    /* and return the result */
    return result;
}

int main(void) {
    int *p = NULL;
    int i = 0;

    p = callocx(100, sizeof *p);

    if(NULL == p)
        printf("mycalloc returned NULL.\n");
    else {

        for(i = 0; i < 100; i++) {
            printf("%08X ", p[i]);
            if(i % 8 == 7)
                printf("\n");
        }

        printf("\n");
        free(p);
    }

    return 0;
}
