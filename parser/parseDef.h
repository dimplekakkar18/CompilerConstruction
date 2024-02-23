#include "../lexer2.h"
#define NUMRULES 91
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
    __A__
}NONTERMINAL;


typedef union SYMBOL{
    TOKENS terminal; 
    NONTERMINAL nonterminal; 
}SYMBOL;


typedef enum SYMBOLTYPE{
    TERMINAL, 
    NON_TERMINAL, 
    EPSILON,
    //NONE,
}SYMBOLTYPE;

ruleLL * grammar[NUMRULES]; 




