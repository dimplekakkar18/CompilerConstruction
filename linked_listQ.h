// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "element.h"
#include <stdbool.h>

struct node
{
    Element data;
    struct node *next;
};
typedef struct node node;
typedef node * NODE;

struct linked_list
{
    int count;
    NODE head;
    NODE tail; // Not required for stack. Required for Queue
};
typedef struct linked_list linked_list;
typedef linked_list * LIST;

LIST createNewList();
// This function allocates memory for a new list and returns a pointer to it.
// The list is empty and the count is set to 0.

NODE createNewQNode(Element data);
// This function allocates memory for a new node and returns a pointer to it.
// The next pointer is set to NULL and the data is set to the value passed in.

void insertNodeIntoList(NODE node, LIST list);
// This function inserts a node at the beginning of the list.

void removeFirstNode(LIST list);
// This function removes the first node from the list.

void insertNodeAtEnd(NODE node, LIST list);
// This function inserts a node at the end of the list.

void destroyListQ(LIST list);
#endif