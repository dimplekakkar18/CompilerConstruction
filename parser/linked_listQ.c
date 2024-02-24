#include <stdio.h>
#include "linked_listQ.h"
#include <stdlib.h>

LIST createNewList() {
	LIST l1 = (LIST) malloc(sizeof(linked_list));
	if(l1==NULL) printf("%s\n", "Memory could not be allocated for the linked_list");
	l1->count = 0;
	l1->head = NULL;
	l1->tail = NULL;
	return l1;
}
// This function allocates memory for a new list and returns a pointer to it.
// The list is empty and the count is set to 0.

NODE createNewNode(Element data) {
	NODE n = (NODE) malloc(sizeof(node));
	if(n==NULL) return n;
	n->data = data;
	n->next = NULL;
	return n;
}
// This function allocates memory for a new node and returns a pointer to it.
// The next pointer is set to NULL and the data is set to the value passed in.

void insertNodeIntoList(NODE node, LIST l1) {
	node->next = l1->head;
	l1->head = node;
	l1->tail = node;
	l1->count++;
}
// This function inserts a node at the beginning of the list.

void removeFirstNode(LIST l1) {
	if(l1->head==NULL) return;
	NODE temp = l1->head;
	l1->head = temp->next;
    free(temp);
	l1->count--;
}
// This function removes the first node from the list.

void insertNodeAtEnd(NODE node, LIST l1) {
	if(l1->head==NULL){
		l1->head = node;
		l1->tail = node;
		l1->count++;
		return;
	}
	l1->tail->next = node;
	l1->tail = node;
	l1->count++;

} // Not required for stack. Required for Queue
// This function inserts a node at the end of the list.

void destroyListQ(LIST l1) {
	if(l1->head==NULL){
		free(l1);
		return;
	}
	while(l1->head!=NULL){
		removeFirstNode(l1);
	}
	free(l1);
}