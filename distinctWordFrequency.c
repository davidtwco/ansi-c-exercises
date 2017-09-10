#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAXWORD 1000 /* longest word that can be read by getword */

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct wnode {
    int number;
    struct words *words;
    struct wnode *left;
    struct wnode *right;
};

struct words {
    char *word;
    struct words *next;
};

struct tnode *addtree(struct tnode *, char *);
struct wnode *addwtree(struct wnode *, int, char*);
struct words *addword(struct words*, char *);
void printwords(const struct words*, const int);

struct wnode *traverse(const struct tnode *, struct wnode *);
void treeprint(const struct wnode *);
int getword(char *, int);

int main() {
    struct tnode *root;
    struct wnode *wroot;

    char word[MAXWORD];

    /* Get all the words. */
    root = NULL;
    wroot = NULL;

    while(getword(word, MAXWORD) != 'x')
        if(isalpha(word[0]))
            root = addtree(root, word);

    wroot = traverse(root, wroot);
    treeprint(wroot);
    return 0;
}

struct tnode *talloc(void);
struct wnode *numwordalloc(void);
struct words *wordsalloc(void);
char *_strdup(char *);

int getch(void);
void ungetch(int c);

#define IN 1
#define OUT 0

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

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if(p == NULL) { /* new word */
        p = talloc();
        p->word = _strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if(cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

struct wnode *addwtree(struct wnode *p, int count, char* w) {
    if (p == NULL) {
        p = numwordalloc();
        p->number = count;
        p->words = NULL;
        p->words = addword(p->words, w);
    } else if (count > p->number)
        p->left = addwtree(p->left, count, w);
    else
        p->right = addwtree(p->right, count, w);
    return p;
}

struct words *addword(struct words* list, char *w) {
    if (list == NULL) {
        list = wordsalloc();
        list->word = _strdup(w);
        list->next = NULL;
    } else {
        list->next = addword(list->next, w);
    }
    return list;
}

/* treeprint: From K&R2 page 142. Prints tree p in-order. */
void treeprint(const struct wnode *p) {
    if(p != NULL) {
        treeprint(p->left);
        printwords(p->words, p->number);
        treeprint(p->right);
    }
}

void printwords(const struct words* w, const int count) {
    if (w != NULL) {
        printf("%4d\t%s\n", count, w->word);
        w = w->next;
    }
}

struct wnode *traverse(const struct tnode *p, struct wnode *q) {
    if (p != NULL) {
        q = traverse(p->left, q);
        q = addwtree(q, p->count, p->word);
        q = traverse(p->right, q);
    }
    return q;
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct wnode *numwordalloc(void) {
    return (struct wnode *) malloc(sizeof(struct wnode));
}

struct words *wordsalloc(void) {
    return (struct words *) malloc(sizeof(struct words));
}

char *_strdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if(p != NULL)
        strcpy(p, s);
    return p;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch() */
int bufp = 0;       /* next free position in buf */

int getch(void) { /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {  /* push character back on input */
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
    return;
}
