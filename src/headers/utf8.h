#ifndef UTF8_H
#define UTF8_H

/**
 * @file utf8.h
 * @brief Definition of utf8 library.
 */

#include <stdbool.h>
#include <stdio.h>

/** BOM (Byte Order Mark) constant. */
#define BOM 0xFEFF

typedef long *Ucs4str;

#define AS_UCS4STR(codePoints...) (long[]){codePoints}
#define LETTER_SIZE sizeof(long)

/**
 * (getmap[n] & byte) reset bits that was used to encode byte position in UTF-8 character.
 * when n > 0 for first byte in multibyte string.
 * when n == 0 for every bite that follow.
 *
 * |INDEX |DEC | HEX  | BIN      |
 * |------|----|------|----------|
 * | 0    | 63 | 0x3F | 00111111 |
 * | 1    | 31 | 0x1F | 00011111 |
 * | 2    | 15 | 0x0F | 00001111 |
 * | 3    |  7 | 0x07 | 00000111 |
 * | 4    |  3 | 0x03 | 00000011 |
 * | 5    |  1 | 0x01 | 00000001 |
 */
static const long getmap[6] = {0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01};

/**
 * putmap[n] is a number of shifts that must be performed of UCS-4 code point in order to
 * move bits of UTF-8 n-th bite into lowest indexes.
 *
 * |INDEX |DEC | HEX  | BIN      |
 * |------|----|------|----------|
 * | 0    |  0 | 0x00 | 00000000 |
 * | 1    |  6 | 0x06 | 00000110 |
 * | 2    | 12 | 0x0C | 00001100 |
 * | 3    | 18 | 0x12 | 00010010 |
 * | 4    | 24 | 0x18 | 00011000 |
 * | 5    | 30 | 0x1E | 00011110 |
 */
static const long putmap[6] = {0x00, 0x06, 0x0C, 0x12, 0x18, 0x1E};

/**
 * bits of prefix[n] until first zero are prefix of first character in UTF-8 n-byte long
 * sequence. For evry byte that folow prefix[0] contain prefix of byte.
 *
 * |INDEX |DEC | HEX  | BIN      |
 * |------|----|------|----------|
 * | 0    | 128 | 0x80 | 10000000 |
 * | 1    | 192 | 0xC0 | 11000000 |
 * | 2    | 224 | 0xE0 | 11100000 |
 * | 3    | 240 | 0xF0 | 11110000 |
 * | 4    | 248 | 0xF8 | 11111000 |
 * | 5    | 252 | 0xFC | 11111100 |
 */
static const long prefix[6] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

/**
 * @brief Read single character from utf8 encoded file.
 * @param file Pointer to input stream.
 * @return UCS-4 code point.
 */
long utf8_read(FILE *file);

/**
 * @brief Read stream until new line character is detected.
 * @param file Pointer to input stream.
 * @return Part of stream as USC-4 code points string followed by '\0'.
 */
Ucs4str utf8_readLine(FILE *file);

/**
 * @brief Read stream until whitespace is detected.
 * @param file Pointer to input stream.
 * @return Part of stream as USC-4 code points string followed by '\0'.
 */
Ucs4str utf8_readWord(FILE *file);

/**
 * @brief Write single character into output stream.
 * @param file Output stream.
 * @param codePoint Character to be written.
 */
void utf8_write(FILE *file, long codePoint);

/**
 * @brief Write string into output stream. Add newline at the end.
 * @param file Output stream.
 * @param line String to be written.
 */
void utf8_writeLine(FILE *file, Ucs4str line);

/**
 * @brief Write string into output stream. Do not add whitespace befor or after the word.
 * @param file Output stream.
 * @param word String to be written.
 */
void utf8_writeWord(FILE *file, Ucs4str word);


/**
 * @brief Test if @p code is whitespace.
 * @param[in] code UCS-4 code point.
 * @return bool
 */
bool utf8_isWhitespace(long code);

/**
 * @brief Test if @p string starts with @p start.
 * @param string
 * @param start
 * @return bool
 */
bool utf8_startsWith(Ucs4str string, Ucs4str start);

/**
 * @brief Test is string are equal.
 * @param s1
 * @param s2
 * @return bool
 */
bool utf8_equals(Ucs4str s1, Ucs4str s2);

/**
 * @brief Calculate size of a string.
 * @param string
 * @return string size
 */
int utf8_length(Ucs4str string);

/**
 * @brief Trim whitespaces from beginning of string.
 * @param string
 * @return new string
 */
Ucs4str utf8_trim(Ucs4str string);

/**
 * @brief Extract part of string.
 * @param string
 * @param offset Beginning of part to extract.
 * @param length Length of part to extract. If equal 0 then cut until end of string.
 * @return new string
 */
Ucs4str utf8_substring(Ucs4str string, int offset, int length);

/**
 * @brief Help iterate through line of text.
 * @param line
 * @param offset Start from here.
 * @param hasNext Indicates if there is next word in line.
 * @return new string
 */
Ucs4str utf8_nextWord(Ucs4str line, int *offset, bool *hasNext);

/**
 * @brief Creates new string from buffer
 * @param buffer
 * @param offset read buffer from here
 * @param length read length number of characters from buffer
 * @return new string
 */
Ucs4str ucs4str_new(long *buffer, int offset, int length);

#endif
