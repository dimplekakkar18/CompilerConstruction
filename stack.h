// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426


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