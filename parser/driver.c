#include "parser.h"
#include "linkedList.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "set.h"
#include "../lexer.h"
#include <stdbool.h> 
#include "treeADT.h"
int main(int argc, char * argv[]){
    int choice = 0; 
    FILE *fp = fopen(argv[1], "r");
    FILE * errorfile = fopen("errorfile.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }
    if (errorfile == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }
    int flag = 1;

    while(1){
        printf("Enter choice: \n"); 
        scanf("%d",&choice);
        switch(choice)
        {
            case 0: 
                printf("Exiting...\n"); 
                fclose(fp); 
                return 0; 
                break; 
            case 1:
                removeComments(argv[1],"clean.txt");
                // fp = fopen("clean.txt", "r"); 
                fclose(fp);
                fp = NULL;
                break; 
            case 2:
            
                initializeBuffers();
                createSymbolTable();
                fp = fopen("clean.txt", "r"); 
                if(fp == NULL)
                {
                    printf("Error opening file\n");
                    return -1;
                }
                while (flag)
                //for(int i = 0;i<20;i++)
                    {
                        createSymbolTable();
                        TOKEN token = getToken(fp, errorfile);
                        if (*token.lexeme == EOF){
                            // printf("*****\n");
                            break;
                        }
                        // if (token.tokenId == NUM){
                        //     printf("%d\n", token.val.intValue);
                        // } else if (token.tokenId == RNUM){
                        //     printf("%f\n", token.val.floatValue);
                        // }
                        // if(token.tokenId==TK_ID && len(token.lexeme)>20) fprintf(errorfile, "Line No %d: Error :Variable Identifier is longer than the prescribed length of 20 characters.\n",lineNo);
                        // else if (token.tokenId==TK_FIELDID && len(token.lexeme)>30) fprintf(errorfile, "Line No %d: Error :Field Identifier is longer than the prescribed length of 30 characters.\n",lineNo);
                        // else{
                        checkTokenID(token.lexeme, token.tokenId);
                        // printf("%d\n", checkTokenID(token.lexeme, token.tokenId));
                        printTokenInfo(token, errorfile); 
                        // }
                        // printf("DO you want to continue? (1/0): ");
                        // scanf("%d", &flag);
                    } 
                    
                break;  
            case 3:
                lineNo = 1;
                createSymbolTable();
                create_hashTable();
                if(fp != NULL)
                    fseek(fp, 0, SEEK_SET);
                else
                    fp = fopen("clean.txt", "r"); 
                if(fp == NULL)
                {
                    printf("Error opening file\n");
                    return -1;
                }
                initializeBuffers();
                // printf("DEBUB  %ld",ftell(fp));
                
                ruleLL *rules = createGrammar("grammar.csv");
                // print_rules(rules);
                token_set *first_sets = malloc(sizeof(token_set) * NUM_NONTERMINALS);
                token_set *follow_sets = malloc(sizeof(token_set) * NUM_NONTERMINALS);
                computeFirst(first_sets,rules);
                // for (int i = 0; i < NUM_NONTERMINALS; i++)
                // {
                //     printf("First(%s): ", nonterminals[i]);
                //     printSet(&first_sets[i]);
                //     printf("\n");
                // }
                generateFollow(rules,follow_sets,first_sets);
                // for (int i = 0; i < NUM_NONTERMINALS; i++)
                // {
                //     printf("Follow(%s): ", nonterminals[i]);
                //     printSet(&follow_sets[i]);
                //     printf("\n");
                // }
                int** pt = makeParseTable2(first_sets,follow_sets,rules);     
                printf("**************************** DEBUG 3 \n");            
                Tree * parseTree = makeParseTree(rules,pt,fp, errorfile,first_sets); 
                printf("**************************** DEBUG 4************* \n"); 
                fclose(fp);
                fp = fopen(argv[2], "w"); 
                if(fp == NULL)
                {
                    printf("Error opening file\n");
                    return -1;
                }
                //bool fl = true; 

                //if(fl == true) 
                printTree(parseTree); 
                printf("\n");
                fclose(fp);
                fclose(errorfile); 
                break; 

        }
    }
    return 0; 

}