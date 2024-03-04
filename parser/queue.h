// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#ifndef QUEUE_H
#define QUEUE_H
#include "element.h"
#include <stdbool.h>

typedef struct Queue Queue;

Queue *createQueue();
// createQueue() returns a pointer to a new Queue instance.
bool enqueue(Queue *queue, Element element);
// enqueue() returns true if the element was successfully added to the
// queue, false otherwise.
bool dequeue(Queue *queue);
// dequeue() returns true if the element was successfully removed from
// the queue, false otherwise.
Element *front(Queue *queue);
// front() returns a pointer to the element at the front of the queue,
// or NULL if the queue is empty.
int size(Queue *queue);
// size() returns the number of elements in the queue.
bool isEmptyQ(Queue *queue);
// isEmpty() returns true if the queue is empty, false otherwise.
void destroyQueue(Queue *queue);
// destroyQueue() frees all memory associated with the queue.
#endif