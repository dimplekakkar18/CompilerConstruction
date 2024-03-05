// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#include "linked_listQ.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    NODE front;
    LIST data;
};

Queue *createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if(q != NULL){
        LIST l1 = createNewList();
        q->data = l1;
        q->front = q->data->head;
    }
    return q;
}

bool enqueue(Queue *q, Element e) {
	NODE node = createNewQNode(e);
	if(node==NULL) return false;
	insertNodeAtEnd(node ,q->data);
    q->front = q->data->head;
    return true;
}
// Pushes element onto stack. Returns false if memory allocation fails

// Returns a pointer to the top element. Returns NULL if stack is empty
Element* front(Queue *q) {
    if(isEmptyQ(q)) {
    	return NULL;
    }
    return &q->front->data;
}

// Pops the top element and returns true. Returns false if stack is empty
bool dequeue(Queue *q) {
    if(isEmptyQ(q)) return false;
    removeFirstNode(q->data);
    q->front = q->data->head;
    return true;
}

// Returns true if stack is empty. Returns false otherwise
bool isEmptyQ(Queue* q) {
    if(q->front==NULL) {
    	return true;
    }
    return false;
}

int size(Queue *q) {
    NODE temp = q->data->head;
    int size = 0;
    while(temp!=NULL){
        temp = temp->next;
        size++;
    }
    return size;
}
// size() returns the number of elements in the queue.

void destroyQueue(Queue *q) {
	destroyListQ(q->data);
    free(q);
}