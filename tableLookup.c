#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist { /* table entry */
    struct nlist *next; /* next entry in chain */
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
int undef(char * name);

int main() {
}

unsigned hash(char *s);
char *_strdup(char *s);

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = _strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /* free previous defn */
    if ((np->defn = _strdup(defn)) == NULL)
        return NULL;
    return np;
}

int undef(char * name) {
    struct nlist * np1, * np2;

    /* If we don't find an existing record then there is
     * nothing to remove. */
    if ((np1 = lookup(name)) == NULL)
        return 1;

    /* Walk along the list, keeping track of the previous
     * record we had. */
    for (np1 = np2 = hashtab[hash(name)]; np1 != NULL;
         np2 = np1, np1 = np1->next ) {
        /* We found the record to remove */
        if (strcmp(name, np1->name) == 0) {

            /*  Remove node from list  */
            if (np1 == np2)
                /* If there was no previous record, ie. we're
                 * at the root of the table, then set the table
                 * pointer to np1's next. */
                hashtab[hash(name)] = np1->next;
            else
                /* Replace the previous node's next pointer
                 * (that was pointing at np1) to the record
                 * that np1's next pointer is pointing at. */
                np2->next = np1->next;

            /* Free up memory. */
            free(np1->name);
            free(np1->defn);
            free(np1);

            return 0;
        }
    }

    return 1; /* Name not found. */
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; /* found */
    return NULL; /* not found */
}

char *_strdup(char *s) { /* make a duplicate of s */
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
