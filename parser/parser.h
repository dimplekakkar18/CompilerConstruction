#include <stdio.h>
#include <stdlib.h>
#include "linkedList.c"
#define NUMRULES 87

ruleLL * createGrammar(FILE * fp,hash_ele * hash_table); 
int calculateHash(char *word); 
hash_ele * create_hashTable(); 
