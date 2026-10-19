/**
 * @file utf8_ctype.c
 * @brief Implementation of tools to categorise unicode characters.
 */

#include "../headers/utf8.h"


bool utf8_isWhitespace(long code) {
    if (code == 0x20)
        return true;
    if (code >= 0x09 && code <= 0x0D)
        return true;
    if (code == 0x85 || code == 0xA0 || code == 0x1680)
        return true;
    if (code >= 0x2000 && code <= 0x200A)
        return true;
    if (code == 0x2028 || code == 0x2029 || code == 0x202F || code == 0x205F || code == 0x3000)
        return true;
    return 0;
}
