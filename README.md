# ansi-c-exercises
This repository contains my solutions to the exercises from The C Programming Language by Brian Kernighan and Dennis Ritchie.

All files will either be from a commit that lists the exercise or will contain a comment detailing where the example was copied from. Some solutions are inspired by those found online, especially in the later chapters.

## Chapter 1 - A Tutorial Introduction
- [x] **Ex 1-1 (Pg 8)** - Run the "hello world" program on your system. Experiment with leaving out parts of the program, to see what error messages you get.
- [x] **Ex 1-2 (Pg 8)** - Experiment to find out what happens when `printf`'s argument string contains `\c`, where c is some character not listed above.
- [x] **Ex 1-3 (Pg 13)** - Modify the temperature conversion program to print a heading above the table. - [Solution](fahrenheitCelsius.c)
- [x] **Ex 1-4 (Pg 13)** - Write a program to print the corresponding Celsius to Fahrenheit table. - [Solution](celsiusFahrenheit.c)
- [x] **Ex 1-5 (Pg 14)** - Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0. - [Solution](fahrenheitCelsiusForLoop.c)
- [x] **Ex 1-6 (Pg 17)** - Verify that the expression `getchar() != EOF` is 0 or 1.
- [x] **Ex 1-7 (Pg 17)** - Write a program to print the value of `EOF`. - [Solution](printEOF.c)
- [x] **Ex 1-8 (Pg 20)** - Write a program to count blanks, tabs, and newlines. - [Solution](countBlanksTabsNewlines.c)
- [x] **Ex 1-9 (Pg 20)** - Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank. - [Solution](copyInputToOutputReplacingBlanks.c)
- [x] **Ex 1-10 (Pg 20)** - Write a program to copy its input to its output, replacing each tab by `\t` , each backspace by `\b` , and each backslash by `\\`. This makes tabs and backspaces visible in an unambiguous way. - [Solution](copyInputToOutputReplacingEscapeCharacters.c)
- [x] **Ex 1-11 (Pg 21)** - How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any?
- [x] **Ex 1-12 (Pg 21)** - Write a program that prints its input one word per line. - [Solution](printOneWordOfInputPerLine.c)
- [x] **Ex 1-13 (Pg 24)** - Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging. - [Solution](printWordLengthHistogram.c)
- [x] **Ex 1-14 (Pg 24)** - Write a program to print a histogram of the frequencies of different characters in its input. - [Solution](printCharacterFrequencyHistogram.c)
- [x] **Ex 1-15 (Pg 27)** - Rewrite the temperature conversion program of Section 1.2 to use a function for conversion. - [Solution](temperatureConversionFunction.c)
- [x] **Ex 1-16 (Pg 30)** - Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lines, and as much as possible of the text. - [Solution](printLongestLine.c)
- [x] **Ex 1-17 (Pg 31)** - Write a program to print all input lines that are longer than 80 characters. - [Solution](printLinesLongerThan80Chars.c)
- [x] **Ex 1-18 (Pg 31)** - Write a program to remove all trailing blanks and tabs from each line of input, and to delete entirely blank lines. - [Solution](removeTrailingWhitespaceFromInput.c)
- [x] **Ex 1-19 (Pg 31)** - Write a function `reverse(s)` that reverses the character string `s`. Use it to write a program that reverses its input a line at a time. - [Solution](reverseLines.c)
- [x] **Ex 1-20 (Pg 34)** - Write a program `detab` that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every `n` columns. Should n be a variable or a symbolic parameter? - [Solution](detab.c)
- [x] **Ex 1-21 (Pg 34)** - Write a program `entab` that replaces strings of blanks with the minimum number of tabs and blanks to achieve the same spacing. Use the same stops as for `detab` . When either a tab or a single blank would suffice to reach a tab stop, which should be given preference? - [Solution](entab.c)
- [x] **Ex 1-22 (Pg 34)** - Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column. - [Solution](fold.c)
- [x] **Ex 1-23 (Pg 34)** - Write a program to remove all comments from a C program. Don't forget to handle quoted strings and character constants properly. C comments do not nest. - [Solution](removeComments.c)
- [x] **Ex 1-24 (Pg 34)** - Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets and braces. Don't forget about quotes, both single and double, escape sequences, and comments. (This program is hard if you do it in full generality.) - [Solution](checkUnbalancedParenthesesBracketsBraces.c)

