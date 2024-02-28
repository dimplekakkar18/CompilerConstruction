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