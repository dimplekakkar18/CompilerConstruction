#ifndef PARSER_DEF_H
#define PARSER_DEF_H

#include "../lexer2.h"
#define NUMRULES 90
#define HASH_TABLE_SIZE 487
#define PRIME 31
#define NUM_NONTERMINALS 50
#define NUM_RULES 90
#define NUM_TERMINALS 56

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
    __moreRecID__,
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
}SYMBOLTYPE;


typedef struct hash_ele
{
    enum SYMBOLTYPE type;
    SYMBOL sym;
}hash_ele;



hash_ele hash_table[HASH_TABLE_SIZE];
int calculateHash(char *word);
int addnonTerm();
int addTerm();
void create_hashTable();
int getIndex(char *tok);

#endif