## Chapter 2 - Types, Operators and Expressions
- [x] **Ex 2-1 (Pg 36)** - Write a program to determine the ranges of `char`, `short`, `int`, and `long` variables, both `signed` and `unsigned`, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point types. - [Solution](typeRanges.c)
- [x] **Ex 2-2 (Pg 42)** - Write a loop equivalent to the for loop above without using `&&` or `||`. - [Solution](loopEquivalentNoAndOr.c)
- [x] **Ex 2-3 (Pg 46)** - Write the function `htoi(s)`, which converts a string of hexadecimal digits (including an optional `0x` or `0X`) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F. - [Solution](htoi.c)
- [x] **Ex 2-4 (Pg 48)** - Write an alternate version of `squeeze(s1,s2)` that deletes each character in the string `s1` that matches any character in the string `s2` . - [Solution](squeezeDelete.c)
- [x] **Ex 2-5 (Pg 48)** - Write the function `any(s1,s2)`, which returns the first location in the string `s1` where any character from the string `s2` occurs, or -1 if `s1` contains no characters from `s2`. (The standard library function `strpbrk` does the same job but returns a pointer to the location.) - [Solution](any.c)
- [x] **Ex 2-6 (Pg 49)** - Write a function `setbits(x,p,n,y)` that returns `x` with the `n` bits that begin at position `p` set to the rightmost `n` bits of `y`, leaving the other bits unchanged. - [Solution](setbits.c)
- [x] **Ex 2-7 (Pg 49)** - Write a function `invert(x,p,n)` that returns `x` with the `n` bits that begin at position `p` inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. - [Solution](invert.c)
- [x] **Ex 2-8 (Pg 49)** - Write a function `rightrot(x,n)` that returns the value of the integer `x` rotated to the right by `n` bit positions. - [Solution](rightrot.c)
- [x] **Ex 2-9 (Pg 51)** - In a two's complement number system, `x &= (x-1)` deletes the rightmost 1-bit in `x`. Explain why. Use this observation to write a faster version of `bitcount`. - [Solution](fasterBitcount.c)
- [x] **Ex 2-10 (Pg 52)** - Rewrite the function `lower`, which converts upper case letters to lower case, with a conditional expression instead of if-else. - [Solution](lower.c)

## Chapter 3 - Control Flow
- [x] **Ex 3-1 (Pg 58)** - Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside). Write a version with only one test inside the loop and measure the difference in run-time. - [Solution](binarysearch.c)
- [x] **Ex 3-2 (Pg 60)** - Write a function `escape(s,t)` that converts characters like newline and tab into visible escape sequences like `\n` and `\t` as it copies the string `t` to `s`. Use a `switch`. Write a function for the other direction as well, converting escape sequences into the real characters. - [Solution](escape.c)
- [x] **Ex 3-3 (Pg 63)** - Write a function `expand(s1,s2)` that expands shorthand notations like `a-z` in the string `s1` into the equivalent complete list `abc...xyz` in `s2` . Allow for letters of either case and digits, and be prepared to handle cases like `a-b-c` and `a-z0-9` and `-a-z`. Arrange that a leading or trailing - is taken literally. - [Solution](expand.c)
- [x] **Ex 3-4 (Pg 64)** - In a two's complement number representation, our version of `itoa` does not handle the largest negative number, that is, the value of `n` equal to `-(2 to the power (wordsize - 1))`. Explain why not. Modify it to print that value correctly regardless of the machine on which it runs. - [Solution](itoa.c)
- [x] **Ex 3-5 (Pg 64)** - Write the function `itob(n,s,b)` that converts the integer `n` into a base `b` character representation in the string `s`. In particular, `itob(n,s,16)` formats `n` as a hexadecimal integer in `s`. - [Solution](itob.c)
- [x] **Ex 3-6 (Pg 64)** - Write a version of `itoa` that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough. - [Solution](itoaFieldWidth.c)

