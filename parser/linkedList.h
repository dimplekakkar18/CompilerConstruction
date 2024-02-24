#ifndef LL_H
#define LL_H

#include "parseDef.h"

typedef struct LLNode{
    struct LLNode * next; 
    SYMBOL sym; //This is the union which contains the value of terminal or nonterminal 
    enum SYMBOLTYPE type; //This is flag telling whether it is terminal/nonterminal or epsilon 
}LLNODE; 

typedef struct ruleLL{
    LLNODE * head; 
    LLNODE * tail; 
}ruleLL;
ruleLL* createLL();
LLNODE * createNewNode(SYMBOL symbol, SYMBOLTYPE type);
void addNewNode(LLNODE * node, ruleLL* rule);
ruleLL grammar[NUM_RULES];
#endif 