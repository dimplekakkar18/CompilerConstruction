// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#ifndef PARSER_H
#define PARSER_H
#include "linkedList.h"
#include "treeADT.h"

int calculateHash(char *word);
int addnonTerm();
int addTerm();
void create_hashTable();
int getIndex(char *tok);
Tree * parseInputSourceCode(ruleLL *grammar, int ** parse_table, FILE * fp);
int** makeParseTable(long long int* first, long long int* follow, ruleLL* grammar); 
ruleLL * createGrammar(char * filename); 
void computeFirst(long long int *firstSet, ruleLL* rules);
void generateFollow(ruleLL* grammar, long long int* follow, long long int* first); 
void print_rules(ruleLL* rules);

#endif