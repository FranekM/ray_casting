#include <stdlib.h>
#include "../headers/utf8.h"

#define BUFFER_MAX_SIZE 1000

bool utf8_startsWith(Ucs4str string, Ucs4str start) {
    int i = 0;
    while (start[i] != '\0' && start[i] == string[i])
        i++;
    return start[i] == '\0';
}

int utf8_length(Ucs4str string) {
    int length = 0;
    while (string[length] != '\0')
        length++;
    return length;
}

Ucs4str utf8_trim(Ucs4str string) {
    int i = 0;
    while (utf8_isWhitespace(string[i]))
        i++;
    return utf8_substring(string, i, 0);
}

Ucs4str utf8_substring(Ucs4str string, int offset, int length) {
    int strLength = utf8_length(string);
    if (length + offset > strLength || length == 0)
        length = strLength - offset;
    Ucs4str substr = calloc(length + 1, LETTER_SIZE);
    for (int i = 0; i < length; i++)
        substr[i] = string[i + offset];
    substr[length] = '\0';
    return substr;
}

bool utf8_equals(Ucs4str s1, Ucs4str s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        ++i;
    return s1[i] == s2[i];
}

Ucs4str utf8_nextWord(Ucs4str line, int *offset, bool *hasNext) {
    int i = 0;
    long buffer[BUFFER_MAX_SIZE];
    while (line[*offset] != '\0' && !utf8_isWhitespace(line[*offset]))
        buffer[i++] = line[(*offset)++];
    while (utf8_isWhitespace(line[(*offset)]))
        ++(*offset);
    *hasNext = line[*offset] != '\0';
    return ucs4str_new(buffer, 0, i);
}

Ucs4str ucs4str_new(long *buffer, int offset, int length) {
    Ucs4str str = calloc(length + 1, LETTER_SIZE);
    str[length] = '\0';
    while (--length >= 0)
        str[length] = buffer[offset + length];
    return str;
}