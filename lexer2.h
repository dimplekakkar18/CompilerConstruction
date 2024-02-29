#ifndef LEXER2_H
#define LEXER2_H
typedef struct token TOKEN;
struct token{
    int tokenId;
    int lineNo;
    char* lexeme;
};
typedef struct symbolTableLL
{
    struct identifierNode *head;
    int size;
} symbolTableLL;

typedef struct identifierNode
{
    struct identifierNode *next;
    char *identifierName;
    int tokenID;
} identifierNode;


enum TOKENS {
    TK_MAIN,
    TK_INT,
    TK_ID,
    TK_REAL,
    TK_ENDRECORD,
    TK_END,
    TK_FUNID,
    TK_SEM,
    TK_INPUT,
    TK_PARAMETER,
    TK_LIST,
    TK_SQL,
    TK_SQR,
    TK_OUTPUT,
    TK_RECORD,
    TK_UNION,
    TK_RUID,
    TK_COMMA,
    TK_TYPE,
    TK_COLON,
    TK_FIELDID,
    TK_GLOBAL,
    TK_ASSIGNOP,
    TK_DOT,
    TK_CALL,
    TK_WITH,
    TK_PARAMETERS,
    TK_WHILE,
    TK_OP,
    TK_CL,
    TK_IF,
    TK_THEN,
    TK_ELSE,
    TK_ENDIF,
    TK_READ,
    TK_WRITE,
    TK_PLUS,
    TK_MINUS,
    TK_MUL,
    TK_DIV,
    TK_RETURN,
    TK_NOT,
    TK_LT,
    TK_LE,
    TK_EQ,
    TK_GT,
    TK_GE,
    TK_NE,
    TK_NUM,
    TK_RNUM,
    TK_ENDUNION,
    TK_ENDWHILE,
    TK_AND,
    TK_OR,
    TK_DEFINETYPE,
    TK_AS,
    TK_ERROR,
    TK_EOF,
    EPSILON,
    TK_COMMENT  // Add TK_COMMENT at the end
};


struct keyword{
    char * keywordname;
    int tokenID; 
};
#endif 