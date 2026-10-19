#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Size of pointer to void.
 */
#define POINTER_SIZE sizeof(void *)

/**
 * @brief Just like free() but for @p count pointers.
 * @param count number of arguments.
 * @param ... Pointers to be freed.
 */
void utils_freeAll(int count, ...);

#endif
