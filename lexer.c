#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "lexer2.h"

#define MAX_BUFF_SIZE 1024

// global two buffers
char *buffer1, *buffer2;

// begin and finish pointers for the two buffers
int start, end;

// line number
int lineNo = 1;

int flag[] = {0,0};

int lexemeSize;

char* getError(){
    char* str = getLexeme();
    // printf("The lexical error : %s has happened in the line number %d\n", str, lineNo);
    return str;
}

void removeComments(char *test_file, char *clean_file)
{
    FILE *fp1 = fopen(test_file, "r");
    FILE *fp2 = fopen(clean_file, "w");
    char c;
    int flag=0;
    while ((c = fgetc(fp1)) != EOF)
    {
        
        if (flag==0 && c=='%'){  //comment begining
            flag=1;
        }
        else if(flag==0 && c!='%'){
            fputc(c, fp2);
        }
        else if(flag==1 && c=='\n'){
            flag=0;
            fputc(c,fp2);
        }
        else{

        }
    }
    fclose(fp1);
    fclose(fp2);

}

void initializeBuffers(){
    buffer1 = malloc(sizeof(char) * MAX_BUFF_SIZE);
    buffer2 = malloc(sizeof(char) * MAX_BUFF_SIZE);
    bzero(buffer1, MAX_BUFF_SIZE);  // initializes buffer with '\0'
    bzero(buffer2, MAX_BUFF_SIZE);
    start = 0;
    end = 0;
    lineNo = 1;
}

void loadBuffer(char* buffer, FILE* fp){
    int numBytes = fread(buffer, sizeof(char), MAX_BUFF_SIZE, fp);
    if(numBytes < MAX_BUFF_SIZE){
        buffer[numBytes] = EOF;
    }
}

char getCharFromBuffers(FILE* fp){
    end = end%(2*MAX_BUFF_SIZE);
    if(end==0 && !flag[0]){
        loadBuffer(buffer1, fp);
        flag[0] = 1;
    }
    if(end==MAX_BUFF_SIZE && !flag[1]){
        loadBuffer(buffer2, fp);
        flag[1] = 1;
    }
    if(end<MAX_BUFF_SIZE){
        return buffer1[end];
    }
    else{
        return buffer2[end-MAX_BUFF_SIZE];
    }
}

char* getLexeme(){
    char *lexeme = calloc((end>start?(end-start+1):(end+2*MAX_BUFF_SIZE-start+1)), sizeof(char));
    int i = start;
    int pos = 0;
    for(i = start, pos = 0; i!=end; pos++, i=(i+1)%(MAX_BUFF_SIZE*2))
    {
        lexeme[pos] = (i>=MAX_BUFF_SIZE) ? buffer2[i-MAX_BUFF_SIZE] : buffer1[i];
    }
    lexeme[pos]='\0';
    
    //refreshPtr();
    return lexeme;
}

void refreshPtr(){    
    if(start<MAX_BUFF_SIZE && end>=MAX_BUFF_SIZE)
    {
        flag[0]=0;
    }
    else if(start>=MAX_BUFF_SIZE && end<MAX_BUFF_SIZE){
        flag[1]=0;
    }
    // printf("%d %d\n",start,end);
    start = end;
}
int len(char* str){
    int i = 0;
    while(*(str+i)!='\0') i++;
    return i;
}

