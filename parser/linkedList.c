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




