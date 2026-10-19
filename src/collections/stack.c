#include <stdlib.h>
#include "../headers/collections.h"

Stack stack_new() {
    Stack stack = malloc(QUEUE_SIZE);
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

void stack_clear(Stack stack) {
    StackNode node = stack->head;
    StackNode next = NULL;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    stack->head = NULL;
    stack->size = 0;
}

bool stack_isEmpty(Stack stack) {
    return stack->head == NULL;
}

long stack_poll(Stack stack) {
    long value = 0;
    if (stack->head != NULL) {
        value = stack->head->value;
        StackNode next = stack->head->next;
        free(stack->head);
        stack->head = next;
        --stack->size;
    }
    return value;
}

long stack_peek(Stack stack) {
    long value = 0;
    if (stack->head != NULL)
        value = stack->head->value;
    return value;
}

int stack_push(Stack stack, long value) {
    StackNode node = malloc(NODE_QUEUE_SIZE);
    node->value = value;
    if (stack->head != NULL)
        node->next = stack->head;
    else
        node->next = NULL;
    stack->head = node;
    return ++stack->size;
}

int stack_size(Stack stack) {
    return stack->size;
}
