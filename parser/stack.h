#ifndef STACK_H
#define STACK_H

typedef struct stackNODE{
    struct stackNODE* next;
    int val;
}*stackNODE;

typedef struct{
    int count;
    stackNODE head;
}stack;


stack * getStack();

void push(stack *st,int val);

int pop(stack *st);

void deleteStack(stack * st);

#endif