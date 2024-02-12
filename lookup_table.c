#include <stdio.h>
#include <string.h>
#include "lexer2.h"

#define NUM_KEYWORDS 28
#define HASH_TABLE_SIZE 127 // Prime Number

struct keyword kwtable[HASH_TABLE_SIZE];

int calculateHash(char *kwname)
{
    int prime = 31;
    int hash_value = 0;
    for (int i = 0; i < strlen(kwname); i++)
    {
        hash_value = (hash_value * prime + kwname[i]) % HASH_TABLE_SIZE;
        //hash_value = ((hash_value << 5) + hash_value) + kwname[i];
    }
    return hash_value;
}

int getKeyWordID(char *lexeme)
{

    int index = calculateHash(lexeme);
    if (kwtable[index].keywordname != NULL)
    {
        int original_index = index;
        int probe_num = 1;
        while(index<HASH_TABLE_SIZE && strcmp(kwtable[index].keywordname, lexeme) != 0)
        {
            index =(original_index + probe_num * probe_num) % HASH_TABLE_SIZE;
            probe_num++;
        }
        if(index<HASH_TABLE_SIZE) return kwtable[index].tokenID;       
    }

    return -1;
}

void initialize_table(struct keyword *kwtable){
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        kwtable[i].keywordname = NULL;
        kwtable[i].tokenID = -1;
    }
}

int lookUpTable()
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
        {"else", TK_ELSE}};

    initialize_table(kwtable);
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
            int probe_num = 1;
            int original_index = index;

            while (kwtable[index].keywordname != NULL)
            {
                index = (original_index + probe_num * probe_num) % HASH_TABLE_SIZE;
                probe_num++;

                if (index == original_index) 
                    break;
            }

            kwtable[index].keywordname = arr[i].keywordname;
            kwtable[index].tokenID = arr[i].tokenID;
            collision++;
        }
    }

    //printf("Collissions : %d  \n",collision);
}