void print_token(enum TOKENS token) {
    switch(token) {
        case TK_ASSIGNOP:
            printf("TK_ASSIGNOP\n");
            break;
        case TK_COMMENT:
            printf("TK_COMMENT\n");
            break;
        case TK_FIELDID:
            printf("TK_FIELDID\n");
            break;
        case TK_ID:
            printf("TK_ID\n");
            break;
        case TK_NUM:
            printf("TK_NUM\n");
            break;
        case TK_RNUM:
            printf("TK_RNUM\n");
            break;
        case TK_FUNID:
            printf("TK_FUNID\n");
            break;
        case TK_RUID:
            printf("TK_RUID\n");
            break;
        case TK_WITH:
            printf("TK_WITH\n");
            break;
        case TK_PARAMETERS:
            printf("TK_PARAMETERS\n");
            break;
        case TK_END:
            printf("TK_END\n");
            break;
        case TK_WHILE:
            printf("TK_WHILE\n");
            break;
        case TK_UNION:
            printf("TK_UNION\n");
            break;
        case TK_ENDUNION:
            printf("TK_ENDUNION\n");
            break;
        case TK_DEFINETYPE:
            printf("TK_DEFINETYPE\n");
            break;
        case TK_AS:
            printf("TK_AS\n");
            break;
        case TK_TYPE:
            printf("TK_TYPE\n");
            break;
        case TK_MAIN:
            printf("TK_MAIN\n");
            break;
        case TK_GLOBAL:
            printf("TK_GLOBAL\n");
            break;
        case TK_PARAMETER:
            printf("TK_PARAMETER\n");
            break;
        case TK_LIST:
            printf("TK_LIST\n");
            break;
        case TK_SQL:
            printf("TK_SQL\n");
            break;
        case TK_SQR:
            printf("TK_SQR\n");
            break;
        case TK_INPUT:
            printf("TK_INPUT\n");
            break;
        case TK_OUTPUT:
            printf("TK_OUTPUT\n");
            break;
        case TK_INT:
            printf("TK_INT\n");
            break;
        case TK_REAL:
            printf("TK_REAL\n");
            break;
        case TK_COMMA:
            printf("TK_COMMA\n");
            break;
        case TK_SEM:
            printf("TK_SEM\n");
            break;
        case TK_COLON:
            printf("TK_COLON\n");
            break;
        case TK_DOT:
            printf("TK_DOT\n");
            break;
        case TK_ENDWHILE:
            printf("TK_ENDWHILE\n");
            break;
        case TK_OP:
            printf("TK_OP\n");
            break;
        case TK_CL:
            printf("TK_CL\n");
            break;
        case TK_IF:
            printf("TK_IF\n");
            break;
        case TK_THEN:
            printf("TK_THEN\n");
            break;
        case TK_ENDIF:
            printf("TK_ENDIF\n");
            break;
        case TK_READ:
            printf("TK_READ\n");
            break;
        case TK_WRITE:
            printf("TK_WRITE\n");
            break;
        case TK_RETURN:
            printf("TK_RETURN\n");
            break;
        case TK_PLUS:
            printf("TK_PLUS\n");
            break;
        case TK_MINUS:
            printf("TK_MINUS\n");
            break;
        case TK_MUL:
            printf("TK_MUL\n");
            break;
        case TK_DIV:
            printf("TK_DIV\n");
            break;
        case TK_CALL:
            printf("TK_CALL\n");
            break;
        case TK_RECORD:
            printf("TK_RECORD\n");
            break;
        case TK_ENDRECORD:
            printf("TK_ENDRECORD\n");
            break;
        case TK_ELSE:
            printf("TK_ELSE\n");
            break;
        case TK_AND:
            printf("TK_AND\n");
            break;
        case TK_OR:
            printf("TK_OR\n");
            break;
        case TK_NOT:
            printf("TK_NOT\n");
            break;
        case TK_LT:
            printf("TK_LT\n");
            break;
        case TK_LE:
            printf("TK_LE\n");
            break;
        case TK_EQ:
            printf("TK_EQ\n");
            break;
        case TK_GT:
            printf("TK_GT\n");
            break;
        case TK_GE:
            printf("TK_GE\n");
            break;
        case TK_NE:
            printf("TK_NE\n");
            break;
        case TK_ERROR:
            printf("TK_ERROR\n");
            break;
        default:
            printf("Unknown token\n");
            break;
    }
}

void printTokenInfo(TOKEN tk){
    if(tk.tokenId == TK_ERROR){
        // unknown symbol  
        // unknown pattern 
        // var id is having len > 20 - Done
        // field id is having len > 30 - Done
        if(len(tk.lexeme)==1 && (*tk.lexeme<'A' || *tk.lexeme>'Z')){
            printf("Line No %d : Error: Unknown Symbol <%s>\n", lineNo, tk.lexeme);
        }
        else{
            printf("Line no: %d : Error: Unknown pattern <%s>\n", lineNo, tk.lexeme);
        }
        return;
    }
    if(tk.tokenId==TK_COMMENT){
        printf("Line no. %d\tLexeme %-20s\tToken TK_COMMENT\n", lineNo++, tk.lexeme);
        return;
    }
    printf("Line no. %d\tLexeme %-20s\tToken ", lineNo, tk.lexeme);
    print_token(tk.tokenId);
}

