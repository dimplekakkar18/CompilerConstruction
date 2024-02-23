#include "stack.h"

stack * getStack()
{
    stack *st = malloc(sizeof(stack));
    st->count = 0;
    return st;
}

void push(stack *st,int val)
{
    stackNODE sd = malloc(sizeof(stackNODE));
    sd->next = st->head;
    st->head = sd;
    st->count++;
}

int pop(stack *st)
{
    if(st->count == 0)
        return -1;

    int val = st->head->val;
    stackNODE temp = st->head;
    st->head = st->head->next;
    st->count--;
    free(temp);
    return val;
}

void deleteStack(stack *st)
{
    stackNODE node = st->head;
    int i = st->count;
    free(st);
    for(;i>0;i--)
    {
        stackNODE temp = node->next;
        free(node);
        node = temp;
    }
}