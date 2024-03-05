#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include <stdlib.h>

#define NUM_KEYWORDS 30     // Number of keywords in the language
#define HASH_TABLE_SIZE 127 // Prime Number to minimize collisions
#define PRIME 31            // Prime Number to minimize collisions

symbolTableLL *symbolTable[HASH_TABLE_SIZE];

// Function to calculate a hash value for a given identifier
int calcHash(char *identifier)
{
    int hash_value = 0;
    for (int i = 0; i < strlen(identifier); i++)
    {
        /*Update hash_value as iterate through the string using a hash function
        By using a prime number in the hash function, the likelihood of generating the
        same hash value for different keys is reduced, thus minimizing collisions.*/
        hash_value = (hash_value * PRIME + identifier[i]) % HASH_TABLE_SIZE;
    }
    return hash_value;
}

void createSymbolTable()
{
    // Dynamically Allocating memory for the symbol table
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
        {"EOF", TK_EOF}};

    for (int i = 0; i < NUM_KEYWORDS; i++)
    {
        // Add the keywords to the symbol table
        identifierNode *node = createSymbolNode(arr[i].keywordname, arr[i].tokenID);
        int index = calcHash(node->identifierName);
        insertToSymbolTable(node->identifierName, node->tokenID);
    }
}


// Function to create a new identifier node and allocate memory for the symbol table
identifierNode *createSymbolNode(char *identifierName, int tokenID)
{
    identifierNode *newN = (identifierNode *)malloc(sizeof(identifierNode));

    // Set the identifier name and token of the new node to the provided identifierName and tokenID
    newN->identifierName = identifierName;
    newN->tokenID = tokenID;

    
    newN->next = NULL; // Set the next pointer of the new node to NULL, as it is a new node
    return newN;
}

// Function to insert a new identifier and its corresponding token ID into the symbol table
int insertToSymbolTable(char *identifierName, int tokenID)
{
    // Calculate the hash index for the given identifier name
    int index = calcHash(identifierName);
    identifierNode *insertNode = createSymbolNode(identifierName, tokenID);

    
    identifierNode *temp = symbolTable[index]->head; // Retrieve the head of the linked list at the calculated hash index

    
    if (symbolTable[index]->size == 0)
    {
        /* If the linked list at given index is empty , make the current node the head of the linked list
         and increment the size of linked list */ 
        symbolTable[index]->head = insertNode;   
        symbolTable[index]->size++;
        return index;
    }
    else
    {
        // Traverse the linked list to find the last node
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = insertNode;// Insert the node at the end        
        symbolTable[index]->size++; // Increment the size of linked list
        return index;
    }
    return -1;
}

// Function to search the symbol table for a particular lexeme
int searchSymbolTable(char *identifierName)
{
    int index = calcHash(identifierName);
    identifierNode *curr = symbolTable[index]->head;
    while (curr != NULL)
    {
        if (strcmp(curr->identifierName, identifierName) == 0)
            return curr->tokenID; // return the tokenID found in the symbol table 
        else
            curr = curr->next;
    }
    return -1;
}

// function to search the symbol table for a particular lexeme , if dound return the tokenID else insert it into the symbol table
int checkTokenID(char *identifierName, int tokenID)
{

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

// Function to free memory allocated for the symbol table by freeing the memory associated with each node
void freeSymbolTable()
{

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {

        while (symbolTable[i]->head != NULL)
        {
            // Save the reference to the next node
            identifierNode *curr = symbolTable[i]->head;
            symbolTable[i]->head = curr->next;
            free(curr); // Free memory allocated for the current node
        }
        free(symbolTable[i]); // Free memory allocated for the symbol table entry at the current index
    }
}

