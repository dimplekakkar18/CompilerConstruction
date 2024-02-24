#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include <stdlib.h>

#define NUM_KEYWORDS 30
#define HASH_TABLE_SIZE 127 // Prime Number
#define PRIME 31


symbolTableLL *symbolTable[HASH_TABLE_SIZE];

int calculateHash(char *identifier)
{
    int hash_value = 0;
    for (int i = 0; i < strlen(identifier); i++)
    {
        hash_value = (hash_value * PRIME + identifier[i]) % HASH_TABLE_SIZE;
        // hash_value = ((hash_value << 5) + hash_value) + kwname[i];
    }
    return hash_value;
}

void createSymbolTable()
{
    // Allocating memory for the symbol table
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        symbolTable[i] = (symbolTableLL *)malloc(sizeof(symbolTableLL));
        symbolTable[i]->head = NULL;
        symbolTable[i]->size = 0;
    }

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
        {"endwhile", TK_ENDWHILE},
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
        {"ERROR", TK_ERROR},
        {"EOF", TK_EOF}
};

    for (int i = 0; i < NUM_KEYWORDS; i++)
    {
        identifierNode* node = createNewNode(arr[i].keywordname,arr[i].tokenID);
        int index = calculateHash(node->identifierName);
        insertToSymbolTable(node->identifierName,node->tokenID);
    }
}

identifierNode *createNewNode(char *identifierName, int tokenID)
{
    identifierNode *newN = (identifierNode *)malloc(sizeof(identifierNode));
    newN->identifierName = identifierName;
    newN->tokenID = tokenID;
    newN->next = NULL;
    return newN;
}

int insertToSymbolTable(char * identifierName, int tokenID){
    int index = calculateHash(identifierName);
    identifierNode * insertNode = createNewNode(identifierName, tokenID); 
    identifierNode * temp = symbolTable[index]->head; 

    if(symbolTable[index]->size == 0)
    {
        symbolTable[index]->head = insertNode; 
        symbolTable[index]->size++; 
        return index; 
    }
    else{
        while(temp->next!=NULL)
        {
            temp = temp->next; 
        }
        temp->next = insertNode; 
        symbolTable[index]->size++;  
        return index; 
    }
    return -1; 

}
int searchSymbolTable(char *identifierName)
{
    int index = calculateHash(identifierName);
    identifierNode *curr = symbolTable[index]->head;
    while (curr != NULL)
    {
        if (strcmp(curr->identifierName, identifierName) == 0)
            return curr->tokenID;
        else
            curr = curr->next;
    }
    return -1;
}

int checkTokenID(char *identifierName, int tokenID)
{

    // int index = calculateHash(identifierName);
    int token = searchSymbolTable(identifierName);
    if (token != -1)
        return tokenID;
    else
    {
        int insert = insertToSymbolTable(identifierName, tokenID);
        if (insert == -1)
            printf("Error inserting lexeme to Symbol Table \n");
        return tokenID; 
    }
    return -1;
}

// void insertKeyWord()
// {

// }

// int main(){

//     createSymbolTable(); 
//     // insertKeyWord();

// }