## Chapter 4 - Functions and Program Structure
- [x] **Ex 4-1 (Pg 71)** - Write the function `strrindex(s,t)`, which returns the position of the rightmost occurrence of `t` in `s`, or -1 if there is none. - [Solution](strrindex.c)
- [x] **Ex 4-2 (Pg 73)** - Extend `atof` to handle scientific notation of the form `123.45e-6` where a floating-point number may be followed by e or E and an optionally signed exponent. - [Solution](atof.c)
- [x] **Ex 4-3 (Pg 79)** - Given the basic framework, it's straightforward to extend the calculator. Add the modulus (`%`) operator and provisions for negative numbers. - [Solution](calculator.c)
- [x] **Ex 4-4 (Pg 79)** - Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack. - [Solution](calculator.c)
- [x] **Ex 4-5 (Pg 79)** - Add access to library functions like `sin`, `exp`, and `pow`. See `<math.h>` in Appendix B, Section 4. - [Solution](calculator.c)
- [x] **Ex 4-6 (Pg 79)** - Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.) Add a variable for the most recently printed value. - [Solution](calculator.c)
- [x] **Ex 4-7 (Pg 79)** - Write a routine `ungets(s)` that will push back an entire string onto the input. Should `ungets` know about `buf` and `bufp`, or should it just use `ungetch`? - [Solution](calculator.c)
- [x] **Ex 4-8 (Pg 79)** - Suppose that there will never be more than one character of pushback. Modify `getch` and `ungetch` accordingly. - [Solution](calculator.c)
- [x] **Ex 4-9 (Pg 79)** - Our `getch` and `ungetch` do not handle a pushed-back `EOF` correctly. Decide what their properties ought to be if an `EOF` is pushed back, then implement your design. - [Solution](calculator.c)
- [x] **Ex 4-10 (Pg 79)** - An alternate organization uses `getline` to read an entire input line; this makes `getch` and `ungetch` unnecessary. Revise the calculator to use this approach. - [Solution](calculator.c)
- [x] **Ex 4-11 (Pg 83)** - Modify `getop` so that it doesn't need to use `ungetch`. Hint: use an internal static variable. - [Solution](getop.c)
- [x] **Ex 4-12 (Pg 88)** - Adapt the ideas of `printd` to write a recursive version of `itoa`; that is, convert an integer into a string by calling a recursive routine. - [Solution](itoaRecursive.c)
- [x] **Ex 4-13 (Pg 88)** - Write a recursive version of the function `reverse(s)`, which reverses the string `s` in place. - [Solution](reverseRecursive.c)
- [x] **Ex 4-14 (Pg 91)** - Define a macro `swap(t,x,y)` that interchanges two arguments of type `t`. (Block structure will help.) - [Solution](swapMacro.c)

