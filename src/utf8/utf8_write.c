/**
 * @file utf8_write.c
 * @brief Implementation of writing into utf8 stream.
 */

#include <stdio.h>
#include "../headers/utf8.h"

/**
 * @brief Indicate how many bytes is needed to encode UCS-4 code point in UTF-8.
 * @param c UCS-4 code point.
 * @return Number of bytes.
 */
static int require(long);

void utf8_write(FILE *file, long codePoint) {
    if (codePoint < 0x80) {
        fputc(codePoint, file);
        return;
    }

    int bytes = require(codePoint);
    int c = (codePoint >> putmap[bytes]) & getmap[bytes] | prefix[bytes];
    fputc(c, file);
    while (bytes-- > 0) {
        c = (codePoint >> putmap[bytes]) & getmap[0] | prefix[0];
        fputc(c, file);
    }
}

void utf8_writeWord(FILE *file, Ucs4str word) {
    while (*word != '\0')
        utf8_write(file, *word++);
}

void utf8_writeLine(FILE *file, Ucs4str line) {
    utf8_writeWord(file, line);
    utf8_write(file, '\n');
}

int require(long c) {
    if (c < 0x800)
        return 1;
    if (c < 0x10000)
        return 2;
    if (c < 0x200000)
        return 3;
    if (c < 0x4000000)
        return 4;
    if (c < 0x80000000)
        return 5;
    return 0;
}
