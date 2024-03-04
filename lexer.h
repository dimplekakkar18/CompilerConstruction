#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer2.h"

// int lookUpTable();
// int calculateHash(char *word);
// int getKeyWordID(char *word);
// void insertKeyWord();
int calcHash(char *identifier);
void createSymbolTable();
identifierNode *createSymbolNode(char *identifierName, int tokenID);
int insertToSymbolTable(char * identifierName, int tokenID);
int searchSymbolTable(char *identifierName);
int checkTokenID(char *identifierName, int tokenID);
void destroySymbolTable(); 


// Contents of your header file go here
void removeComments(char *test_file, char *clean_file);
void initializeBuffers();
void loadBuffer(char* buffer, FILE* fp);
char getCharFromBuffers(FILE* fp);
char* getLexeme();
void refreshPtr();
TOKEN getToken(FILE *fp, FILE* errorfile);
int len(char * string); 
void printTokenInfo(TOKEN tk, FILE * fp); 


#endif 
