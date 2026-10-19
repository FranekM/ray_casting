/**
 * @file utf8_read.c
 * @brief Implementation of reading from utf8 stream.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../headers/utf8.h"

/** Size of buffer. */
#define MAX_BUFFER_SIZE 1000

/** Buffer for reading from utf8 stream. */
static long buffer[MAX_BUFFER_SIZE];

/**
 * @brief Indicate how many bytes was used to encode current character in UTF-8.
 * @param c First byte of current character.
 * @return Number of bytes.
 */
static int require(long c);

/**
 * @brief Read first character from stream into buffer and return bufferIndex, where next character shcould be saved.
 *        If there was no BOM character the bufferIndex will be 1, else it will be 0 indicating that BOM is at first
 *        bufferIndex of buffer and should be overrided by next character from stream.
 * @param file pointer to input stream.
 * @return Index of buffer where next character from stream should be saved.
 */
static int skipBOM(FILE *file);

/**
 * @brief Predicate function to be passed into utf8_bufferedRead() when reading should end at white space.
 * @param code UCS-4 code point.
 * @see utf8_bufferedRead()
 */
static int endWithSpace(long code);

/**
 * @brief Predicate function to be passed into utf8_bufferedRead() when reading should end at new line character.
 * @param code UCS-4 code point.
 * @see utf8_bufferedRead()
 */
static int endWithNewLine(long code);

/**
 * @brief Read from stream using buffer until @p end predicate returns true or EOF is reached or buffer is full.
 * @param file Pointer to input stream.
 * @param end Predicate function accepting UCS-4 code point, evaluating into true (1) or false (0).
 * @return Array of UCS-4 code points as string followed by '\0'.
 */
static Ucs4str utf8_bufferedRead(FILE *file, int (*end)(long));


long utf8_read(FILE *file) {
    long c = fgetc(file);
    if (c < 0x80)
        return c;
    int bytes = require(c);
    long codePoint = (c & getmap[bytes]) << putmap[bytes];
    while (bytes-- > 0) {
        c = fgetc(file);
        codePoint |= (c & getmap[0]) << putmap[bytes];
    }
    return codePoint;
}

Ucs4str utf8_bufferedRead(FILE *file, int (*end)(long)) {
    long c;
    int i = skipBOM(file);
    if (buffer[0] == EOF)
        return NULL;
    do
        buffer[i++] = c = utf8_read(file);
    while (!end(c) && c != EOF && i < MAX_BUFFER_SIZE);
    return ucs4str_new(buffer, 0, i-1);
}

Ucs4str utf8_readWord(FILE *file) {
    return utf8_bufferedRead(file, endWithSpace);
}

Ucs4str utf8_readLine(FILE *file) {
    return utf8_bufferedRead(file, endWithNewLine);
}

int endWithSpace(long code) {
    return utf8_isWhitespace(code);
}

int endWithNewLine(long code) {
    return code == '\n';
}

int skipBOM(FILE *file) {
    if ((buffer[0] = utf8_read(file)) == BOM)
        return 0;
    return 1;
}

int require(long c) {
    if ((c & 0xE0) == 0xC0)
        return 1;
    if ((c & 0xF0) == 0xE0)
        return 2;
    if ((c & 0xF8) == 0xF0)
        return 3;
    if ((c & 0xFC) == 0xF8)
        return 4;
    if ((c & 0xFE) == 0xFC)
        return 5;
    return 0;
}
