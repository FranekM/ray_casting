#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <stdbool.h>
#include "utils.h"


#define ARRAYLIST_SIZE sizeof(struct arraylist)

typedef struct arraylist {
    void **list;
    int maxSize;
    int size;
} arraylist, *ArrayList;

ArrayList arrayList_new(int initSize);
void arrayList_clear(ArrayList list);
void arrayList_delete(ArrayList list);
void *arrayList_get(ArrayList list, int index);
int arrayList_add(ArrayList list, void *value);
int arrayList_size(ArrayList list);


#define NODE_QUEUE_SIZE sizeof(struct node_queue)
#define QUEUE_SIZE sizeof(struct queue)

typedef struct node_queue {
    void *value;
    struct node_queue *next;
    struct node_queue *prev;
} node_queue, *QueueNode;

typedef struct queue {
    QueueNode head;
    QueueNode tail;
    int size;
} queue, *Queue;

Queue queue_new();
void queue_clear(Queue queue);
void *queue_poll(Queue queue);
void *queue_peek(Queue queue);
int queue_add(Queue queue, void *value);
int queue_size(Queue queue);


#define NODE_STACK_SIZE sizeof(struct node_stack)
#define STACK_SIZE sizeof(struct stack)

typedef struct node_stack {
    long value;
    struct node_stack *next;
} node_stack, *StackNode;

typedef struct stack {
    StackNode head;
    int size;
} stack, *Stack;

Stack stack_new();
void stack_clear(Stack stack);
long stack_poll(Stack stack);
long stack_peek(Stack stack);
bool stack_isEmpty(Stack stack);
int stack_push(Stack stack, long value);
int stack_size(Stack stack);

#endif
