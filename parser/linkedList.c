// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
hash_ele hash_table[HASH_TABLE_SIZE]; //FIX
ruleLL* createLL()
{
    ruleLL* linkedlist = malloc(sizeof(ruleLL)); 
    linkedlist->head = NULL; 
    linkedlist->tail = NULL; 
    return linkedlist; 
}

LLNODE * createNewNode(SYMBOL symbol, SYMBOLTYPE type)
{
    LLNODE * node = (LLNODE *) malloc(sizeof(LLNODE));
    node->next = NULL; 
    node->prev = NULL; 
    node->sym = symbol; 
    node->type = type;  
    return node; 
}

void addNewNode(LLNODE * node, ruleLL* rule)
{
    if(rule->head == NULL)
    {
        rule->head = node; 
        rule->tail = node; 
    }
    else
    {
        LLNODE * temp = rule->head; 
        while(temp->next!=NULL)
        {
            temp = temp->next; 
        }
        temp->next = node; 
        node->prev = temp; 
        rule->tail = node; 
    }
}


void freeNode(ruleLL* list) {
    // Free the memory allocated for the node
    if(list->head==NULL)return;
    LLNODE* temp = list->head;
    list->head = temp->next;
    free(temp);
}

void freeLL(ruleLL *list) {
    if(list->head==NULL){
        free(list);
        return;
    }

    while(list->head!=NULL){
        freeNode(list);
    }
    
}

void freeGrammar(ruleLL *grammar) {
    // Free memory for each rule
    for (int i = 0; i < NUMRULES; i++) {
        freeLL(&grammar[i]);
    }
    // Free memory for the grammar array
    free(grammar);
}

