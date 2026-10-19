#include <stdlib.h>
#include "../headers/collections.h"

ArrayList arrayList_new(int initSize) {
    ArrayList list = malloc(ARRAYLIST_SIZE);
    list->maxSize = initSize;
    list->list = calloc(initSize, POINTER_SIZE);
    list->size = 0;
    return list;
}

void arrayList_clear(ArrayList list) {
    for (int i = 0; i < list->size; i++) {
        free(list->list[i]);
        list->list[i] = NULL;
    }
    list->size = 0;
}

void arrayList_delete(ArrayList list) {
    free(list->list);
    free(list);
}

int arrayList_add(ArrayList list, void *value) {
    if (list->size < list->maxSize)
        list->list[list->size++] = value;
    return list->size;
}

void *arrayList_get(ArrayList list, int index) {
    if (index >= list->size || index < 0)
        return NULL;
    return list->list[index];
}

int arrayList_size(ArrayList list) {
    return list->size;
}
