// #define numNTS 57
// #define numRules 90

// int addToSet(long long int* set, int term);

// int setContains(long long int set, int term);


// int calculateHash(char *word); 
#ifndef PARSER_H
#define PARSER_H
#include "linkedList.h"
#include "treeADT.h"

int calculateHash(char *word);
int addnonTerm();
int addTerm();
void create_hashTable();
int getIndex(char *tok);
Tree * makeParseTree(ruleLL *grammar, int ** parse_table, FILE * fp);
int** makeParseTable2(token_set* first, token_set* follow, ruleLL* grammar); 
ruleLL * createGrammar(char * filename); 
void computeFirst(token_set *firstSet, ruleLL* rules);
void generateFollow(ruleLL* grammar, token_set* follow, token_set* first); 
#endif