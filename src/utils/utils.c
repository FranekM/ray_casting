#include <stdarg.h>
#include <stdlib.h>
#include "../headers/utils.h"

void utils_freeAll(int count, ...) {
    va_list args;
    va_start(args, count);
    while (count-- > 0)
        free(va_arg(args, void *));
    va_end(args);
}
