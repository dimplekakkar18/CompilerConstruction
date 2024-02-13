#include <stdio.h>
#include <string.h>
#include "lexer2.h"

#define NUM_KEYWORDS 31
#define HASH_TABLE_SIZE 127 
#define PRIME 31
struct keyword kwtable[HASH_TABLE_SIZE];

int calculateHash(char *kwname){
    
    int hash_value = 0;
    for(int i = 0; i < strlen(kwname); i++){
        hash_value = (hash_value * PRIME + kwname[i]) % HASH_TABLE_SIZE;
    }
    return hash_value;
}

void lookUpTable()
{
    // allocating memory for the LOOKUP table
    struct keyword arr[NUM_KEYWORDS] = {
        {"with", TK_WITH},
        {"parameters", TK_PARAMETERS},
        {"end", TK_END},
        {"while", TK_WHILE},
        {"union", TK_UNION},
        {"endunion", TK_ENDUNION},
        {"definetype", TK_DEFINETYPE},
        {"as", TK_AS},
        {"type", TK_TYPE},
        {"_main", TK_MAIN},
        {"global", TK_GLOBAL},
        {"parameter", TK_PARAMETER},
        {"list", TK_LIST},
        {"input", TK_INPUT},
        {"output", TK_OUTPUT},
        {"int", TK_INT},
        {"real", TK_REAL},
        {"endwhile",TK_ENDWHILE},
        {"if", TK_IF},
        {"then", TK_THEN},
        {"endif", TK_ENDIF},
        {"read", TK_READ},
        {"write", TK_WRITE},
        {"return", TK_RETURN},
        {"call", TK_CALL},
        {"record", TK_RECORD},
        {"endrecord", TK_ENDRECORD},
        {"else", TK_ELSE},
        {"PROGRAMEND", TK_PROGRAMEND},
        {"ERROR", TK_ERROR},
        {"EOF", TK_EOF}
    };

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        kwtable[i].keywordname = NULL;
        kwtable[i].tokenID = -1;
    }
    int collision = 0;

    for (int i = 0; i < NUM_KEYWORDS; i++)
    {
        int index = calculateHash(arr[i].keywordname);
        if (kwtable[index].keywordname == NULL)
        {
            kwtable[index].keywordname = arr[i].keywordname;
            kwtable[index].tokenID = arr[i].tokenID;
        }
        else
        {
            while (kwtable[index].keywordname != NULL)
            {
                index = (index + 1) % HASH_TABLE_SIZE;
            }
            kwtable[index].keywordname = arr[i].keywordname;
            kwtable[index].tokenID = arr[i].tokenID;
            collision++; 
        }
    }
}


int getKeyWordID(char *lexeme){

    int index = calculateHash(lexeme);
    if(kwtable[index].keywordname!=NULL){
        if(strcmp(kwtable[index].keywordname,lexeme)==0){
            return kwtable[index].tokenID;
        }
    }

    return -1;
}
