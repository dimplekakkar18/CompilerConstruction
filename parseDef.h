// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#ifndef PARSER_DEF_H
#define PARSER_DEF_H
#include "lexerDef.h"
#include "set.h"
#include <stdio.h>
#define NUMRULES 90
#define HASH_TABLE_SIZE 487
#define PRIME 31
#define NUM_NONTERMINALS 50
#define NUM_RULES 90
#define NUM_TERMINALS 59
#define END_CODE 61 // num_terminals +2

#define STARTSYMBOL __program__

typedef enum NONTERMINAL
{
    __program__,
    __otherFunctions__,
    __mainFunction__,
    __stmts__,
    __function__,
    __input_par__,
    __output_par__,
    __parameter_list__,
    __dataType__,
    __primitiveDatatype__,
    __constructedDatatype__,
    __remaining_list__,
    __returnStmt__,
    __recOrDefType__,
    __typeDefinition__,
    __typeDefinitions__,
    __fieldDefinitions__,
    __fieldDefinition__,
    __moreFields__,
    __declarations__,
    __declaration__,
    __global_or_not__,
    __otherStmts__,
    __stmt__,
    __assignmentStmt__,
    __SingleOrRecId__,
    __option_single_constructed__,
    __funCallStmt__,
    __outputParameters__,
    __inputParameters__,
    __iterativeStmt__,
    __conditionalStmt__,
    __ioStmt__,
    __arithmeticExpression__,
    __term__,
    __t1__,
    __t0__,
    __factor__,
    __f1__,
    __f0__,
    __booleanExpression__,
    __logicalOp__,
    __relationalOp__,
    __var__,
    __optionalReturn__,
    __idList__,
    __more_ids__,
    __definetypestmt__,
    __A__,
    __optelse__

}NONTERMINAL;

typedef union SYMBOL{
    enum TOKENS terminal; 
    NONTERMINAL nonterminal; 
}SYMBOL;


typedef enum SYMBOLTYPE{
    TERMINAL, 
    NON_TERMINAL, 
    __EPSILON,
    NONE,
    __ENDCODE,
}SYMBOLTYPE;


typedef struct hash_ele
{
    enum SYMBOLTYPE type;
    SYMBOL sym;
}hash_ele, stackEle, tree_ele;


extern char* nonterminals[NUM_NONTERMINALS]; 
extern char* terminals[NUM_TERMINALS]; 
extern hash_ele hash_table[HASH_TABLE_SIZE]; 

#endif