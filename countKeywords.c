#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
    char *word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatite", 0},
    {"while", 0}
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main() {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                   keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int getch(void);
void ungetch(int);

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c;
    char *w = word;
    static int line_beg = 1; /* 1 at beginning of a new line */
    static int after_slash = 0; /* 1 after '\' */
    int after_star = 0; /* 1 after '*' */

    if(isspace(c = getch()))
        after_slash = 0;
    while(isspace(c)) {
        if(c == '\n')
            line_beg = 1;
        c = getch();
    }

    if(c != EOF)
        *w++ = c;

    if(c == '#' && line_beg == 1) { /* Preprocessor directive */
        while((c = getch()) != '\n' && c != EOF) /* Go to end of line */
            ;
        return getword(word, lim); /* Start over */
    }
    line_beg = 0;

    if(c == '\\') /* Set after_slash flag */
        after_slash = after_slash ? 0 : 1; /* Ignore '\\' comment */

    else if(c == '/' ) {
        if((c = getch()) == '*' && !after_slash) { /* Begin comment */
            while((c = getch()) != EOF) {
                if(c == '/') {
                    if(after_star) /* End comment */
                        return getword(word, lim); /* Start over */
                }
                else if(c == '*' && !after_slash)
                    after_star = 1;
                else if(c == '\\')
                    after_slash = after_slash ? 0 : 1; /* Ignore '\\' comments */
                else {
                    after_star = 0;
                    after_slash = 0;
                }
            }
        } /* End comment */

        after_slash = 0; /* Not after slash anymore */
        if(c != EOF)
            ungetch(c);
    }

    else if(c == '\"') {
        if(!after_slash) { /* String literal */
            --w; /* Reset w */
            while((c = getch()) != EOF) {
                if(c == '\"' && !after_slash)
                    break;
                else if(c == '\\')
                    after_slash = after_slash ? 0 : 1; /* Ignore '\\' comments */
                else
                    after_slash = 0;
                *w++ = c;
            }
            *w = '\0';
            if(c == EOF)
                return EOF;
            else
                return getword(word, lim); /* Start over. */
        }
        after_slash = 0; /* Not after a slash anymore. */
    }

    if(!isalpha(c) && c != '_') { /* It's a symbol. */
        *w = '\0';
        if(c != '\\')
            after_slash = 0;
        return c;
    }

    /* Reset this flag since a slash would have just returned. */
    after_slash = 0;

    for( ; --lim > 0; ++w) /* It's a word or letter. */
        if(!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];

}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) { /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
