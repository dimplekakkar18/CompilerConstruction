#include <stdio.h>
#include <parseDef.h>
#include <linkedList.h>
#include <stack.h>
#define numNTS 57
#define numRules 90
#define EPSILON 57//need to change acc

long long int follow[numNTS];
long long int first[numNTS];



void createGrammar(FILE * fp);

int addToSet(long long int* set, int term);

int setContains(long long int set, int term);

void propogateStack();

void generateFollow();
#define NUMRULES 87

ruleLL * createGrammar(FILE * fp,hash_ele * hash_table); 
int calculateHash(char *word); 
hash_ele * create_hashTable(); 
