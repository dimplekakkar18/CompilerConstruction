#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "lexer2.h"

// global buffer size
int bufferSize;

// global two buffers
char *buf1, *buf2;

// begin and finish pointers for the two buffers
int start, end;

// line number
int lineNo = 1;


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
        else if(flag==1 && c=='/n'){
            flag=0;
            fputc(c,fp2);
        }
        else{

        }
    }
    fclose(fp1);
    fclose(fp2);

}



TOKEN getToken(FILE *fp)
{
    // token to be returned
    TOKEN token;

    // declarations
    char c;
    int state = 0;
    char *lexeme;

    while (state >= 0)
    {
        // get character from buffer
        c = getCharFromBuffers(fp);
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
            else if(c==' '|| c=='/t')
            {
                state=4;
                end++;
                break;
            }
            else if ( c == '/n'){
                end++;
                state=4;
                lineNo++;
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
                state=32;
                end++;
                break;
            }
            else if( c == '# ')
            {
                state=37;
                end++;
                break;
            }
            else if (c == '[')
            {
                state=40;
                end++;
                break;
            }
            else if (c == ']')
            {
                state=41;
                end++;
                break;
            }
            else if (c == ',')
            {
                state=42;
                end++;
                break;
            }
            else if (c == ';')
            {
                state=43;
                end++;
                break;
            }
            else if (c == ':')
            {
                state=44;
                end++;
                break;
            }
            else if (c == '.')
            {
                state=45;
                end++;
                break;
            }
            else if (c == '(')
            {
                state=46;
                end++;
                break;
            }
            else if (c == ')')
            {
                state=47;
                end++;
                break;
            }
            else if (c == '+')
            {
                state=48;
                end++;
                break;
            }
            else if (c == '-')
            {
                state=49;
                end++;
                break;
            }
            else if (c == '*')
            {
                state=50;
                end++;
                break;
            }
            else if (c == '/')
            {
                state=51;
                end++;
                break;
            }
            else if (c == '~')
            {
                state=52;
                end++;
                break;
            }
            else if (c == '>')
            {
                state=53;
                end++;
                break;
            }
            else if (c=='!')
            {
                state=54;
                end++;
                break;
            }
            else if ( c == '=')
            {
                state=55;
                end++;
                break;
            }
            else if ( c == '&')
            {
                state=56;
                end++;
                break;
            }
            else if ( c == '@')
            {
                state=57;
                end++;
                break;
            }
            else
            {                   //write code

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
                getlexeme();
                refreshPtr();
                state=0;
                break;
            }
            else
            {
                getlexeme();
                refreshPtr();
                state=0;
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
                getlexeme();
                refreshPtr();
                state=0;
                break;
            }

        case 3:
            if ( c == '-')
            {
                getlexeme(); //populate the token
                refreshPtr();
                state=0;
                break;
            }
            else 
            {
                getError(); //increment errorno
                refreshPtr();
                state=0;
                break;
            }
        
        case 4:
            if ( c == ' ' || c == '/t'){
                state=4;
                end++;
                break;
            }
            else if ( c == '/n')
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
                getlexeme();
                refreshPtr();
                state = 0;
                break;
            }
        case 6:
            if ( c >= 'a' && c <= 'z')
            {
                state=5;
                end++;
                break;
            }
            else if ( c >= 2 && c <= 7)
            {
                state = 7;
                end++;
                break;
            }
            else 
            {
                getlexeme();
                refreshPtr();
                state = 0;
                break;
            }
        case 7:
            if ( c >= 'b' && c <= 'd')
            {
                state=7;
                end++;
                break;
            }
            else if ( c >= 2 && c <= 7 )
            {
                state = 8;
                end++;
                break;
            }
            else 
            {
                getlexeme();
                refreshPtr();
                state=0;
                break;
            }
        case 8 :
            if ( c >= 2 && c <= 7)
            {
                state = 8;
                end++;
                break;
            }
            else 
            {
                getlexeme();
                refreshPtr();
                state=0;
                break;   
            }
        
        case 9:
            if ( c >= 0 && c <= 9)
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
                getlexeme();
                refreshPtr();
                state=0;
                break;
            }
        
        case 10:
            if ( c >= 0 && c <= 9)
            {
                state=11;
                end++;
                break;
            }
            else
            {
                end--;
                getlexeme();
                refreshPtr();
                state = 0;
                break;
            }
        
        case 11:
            if ( c >= 0 && c <= 9)
            {
                state=12;
                end++;
                break;
            }
            else
            {
                getError();
                refreshPtr();
                state=0;
                break;
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
                getlexeme();
                refreshPtr();
                state=0;
                break;
            }
        
        case 13:
            if ( c >= 0 && c <= 9)
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
                getError();
                refreshPtr();
                state=0;
                break;
            }
        case 14 :
            if ( c >= 0 && c <= 9)
            {
                getlexeme();
                refreshPtr();
                state=0;
                break;   
            }
            else
            {
                getError();
                refreshPtr();
                state=0;
                break;
            }
        case 15 :
            if ( c >= 0 && c <= 9)
            {
                state=14;
                end++;
                break;
            }
            else
            {
                getError();
                refreshPtr();
                state=0;
                break;
            }
        case 16 :


        



















        }
    }
}