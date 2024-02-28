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
    initializeBuffers();
    createSymbolTable();
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
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
                fp = fopen("clean.txt", "r"); 
                break; 
            case 2:
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
                break;  
            case 3:
                create_hashTable();
                ruleLL *rules = createGrammar("grammar.csv");
                // print_rules(rules);
                token_set *first_sets = malloc(sizeof(token_set) * NUM_NONTERMINALS);
                token_set *follow_sets = malloc(sizeof(token_set) * NUM_NONTERMINALS);
                computeFirst(first_sets,rules);
                printf("**************************** DEBUG 1 \n"); 
                // for (int i = 0; i < NUM_NONTERMINALS; i++)
                // {
                //     printf("First(%s): ", nonterminals[i]);
                //     printSet(&first_sets[i]);
                //     printf("\n");
                // }
                generateFollow(rules,follow_sets,first_sets);
                printf("**************************** DEBUG 2 \n"); 
                // for (int i = 0; i < NUM_NONTERMINALS; i++)
                // {
                //     printf("Follow(%s): ", nonterminals[i]);
                //     printSet(&follow_sets[i]);
                //     printf("\n");
                // }
                int** pt = makeParseTable2(first_sets,follow_sets,rules);     
                printf("**************************** DEBUG 3 \n");            
                Tree * parseTree = makeParseTree(pt, fp); 
                printf("**************************** DEBUG 4 \n"); 
                fp = fopen(argv[2], "w"); 
                //bool fl = true; 

                //if(fl == true) 
                printTree(parseTree); 
                break; 

        }
    }
    fclose(fp); 
    return 0; 

}