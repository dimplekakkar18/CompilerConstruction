#ifndef STACK_H
#define STACK_H

typedef struct{
    int count;
    stackNODE head;
}stack;

typedef struct{
    stackNODE next;
    int val;
}*stackNODE;

stack * getStack();

void push(stack *st,int val);

int pop(stack *st);

void deleteStack(stack * st);

#endif