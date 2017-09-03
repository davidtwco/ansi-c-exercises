#include <stdio.h>

#define MAX_SIZE 1000

void expand(char s1[], char s2[]);
int both_in_bounds(int c, int d, int u, int l);
int in_bounds(int c, int u, int l);

int main() {
    char test1[] = "a-z A-Z 0-9";
    char output1[MAX_SIZE];

    expand(test1, output1);
    printf("%s expanded to %s\n\n", test1, output1);

    char test2[] = "a-zA-Z0-9";
    char output2[MAX_SIZE];

    expand(test2, output2);
    printf("%s expanded to %s\n\n", test2, output2);

    char test3[] = "-a-z a-b-c";
    char output3[MAX_SIZE];

    expand(test3, output3);
    printf("%s expanded to %s\n\n", test3, output3);

    char test4[] = "9-0";
    char output4[MAX_SIZE];

    expand(test4, output4);
    printf("%s expanded to %s\n\n", test4, output4);

    return 0;
}

void expand(char s1[], char s2[]) {
    int i, j, k, diff;
    int c, pc, ppc;

    for (i = 2, j = 0; (ppc = s1[i-2]) != '\0' && (pc = s1[i-1]) != '\0' && (c = s1[i]) != '\0';) {

        if (pc == '-' && (diff = (c - ppc)) > 1) {
            if (both_in_bounds(c, ppc, 'a', 'z')) {
                for (k = 'a'; k <= 'z'; k++)
                    s2[j++] = k;
                i += 3;
            }

            if (both_in_bounds(c, ppc, 'A', 'Z')) {
                for (k = 'A'; k <= 'Z'; k++)
                    s2[j++] = k;
                i += 3;
            }

            if (both_in_bounds(c, ppc, '0', '9')) {
                for (k = '0'; k <= '9'; k++)
                    s2[j++] = k;
                i += 3;
            }
        } else {
            s2[j++] = ppc;
            ++i;
        }
    }

    s2[j++] = ppc;
    s2[j++] = pc;
    s2[j] = '\0';

}

int both_in_bounds(int c, int d, int l, int u) {
    return in_bounds(c, l, u) && in_bounds(d, l, u);
}

int in_bounds(int c, int l, int u) {
    return (c >= l && c <= u);
}
