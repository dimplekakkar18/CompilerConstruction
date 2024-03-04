// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426


#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
stack * getStack()
{
    stack *st = malloc(sizeof(stack));
    st->count = 0;
    return st;
}

void push(stack *st,stackNODE * sd)
{
    sd->next = st->head;
    st->head = sd;
    st->count++;
}

stackEle pop(stack *st)
{
    if(st->count == 0)
        printf("stack is empty, yet accessed\n");
    stackEle val = st->head->val;
    stackNODE * temp = st->head;
    st->head = st->head->next;
    st->count--;
    free(temp);
    return val;
}

void deleteStack(stack *st)
{
    stackNODE * node = st->head;
    int i = st->count;
    free(st);
    for(;i>0;i--)
    {
        stackNODE * temp = node->next;
        free(node);
        node = temp;
    }
}

stackNODE * top(stack* st){
    return st->head;
}

stackNODE * createStackEle(){
    stackNODE * node = (stackNODE *) malloc(sizeof(stackNODE));
    node->next = NULL; 
    node->treeref = NULL; 
    return node; 
}