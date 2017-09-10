#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define DEFAULTCOMPARISON 6
#define PRINTPREVIOUS_YES 1
#define PRINTPREVIOUS_NO 0
#define PRINTPREVIOUS_NEWGROUP 2

struct tnode { /* the tree node */
    char *word; /* points to the test */
    int count; /* number of occurences */
    struct tnode *left; /* left child */
    struct tnode *right; /* right child */
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *, int);
int getword(char *, int);

/* example from Ch 6, Sec 6.6, Pg 143 */

/* word frequency count */
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int numCharactersMatch;

    /* Get the number of characters we should
     * compare at the start of words. */
    if(argc == 1)
        numCharactersMatch = DEFAULTCOMPARISON;
    else if(argc == 2)
        numCharactersMatch = atoi(argv[1]);
    else {
        printf("Incorrect number of arguments.\n");
        return 1;
    }

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root, numCharactersMatch);
    return 0;
}

struct tnode *talloc(void);
char *_strdup(char *);

/* addtree: add a new with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) { /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = _strdup(w);
        p->count = 1;
        p-> left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++; /* repeated word */
    else if (cond < 0) /* less than the left subtree */
        p->left = addtree(p->left, w);
    else /* greater than the right subtree */
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p, int n) {
    static int printPrevious = 1;
    static struct tnode *previous;

    if (p != NULL) {
        treeprint(p->left, n);

        /* n is how many characters we should compare, if it is
         * 0 then we just print all of them */
        if (n == 0)
            /* Print all the words. */
            printf("%4d %s\n", p->count, p->word);
        else {
            if (previous != NULL) {
                if (strncmp(previous->word, p->word, n) == 0) {
                    if (printPrevious == PRINTPREVIOUS_NEWGROUP) {
                        /* If we find a new group, add an extra newline to separate the
                         * groups in the output */
                        printf("\n%4d %s\n", previous->count, previous->word);
                        printPrevious = PRINTPREVIOUS_NO;
                    } else if (printPrevious == PRINTPREVIOUS_YES) {
                        /* If we find another word in the current group, just add a single
                         * newline. */
                        printf("%4d %s\n", previous->count, previous->word);
                        printPrevious = PRINTPREVIOUS_NO;
                    }
                    /* We do not print the current word by default as if it doesn't have the same
                     * root as the next value then that would be a mistake. Hence why we need
                     * printPrevious. */
                    printf("%4d %s\n", p->count, p->word);
                } else
                    printPrevious = PRINTPREVIOUS_NEWGROUP;
            }
            /* Keep track of previous word. */
            previous = p;
        }

        treeprint(p->right, n);
    }
}


/* talloc: make a tnode */
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *_strdup(char *s) { /* make a duplicate of s */
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int getch(void);
void ungetch(int);

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c;
    char *w = word;
    static int lineBeginning = 1; /* 1 at beginning of a new line */
    static int afterSlash = 0; /* 1 after '\' */
    int afterStar = 0; /* 1 after '*' */

    if(isspace(c = getch()))
        afterSlash = 0;
    while(isspace(c)) {
        if(c == '\n')
            lineBeginning = 1;
        c = getch();
    }

    if(c != EOF)
        *w++ = c;

    if(c == '#' && lineBeginning == 1) { /* Preprocessor directive */
        while((c = getch()) != '\n' && c != EOF) /* Go to end of line */
            ;
        return getword(word, lim); /* Start over */
    }
    lineBeginning = 0;

    if(c == '\\') /* Set afterSlash flag */
        afterSlash = afterSlash ? 0 : 1; /* Ignore '\\' comment */

    else if(c == '/' ) {
        if((c = getch()) == '*' && !afterSlash) { /* Begin comment */
            while((c = getch()) != EOF) {
                if(c == '/') {
                    if(afterStar) /* End comment */
                        return getword(word, lim); /* Start over */
                }
                else if(c == '*' && !afterSlash)
                    afterStar = 1;
                else if(c == '\\')
                    afterSlash = afterSlash ? 0 : 1; /* Ignore '\\' comments */
                else {
                    afterStar = 0;
                    afterSlash = 0;
                }
            }
        } /* End comment */

        afterSlash = 0; /* Not after slash anymore */
        if(c != EOF)
            ungetch(c);
    }

    else if(c == '\"') {
        if(!afterSlash) { /* String literal */
            --w; /* Reset w */
            while((c = getch()) != EOF) {
                if(c == '\"' && !afterSlash)
                    break;
                else if(c == '\\')
                    afterSlash = afterSlash ? 0 : 1; /* Ignore '\\' comments */
                else
                    afterSlash = 0;
                *w++ = c;
            }
            *w = '\0';
            if(c == EOF)
                return EOF;
            else
                return getword(word, lim); /* Start over. */
        }
        afterSlash = 0; /* Not after a slash anymore. */
    }

    if(!isalpha(c) && c != '_') { /* It's a symbol. */
        *w = '\0';
        if(c != '\\')
            afterSlash = 0;
        return c;
    }

    /* Reset this flag since a slash would have just returned. */
    afterSlash = 0;

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