TOKEN getToken(FILE *fp)
{
    // token to be returned
    TOKEN token;

    // declarations
    char c;
    int state = 0;
    char *lexeme;
    lexemeSize = 0;

    while (state >= 0)
    {
        c = getCharFromBuffers(fp);
        // increment lexemeSize
        lexemeSize++;
        switch (state)
        {
        // start state
        case 0:
            if(c=='<')
            {
                state=1;
                end++;
                break;
            }
            else if(c==' '|| c=='\t')
            {
                state=4;
                end++;
                break;
            }
            else if ( c == '\n'){
                end++;
                state=4;
                lineNo++;
                break;
            }
            else if((c=='a')||(c>='e'&& c<='z'))
            {
                state=5;
                end++;
                break;
            }
            else if(c=='b'|| c=='c' || c=='d')
            {
                state=6;
                end++;
                break;
            }
            else if( c>='0' && c<='9')
            {
                state=9;
                end++;
                break;
            }
            else if( c =='_' )
            {
                state=16;
                end++;
                break;
            }
            else if( c == '#')
            {
                state=19;
                end++;
                break;
            }
            else if (c == '[')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_SQL;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == ']')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_SQR;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == ',')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_COMMA;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == ';')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_SEM;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == ':')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_COLON;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == '.')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_DOT;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == '(')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_OP;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == ')')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_CL;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == '+')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_PLUS;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == '-')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_MINUS;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == '*')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_MUL;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == '/')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_DIV;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == '~')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_NOT;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else if (c == '>')
            {
                state=25;
                end++;
                break;
            }
            else if (c=='!')
            {
                state=26;
                end++;
                break;
            }
            else if ( c == '=')
            {
                state=27;
                end++;
                break;
            }
            else if ( c == '&')
            {
                state=21;
                end++;
                break;
            }
            else if ( c == '@')
            {
                state=23;
                end++;
                break;
            }
            else if ( c == '%'){
                state=28;
                end++;
                break;
            }
            else if( c == EOF){
                end++;
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
            else
            {                   
                end++;
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        case 1:
            if ( c == '-' )
            {
                state=2;
                end++;
                break;
            }
            else if ( c == '=')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_LE;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_LT;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
        case 2:
            if ( c== '-' ) 
            {
                state=3;
                end++;
                break;
            }
            else
            {
                end--;
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_LT;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }

        case 3:
            if ( c == '-')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_ASSIGNOP;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
            else 
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
                break;
            }
        
        case 4:
            if ( c == ' ' || c == '\t'){
                state=4;
                end++;
                break;
            }
            else if ( c == '\n')
            {
                state=4;
                end++;
                lineNo++;
                break;
            }
            else
            {
                refreshPtr();
                state=0;
                break;
            }
        case 5:
            if ( c >= 'a' && c<='z')
            {
                state=5;
                end++;
                break;
            }
            else 
            {
                char* lex = getLexeme(); //populate the token
                int id = searchSymbolTable(lex);
                if(id == -1){
                    token.lexeme = lex;
                    token.tokenId = TK_FIELDID;
                    token.lineNo = lineNo;
                }
                else{
                    token.lexeme = lex;
                    token.tokenId = id;
                    token.lineNo = lineNo;
                }
                refreshPtr();
                state = 0;
                return token;
                break;
            }
        case 6:
            if ( c >= 'a' && c <= 'z')
            {
                state=5;
                end++;
                break;
            }
            else if ( c >= '2' && c <= '7')
            {
                state = 7;
                end++;
                break;
            }
            else 
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_FIELDID;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
        case 7:
            if (c >= 'b' && c <= 'd')
            {
                state=7;
                end++;
                break;
            }
            else if (c >= '2' && c <= '7')
            {
                state = 8;
                end++;
                break;
            }
            else 
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_ID;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
        case 8 :
            if ( c >= '2' && c <= '7')
            {
                state = 8;
                end++;
                break;
            }
            else 
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_ID;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;   
            }
        
        case 9:
            if ( c >= '0' && c <= '9')
            {
                state=9;
                end++;
                break;
            }
            else if ( c == '.')
            {
                state = 10;
                end++;
                break;
            }
            else
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_NUM;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
        
        case 10:
            if ( c >= '0' && c <= '9')
            {
                state=11;
                end++;
                break;
            }
            else
            {
                end--;
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_NUM;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
        
        case 11:
            if ( c >= '0' && c <= '9')
            {
                state=12;
                end++;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }

        case 12 :
            if ( c == 'E')
            {
                state = 13;
                end++;
                break;
            }
            else
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_RNUM;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;
            }
        
        case 13:
            if ( c >= '0' && c <= '9')
            {
                state=14;
                end++;
                break;
            }
            else if ( c == '+' || c == '-')
            {
                state = 15;
                end++;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        case 14 :
            if ( c >= '0' && c <= '9')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_RNUM;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break;   
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        case 15 :
            if ( c >= '0' && c <= '9')
            {
                state=14;
                end++;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        case 16 :
            if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                state = 17;
                end++;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        case 17:
            if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                state = 17;
                end++;
                break;
            }
            else if ( c>='0' && c<='9' )
            {
                state=18;
                end++;
                break;
            }
            else
            {
                char* lex = getLexeme(); //populate the token
                int id = searchSymbolTable(lex);
                if(id == TK_MAIN){
                    token.lexeme = lex;
                    token.tokenId = TK_MAIN;
                    token.lineNo = lineNo;
                }
                else{
                    token.lexeme = lex;
                    token.tokenId = TK_FUNID;
                    token.lineNo = lineNo;
                }
                refreshPtr();
                state=0;
                return token;
                break; 
            }
        case 18:
            if ( c>='0' && c<='9' )
            {
                state=18;
                end++;
                break;
            }
            else
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_FUNID;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break; 
            }

        case 19: 
            if( c >= 'a' && c <= 'z')
            {
                state = 20;
                end++;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        
        case 20:
            if( c >= 'a' && c <= 'z')
            {
                state = 20;
                end++;
                break;
            }
            else
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_RUID;
                token.lineNo = lineNo;
                refreshPtr();
                state=0;
                return token;
                break; 
            }

        case 21:
            if( c == '&')
            {
                state = 22;
                end++;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }

        case 22:
            if( c == '&')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_AND;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        
        case 23:
            if ( c == '@')
            {
                state = 24;
                end++;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }

        case 24:
            if( c == '@')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_OR;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        case 25:
            if ( c == '=')
            {
                end++; // if in out function we take token from st to end-1
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_GE;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
            else 
            {
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_GT;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
        
        case 26:
            if ( c == '=')
            {
                end++;// st to end - 1 
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_NE;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        
        case 27:
            if ( c == '=')
            {
                end++;// st to end - 1 
                char* lex = getLexeme(); //populate the token
                token.lexeme = lex;
                token.tokenId = TK_EQ;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
            else
            {
                char* lex = getError(); //increment errorno
                refreshPtr();
                state=0;
                token.lexeme = lex;
                token.tokenId = TK_ERROR;
                token.lineNo = lineNo;
                return token;
            }
        case 28:
            if( c!='\n'){
                state = 28;
                end++;
                break;
            }
            else
            {
                end++;// st to end - 1 
                char* lex = malloc(1*sizeof(char));
                lex[0] = '%';
                token.lexeme = lex;
                token.tokenId = TK_COMMENT;
                token.lineNo = lineNo;
                refreshPtr();
                state = 0;
                return token;
                break;
            }
        }
    }
    return token;
}

int main()
{
    removeComments("./t1.txt","clean.txt");
    initializeBuffers();
    createSymbolTable();
    FILE *fp = fopen("./clean.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }
    int flag = 1;
    while (flag)
    {
        TOKEN token = getToken(fp);
        if (*token.lexeme == EOF){
            // printf("*****\n");
            break;
        }
        // if (token.tokenId == NUM){
        //     printf("%d\n", token.val.intValue);
        // } else if (token.tokenId == RNUM){
        //     printf("%f\n", token.val.floatValue);
        // }
        if(token.tokenId==TK_ID && len(token.lexeme)>20) printf("Line No %d: Error :Variable Identifier is longer than the prescribed length of 20 characters.\n",lineNo);
        else if (token.tokenId==TK_FIELDID && len(token.lexeme)>30) printf("Line No %d: Error :Field Identifier is longer than the prescribed length of 30 characters.\n",lineNo);
        else{
            checkTokenID(token.lexeme, token.tokenId);
            // printf("%d\n", checkTokenID(token.lexeme, token.tokenId));
            printTokenInfo(token); 
        }
        // printf("DO you want to continue? (1/0): ");
        // scanf("%d", &flag);
    }
    fclose(fp);
    return 0;
}




        





        






