#include <stdio.h>

/* This program makes use of a lot of the code from the
 * removeComments.c (Ex1-23) program. */

#define MAX_DEPTH 1000

#define STATE_NO_COMMENT 0
#define STATE_INLINE_COMMENT 1
#define STATE_LINE_COMMENT 2
#define STATE_DETERMINING_COMMENT 3

#define STATE_NO_QUOTES 0
#define STATE_DOUBLE_QUOTES 1
#define STATE_SINGLE_QUOTES 2
#define STATE_DETERMINING_QUOTES 3

int checkStack(int c, char a, char b);

char stack[MAX_DEPTH];
int i, col, line;
int sComment, sQuotes;

/* Check C program for mismatched parentheses, brackets and braces. */
main() {
    extern char stack[];
    extern int i, col, line;
    extern int sComment, sQuotes;
    int c, pc, ppc;

    sComment = STATE_NO_COMMENT;
    sQuotes = STATE_NO_QUOTES;

    i = 0;
    col = 0;
    line = 1;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            // We stop line comments when we hit newlines.
            if (sComment == STATE_LINE_COMMENT)
                sComment = STATE_NO_COMMENT;

            // Keep track of line and column numbers for output.
            ++line;
            col = 0;
        }
        ++col;

        // Don't deal with any quotes if we are in a comment.
        if (sComment == STATE_NO_COMMENT) {
            // Only deal with a quote if it isn't preceeded by a backslash (ie. it isn't
            // being escaped.
            // However, do deal with the quote if that backslash was preceeded by a backslash (ie.
            // the backslash was the character being escaped).
            if (pc != '\\' || (pc == '\\' && ppc == '\\')) {
                // We deal with single and double quotes separately, to
                // ensure that we can't exit a quote state started by a
                // double quote with a single quote.
                if (c == '"') {

                    if (sQuotes == STATE_DOUBLE_QUOTES) {
                        sQuotes = STATE_NO_QUOTES;

                        // Check if the top of the stack matches
                        // a double quote.
                        if (checkStack(c, '"', '"') == 1)
                            return 1;
                    } else if (sQuotes == STATE_NO_QUOTES) {
                        sQuotes = STATE_DOUBLE_QUOTES;
                        // Add double quote to the stack.
                        stack[++i] = '"';
                    }

                } else if (c == '\'') {

                    if (sQuotes == STATE_SINGLE_QUOTES) {
                        sQuotes = STATE_NO_QUOTES;

                        // Check if the top of the stack matches
                        // a single quote.
                        if (checkStack(c, '\'', '\'') == 1)
                            return 1;
                    } else if (sQuotes == STATE_NO_QUOTES) {
                        sQuotes = STATE_SINGLE_QUOTES;
                        // Add single quote to the stack.
                        stack[++i] = '\'';
                    }

                }
            }
        }

        // Only deal with comments if the previous character was a slash
        // and we're not in quotes.
        if (pc == '/' && sQuotes == STATE_NO_QUOTES) {
            // If we have two slashes, start a line comment.
            if (c == '/') {
                sComment = STATE_LINE_COMMENT;

            // If we have a slash and a star, start a inline comment.
            // We do support these extending over multiple lines.
            } else if (c == '*') {
                sComment = STATE_INLINE_COMMENT;

                // When we start a inline comment, add it to our stack
                // so we can check it later.
                stack[++i] = 'c';
                printf("Push comment. Line %d, col %d.\n", line, col);

            // If we saw a single slash but it didn't end up
            // as a comment, print it now since we didn't earlier.
            } else if (sComment == STATE_DETERMINING_COMMENT) {
                sComment = STATE_NO_COMMENT;
            }
        }

        // If we find a slash and we're not already in a comment or
        // in quotes then ensure that we don't print it until we
        // determine if it is or is not a comment.
        //
        // It is impossible to get into a situation where we get
        // stuck in this determining state.
        // This also wouldn't cause issues when we find the end of
        // a inline comment as we would not be in the NO_COMMENT
        // state.
        if (c == '/' && sComment == STATE_NO_COMMENT && sQuotes == STATE_NO_QUOTES) {
            sComment = STATE_DETERMINING_COMMENT;
        }

        // If the previous character was a star and the current is a slash
        // and we're in a inline comment and no quotes, end the inline comment.
        if (pc == '*' && c == '/' &&
                sComment == STATE_INLINE_COMMENT && sQuotes == STATE_NO_QUOTES) {

            // Check that the top item in our stack is a comment as we leave an
            // inline comment.
            if (stack[i] == 'c') {
                printf("Pop comment. Line %d, col %d.\n", line, col);
                --i;
            }
            else {
                printf("ERR: expected end of comment, found %c. Line %d, col %d. \n",
                        stack[i], line, col);
                return 1;
            }

            sComment = STATE_NO_COMMENT;
            continue;
        }

        // Only deal with normal pairs of symbols when we are not in comments or quotes.
        if (sQuotes == STATE_NO_QUOTES && sComment == STATE_NO_COMMENT) {
            // If we find opening symbols then we add them to the top of our stack.
            if (c == '(' || c == '{' || c == '[' || c == '<') {
                stack[++i] = c;
                printf("Push %c. Line %d, col %d.\n", c, line, col);
            }

            // Use our helper function to check if the top of the stack
            // has the corresponding bracket to the current character (if
            // we're on that a end of pair character).
            if (checkStack(c, '(', ')') == 1)
                return 1;

            if (checkStack(c, '{', '}') == 1)
                return 1;

            if (checkStack(c, '[', ']') == 1)
                return 1;

            if (checkStack(c, '<', '>') == 1)
                return 1;
        }

        ppc = pc;
        pc = c;
    }

    printf("Program is valid.\n");
    return 0;
}

int checkStack(int c, char a, char b) {
    extern char stack[];
    extern int i, col, line;

    // If current character is a 'end of pair' character, ie. ')'.
    if (c == b) {
        // Check that the stack has a matching 'start of pair' character
        // for our character, ie. '('
        if (stack[i] == a) {
            printf("Pop %c. Line %d, col %d.\n", b, line, col);
            // Decrement our stack.
            --i;
        }
        else {
            printf("ERR: expected %c, found %c. Line %d, col %d. \n",
                    b, stack[i], line, col);
            return 1;
        }
    }
    return 0;
}
