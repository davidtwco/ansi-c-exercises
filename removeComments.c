#include <stdio.h>

#define STATE_NO_COMMENT 0
#define STATE_INLINE_COMMENT 1
#define STATE_LINE_COMMENT 2
#define STATE_DETERMINING_COMMENT 3

#define STATE_NO_QUOTES 0
#define STATE_DOUBLE_QUOTES 1
#define STATE_SINGLE_QUOTES 2
#define STATE_DETERMINING_QUOTES 3

/* Print C program input without comments. */
main() {
    int sComment, sQuotes;
    int currentCharacter, previousCharacter, previousPreviousCharacter;

    sComment = STATE_NO_COMMENT;
    sQuotes = STATE_NO_QUOTES;

    while ((currentCharacter = getchar()) != EOF) {
        if (currentCharacter == '\n') {
            // We stop line comments when we hit newlines.
            if (sComment == STATE_LINE_COMMENT)
                sComment = STATE_NO_COMMENT;

            // Print the newline.
            putchar(currentCharacter);
            continue;
        }

        // Don't deal with any quotes if we are in a comment.
        if (sComment == STATE_NO_COMMENT) {
            // Only deal with a quote if it isn't preceeded by a backslash (ie. it isn't
            // being escaped.
            // However, do deal with the quote if that backslash was preceeded by a backslash (ie.
            // the backslash was the character being escaped).
            if (previousCharacter != '\\' || (previousCharacter == '\\' && previousPreviousCharacter == '\\')) {
                // We deal with single and double quotes separately, to
                // ensure that we can't exit a quote state started by a
                // double quote with a single quote.
                if (currentCharacter == '"') {

                    if (sQuotes == STATE_DOUBLE_QUOTES) {
                        sQuotes = STATE_NO_QUOTES;
                    } else if (sQuotes == STATE_NO_QUOTES) {
                        sQuotes = STATE_DOUBLE_QUOTES;
                    }

                } else if (currentCharacter == '\'') {

                    if (sQuotes == STATE_SINGLE_QUOTES) {
                        sQuotes = STATE_NO_QUOTES;
                    } else if (sQuotes == STATE_NO_QUOTES) {
                        sQuotes = STATE_SINGLE_QUOTES;
                    }

                }
            }
        }

        // Only deal with comments if the previous character was a slash
        // and we're not in quotes.
        if (previousCharacter == '/' && sQuotes == STATE_NO_QUOTES) {
            // If we have two slashes, start a line comment.
            if (currentCharacter == '/') {
                sComment = STATE_LINE_COMMENT;

            // If we have a slash and a star, start a inline comment.
            // We do support these extending over multiple lines.
            } else if (currentCharacter == '*') {
                sComment = STATE_INLINE_COMMENT;

            // If we saw a single slash but it didn't end up
            // as a comment, print it now since we didn't earlier.
            } else if (sComment == STATE_DETERMINING_COMMENT) {
                sComment = STATE_NO_COMMENT;
                putchar('/');
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
        if (currentCharacter == '/' &&
                sComment == STATE_NO_COMMENT &&
                sQuotes == STATE_NO_QUOTES) {
            sComment = STATE_DETERMINING_COMMENT;
        }

        // If the previous character was a star and the current is a slash
        // and we're in a inline comment and no quotes, end the inline comment.
        if (previousCharacter == '*' && currentCharacter == '/'
                && sComment == STATE_INLINE_COMMENT && sQuotes == STATE_NO_QUOTES) {
            sComment = STATE_NO_COMMENT;
            continue;
        }

        // Print all non-comment characters.
        if (sComment == STATE_NO_COMMENT)
            putchar(currentCharacter);

        previousPreviousCharacter = previousCharacter;
        previousCharacter = currentCharacter;
    }

    // Some strings with comments inside them for testing.
    char *t1 = " // this is an example of a comment within a string \" ";
    char *t2 = " /* this is an example of a comment ' within a string */ ";
    char *t3 = " /* this is an \" \' example of a comment in string with no end";
    // This is a comment with a string inside it. "partially quoted text

    return 0;
}