## Chapter 5 - Pointers and Arrays
- [x] **Ex 5-1 (Pg 97)** - As written, `getint` treats a `+` or `-` not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input. - [Solution](getint.c)
- [x] **Ex 5-2 (Pg 97)** - Write `getfloat`, the floating-point analog of `getint`. What type does `getfloat` return as its function value? - [Solution](getfloat.c)
- [x] **Ex 5-3 (Pg 107)** - Write a pointer version of the function `strcat` that we showed in Chapter 2: `strcat(s,t)` copies the string `t` to the end of `s`. - [Solution](strcat.c)
- [x] **Ex 5-4 (Pg 107)** - Write the function `strend(s,t)`, which returns 1 if the string `t` occurs at the end of the string `s`, and zero otherwise. - [Solution](strend.c)
- [x] **Ex 5-5 (Pg 107)** - Write versions of the library functions `strncpy`, `strncat`, and `strncmp`, which operate on at most the first `n` characters of their argument strings. For example, `strncpy(s,t,n)` copies at most `n` characters of `t` to `s`. Full descriptions are in Appendix B. - [Solution](strn.c)
- [x] **Ex 5-6 (Pg 107)** - Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include `getline` (Chapters 1 and 4), `atoi`, `itoa`, and their variants (Chapters 2, 3, and 4), `reverse` (Chapter 3), and `strindex` and `getop` (Chapter 4). - [Solution](pointerVariants.c)
- [x] **Ex 5-7 (Pg 110)** - Rewrite `readlines` to store lines in an array supplied by `main`, rather than calling `alloc` to maintain storage. How much faster is the program? - [Solution](sort.c)
- [x] **Ex 5-8 (Pg 112)** - There is no error-checking in `day_of_year` or `month_day`. Remedy this defect. - [Solution](dayOfYear.c)
- [x] **Ex 5-9 (Pg 114)** - Rewrite the routines `day_of_year` and `month_day` with pointers instead of indexing.
- [x] **Ex 5-10 (Pg 118)** - Write the program `expr`, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example, `expr 2 3 4 + *` evaluates `2 X (3+4)`. - [Solution](expr.c)
- [x] **Ex 5-11 (Pg 118)** - Modify the programs `entab` and `detab` (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments. - Solution: [entab](entabArgs.c), [detab](detabArgs.c)
- [x] **Ex 5-12 (Pg 118)** - Extend `entab` and `detab` to accept the shorthand `entab -m +n` to mean tab stops every `n` columns, starting at column `m`. Choose convenient (for the user) default behavior. - Solution: [entab](entabArgs.c), [detab](detabArgs.c)
- [x] **Ex 5-13 (Pg 118)** - Write the program `tail`, which prints the last `n` lines of its input. By default, `n` is 10, say, but it can be changed by an optional argument, so that `tail -n` prints the last `n` lines. The program should behave rationally no matter how unreasonable the input or the value of `n`. Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size. - [Solution](tail.c)
- [x] **Ex 5-14 (Pg 121)** - Modify the sort program to handle a `-r` flag, which indicates sorting in reverse (decreasing) order. Be sure that `-r` works with `-n`. - [Solution](sortFuncPointer.c)
- [x] **Ex 5-15 (Pg 121)** - Add the option `-f` to fold upper and lower case together, so that case distinctions are not made during sorting; for example, `a` and `A` compare equal. - [Solution](sortFuncPointer.c)
- [x] **Ex 5-16 (Pg 121)** - Add the `-d` ("directory order") option, which makes comparisons only on letters, numbers and blanks. Make sure it works in conjunction with `-f`. - [Solution](sortFuncPointer.c)
- [x] **Ex 5-17 (Pg 121)** - Add a field-handling capability, so sorting may be done on fields within lines, each field sorted according to an independent set of options. (The index for this book was sorted with `-df` for the index category and `-n` for the page numbers.) - [Solution](sortFuncPointer.c)
- [x] **Ex 5-18 (Pg 126)** - Make `dcl` recover from input errors. - [Solution](dcl.c)
- [x] **Ex 5-19 (Pg 126)** - Modify `undcl` so that it does not add redundant parentheses to declarations. - [Solution](undcl.c)
- [x] **Ex 5-20 (Pg 126)** - Expand `dcl` to handle declarations with function argument types, qualifiers like `const`, and so on. - [Solution](dcl.c)

## Chapter 6 - Structures
- [x] **Ex 6-1 (Pg 136)** - Our version of `getword` does not properly handle underscores, string constants, comments, or preprocessor control lines. Write a better version. - [Solution](countKeywords.c)
- [x] **Ex 6-2 (Pg 143)** - Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters but different somewhere thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set from the command line. - [Solution](wordFrequency.c)
- [x] **Ex 6-3 (Pg 143)** - Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. Remove noise words like "the," "and," and so on. - [Solution](crossReferencer.c)
- [x] **Ex 6-4 (Pg 143)** - Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. Precede each word by its count. - [Solution](distinctWordFrequency.c)
- [x] **Ex 6-5 (Pg 145)** - Write a function `undef` that will remove a name and definition from the table maintained by `lookup` and `install`. - [Solution](tableLookup.c)
- [x] **Ex 6-6 (Pg 145)** - Implement a simple version of the `#define` processor (i.e., no arguments) suitable for use with C programs, based on the routines of this section. You may also find `getch` and `ungetch` helpful. - [Solution](defineProcessor.c)

## Chapter 7 - Input and Output
- [x] **Ex 7-1 (Pg 153)** - Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked with, as found in `argv[0]`. - [Solution](upperOrLower.c)
- [x] **Ex 7-2 (Pg 155)** - Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines. - [Solution](printArbitraryHexOct.c)
- [x] **Ex 7-3 (Pg 156)** - Revise `minprintf` to handle more of the facilities of `printf`. - [Solution](minprintf.c)
- [x] **Ex 7-4 (Pg 159)** - Write a private version of `scanf` analogous to `minprintf` from the previous section. - [Solution](minscanf.c)
- [x] **Ex 7-5 (Pg 159)** - Rewrite the postfix calculator of Chapter 4 to use `scanf` and/or `sscanf` to do the input and number conversion. - [Solution](calculator.c)
- [x] **Ex 7-6 (Pg 165)** - Write a program to compare two files, printing the first line where they differ. - [Solution](diff.c)
- [x] **Ex 7-7 (Pg 165)** - Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments, from the standard input. Should the file name be printed when a matching line is found? - [Solution](find.c)
- [x] **Ex 7-8 (Pg 165)** - Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file. - [Solution](pager.c)
- [x] **Ex 7-9 (Pg 168)** - Functions like `isupper` can be implemented to save space or to save time. Explore both possibilities. - [Solution](isupper.c)

## Chapter 8 - The UNIX System Interface
*A majority of the solutions to this chapter are heavily inspired by other solutions found online.*
- [x] **Ex 8-1 (Pg 174)** - Rewrite the program `cat` from Chapter 7 using `read`, `write`, `open` and `close` instead of their standard library equivalents. Perform experiments to determine the relative speeds of the two versions. - [Solution](cat.c)
- [x] **Ex 8-2 (Pg 178)** - Rewrite `fopen` and `_fillbuf` with fields instead of explicit bit operations. Compare code size and execution speed. - [Solution](fopen.c)
- [x] **Ex 8-3 (Pg 179)** - Design and write `_flushbuf`, `fflush` and `fclose`. - [Solution](fopen.c)
- [x] **Ex 8-4 (Pg 179)** - The standard library function `int fseek(FILE *fp, long offset, int origin)` is identical to `lseek` except that `fp` is a file pointer instead of a file descriptor and the return value is an `int` status, not a position. Write `fseek`. Make sure that your `fseek` coordinates properly with the buffering done for the other functions of the library. - [Solution](fopen.c)
- [x] **Ex 8-5 (Pg 184)** - Modify the `fsize` program to print the other information contained in the inode entry. - [Solution](fsize.c)
- [x] **Ex 8-6 (Pg 189)** - The standard library function `calloc(n,size)` returns a pointer to `n` objects of size `size`, with the storage initialized to zero. Write `calloc`, by calling `malloc` or by modifying it. - [Solution](calloc.c)
- [x] **Ex 8-7 (Pg 189)** - `malloc` accepts a size request without checking its plausibility; `free` believes that the block it is asked to free contains a valid size field. Improve these routines so they take more pains with error checking. - [Solution](malloc.c)
- [x] **Ex 8-8 (Pg 189)** - Write a routine `bfree(p,n)` that will free an arbitrary block `p` of `n` characters into the free list maintained by `malloc` and `free`. By using `bfree`, a user can add a static or external array to the free list at any time. - [Solution](bfree.c)
