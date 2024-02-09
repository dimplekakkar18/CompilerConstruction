#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lexer2.h>

// Contents of your header file go here
void removeComments(char *test_file, char *clean_file);
int convertToInt(char* lexeme);
double convertToRNUMt(char* lexeme);
TOKEN getToken(FILE* fp);    //implement getlexeme()

#endif 
