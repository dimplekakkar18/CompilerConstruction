// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#ifndef LL_H
#define LL_H

#include "parseDef.h"

typedef struct LLNode{
    struct LLNode * next; 
    struct LLNode * prev; 
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
void freeNode(ruleLL *list);
void freeLL(ruleLL *list);
void freeGrammar(ruleLL *grammar);

extern ruleLL grammar[NUM_RULES]; 
#endif 