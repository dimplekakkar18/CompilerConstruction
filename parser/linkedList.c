#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
ruleLL createLL()
{
    ruleLL linkedlist; 
    linkedlist.head = NULL; 
    linkedlist.tail = NULL; 
    return linkedlist; 
}

LLNODE * createNewNode(SYMBOL symbol, SYMBOLTYPE type)
{
    LLNODE * node = (LLNODE *) malloc(sizeof(LLNODE));
    node->next = NULL; 
    node->sym = symbol; 
    node->type = type;  
    return node; 
}

int addNewNode(LLNODE * node, ruleLL rule)
{
    if(rule.head == NULL)
    {
        rule.head = node; 
        rule.tail = node; 
    }
    else
    {
        LLNODE * temp = rule.head; 
        while(temp->next!=NULL)
        {
            temp = temp->next; 
        }
        temp->next = node; 
    }
}



