#include <stdlib.h>
#include "../headers/collections.h"

static void joinNodes(QueueNode a, QueueNode b);

Queue queue_new() {
    Queue queue = malloc(QUEUE_SIZE);
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

void queue_clear(Queue queue) {
    QueueNode node = queue->head;
    QueueNode prev = NULL;
    while (node != NULL) {
        prev = node->prev;
        free(node);
        node = prev;
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

void *queue_poll(Queue queue) {
    void *value = NULL;
    if (queue->head != NULL) {
        value = queue->head->value;
        QueueNode prev = queue->head->prev;
        free(queue->head);
        queue->head = prev;
        --queue->size;
    }
    return value;
}

void *queue_peek(Queue queue) {
    void *value = NULL;
    if (queue->head != NULL)
        value = queue->head->value;
    return value;
}

int queue_add(Queue queue, void *value) {
    QueueNode node = malloc(NODE_QUEUE_SIZE);
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    if (queue->size == 0)
        queue->head = node;
    else
        joinNodes(queue->tail, node);
    queue->tail = node;
    return ++queue->size;
}

int queue_size(Queue queue) {
    return queue->size;
}

void joinNodes(QueueNode a, QueueNode b) {
    a->prev = b;
    b->next = a;
}
