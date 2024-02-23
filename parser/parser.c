#include "parseDef.h"
#include "linkedList.c"
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_NONTERMINALS 50 
#define NUM_TERMINALS 56
#define PRIME 853 
#define HASH_TABLE_SIZE 1024

char *nonterminals[NUM_NONTERMINALS] = {
    "<program>",
    "<otherFunctions>",
    "<mainFunction>",
    "<stmts>",
    "<function>",
    "<input_par>",
    "<output_par>",
    "<parameter_list>",
    "<dataType>",
    "<primitiveDatatype>",
    "<constructedDatatype>",
    "<remaining_list>",
    "<returnStmt>",
    "<recOrDefType>",
    "<typeDefinition>",
    "<typeDefinitions>",
    "<fieldDefinitions>",
    "<fieldDefinition>",
    "<moreFields>",
    "<declarations>",
    "<declaration>",
    "<global_or_not>",
    "<otherStmts>",
    "<stmt>",
    "<assignmentStmt>",
    "<SingleOrRecId>",
    "<moreRecID>",
    "<funCallStmt>",
    "<outputParameters>",
    "<inputParameters>",
    "<iterativeStmt>",
    "<conditionalStmt>",
    "<ioStmt>",
    "<arithmeticExpression>",
    "<term>",
    "<t1>",
    "<t0>",
    "<factor>",
    "<f1>",
    "<f0>",
    "<booleanExpression>",
    "<logicalOp>",
    "<relationalOp>",
    "<var>",
    "<optionalReturn>",
    "<idList>",
    "<more_ids>",
    "<definetypestmt>",
    "<A>",
    "<optelse>"};

char *terminals[NUM_TERMINALS] = {
    "TK_MAIN",
    "TK_INT",
    "TK_ID",
    "TK_REAL",
    "TK_ENDRECORD",
    "TK_END",
    "TK_FUNID",
    "TK_SEM",
    "TK_INPUT",
    "TK_PARAMETER",
    "TK_LIST",
    "TK_SQL",
    "TK_SQR",
    "TK_OUTPUT",
    "TK_RECORD",
    "TK_UNION",
    "TK_RUID",
    "TK_COMMA",
    "TK_TYPE",
    "TK_COLON",
    "TK_FIELDID",
    "TK_GLOBAL",
    "TK_ASSIGNOP",
    "TK_DOT",
    "TK_CALL",
    "TK_WITH",
    "TK_PARAMETERS",
    "TK_WHILE",
    "TK_OP",
    "TK_CL",
    "TK_IF",
    "TK_THEN",
    "TK_ELSE",
    "TK_ENDIF",
    "TK_READ",
    "TK_WRITE",
    "TK_PLUS",
    "TK_MINUS",
    "TK_MUL",
    "TK_DIV",
    "TK_RETURN",
    "TK_NOT",
    "TK_LT",
    "TK_LE",
    "TK_EQ",
    "TK_GT",
    "TK_GE",
    "TK_NE",
    "TK_NUM",
    "TK_RNUM",
    "TK_ENDUNION",
    "TK_ENDWHILE",
    "TK_AND",
    "TK_OR",
    "TK_DEFINETYPE",
    "TK_AS"};

ruleLL * createGrammar(FILE * fp,hash_ele * hash_table)
{
    char buffer[128];
    struct LLNode * lhs;
    struct LLNode * rhs; 
    ruleLL * grammar = (ruleLL *) malloc(sizeof(ruleLL) * NUMRULES);

    if (fp == NULL)
    {
        printf("Error opening file\n");
    }

    //Allocate memory for each rule
    for(int i=0; i<NUMRULES; i++)
    {
        grammar[i] = createLL();
    }

    int i = 0; 
    char delim[] = ",\n";

    while (fgets(buffer, 128, fp) != NULL)
    {
        
        char * tok = strtok(buffer, delim); //Just extracting the lhs from each rule 
        
        int index = calculateHash(tok); 

        if (hash_table[index].type == NON_TERMINAL)
        {
            lhs = createNewNode(hash_table[index].sym, NON_TERMINAL); 
            addNewNode(lhs,grammar[i]);
        }
        else{
            printf("Error: rule starts with a terminal \n");
        }

        tok = strtok(NULL, delim); //NULL in the first entry means it'll start tokenizing from where it left off, i.e RHS 
        while (tok != NULL)
        {
            tok = trim(tok);
            int index = calculateHash(tok);
            rhs = createNewNode(hash_table[index].sym, hash_table[index].type);
            addNewNode(rhs,grammar[i]);

            tok = strtok(NULL, delim);
        }
        i++;
    }
    fclose(fp);
    
    return grammar;
}

// hash function
int calculateHash(char *word)
{
    int hash_value = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash_value = (hash_value * PRIME + word[i]) % HASH_TABLE_SIZE;
        // hash_value = ((hash_value << 5) + hash_value) + kwname[i];
    }
    return hash_value;
}

hash_ele *create_hashTable()
{

    hash_ele * hash_table = (hash_ele * )malloc((NUM_NONTERMINALS + NUM_TERMINALS) * sizeof(hash_ele)); 

    int num_collisions = 0;

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hash_table[i].type = NONE;
    }

    for (int i = 0; i < NUM_NONTERMINALS; i++)
    {
        int index = calculateHash(nonterminals[i]);

        if (hash_table[index].type == NONE)
        {
            hash_table[index].type = NON_TERMINAL;
            hash_table[index].sym.nonterminal = i;
        }

        else
        {
            int probe = 1;
            int newIndex;
            while (1)
            {
                num_collisions++;
                newIndex = (index + probe * probe) % HASH_TABLE_SIZE;
                if (hash_table[newIndex].type == NONE)
                {
                    hash_table[newIndex].type = NON_TERMINAL;
                    hash_table[newIndex].sym.nonterminal = i;
                    break;
                }
                probe++;
            }
        }
    }

    for (int i = 0; i < NUM_TERMINALS; i++)
    {
        int index = calculateHash(terminals[i]);

        if (hash_table[index].type == NONE)
        {
            hash_table[index].type = TERMINAL;
            hash_table[index].sym.terminal = i;
        }

        else
        {
            int probe = 1;
            int newIndex;
            while (1)
            {
                num_collisions++;
                newIndex = (index + probe * probe) % HASH_TABLE_SIZE;
                if (hash_table[newIndex].type == NONE)
                {
                    hash_table[newIndex].type = TERMINAL;
                    hash_table[newIndex].sym.terminal = i;
                    break;
                }
                probe++;
            }
        }
    }

    char *eps = "EPSILON";
    int eps_index = calculateHash(eps);
    if (hash_table[eps_index].type == NONE)
    {
        hash_table[eps_index].type = EPSILON;
    }
    else
    {

        int probe = 1;
        int newIndex;
        while (1)
        {
            num_collisions++;
            newIndex = (eps_index + probe * probe) % HASH_TABLE_SIZE;
            if (hash_table[newIndex].type == NONE)
            {
                hash_table[newIndex].type = EPSILON;
                break;
            }
            probe++;
        }
    }
    return hash_table; 
}



