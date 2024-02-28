#ifndef STACK_H
#define STACK_H
#include "parseDef.h"

#include "treeADT.h"

typedef struct stackNODE{
    struct stackNODE* next;
    stackEle val;
    TreeNode * treeref; 
}stackNODE;

typedef struct{
    int count;
    stackNODE * head;
}stack;


stack* getStack();

void push(stack *st, stackNODE * sd);

stackEle pop(stack *st);

void deleteStack(stack * st);

stackNODE * top(stack* st);

stackNODE * createStackEle(); 

#endif