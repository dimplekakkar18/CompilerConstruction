// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#include "parser.h"
#include "linkedList.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "lexer.h"
#include <stdbool.h> 
#include "treeADT.h"
#include <time.h>

int main(int argc, char * argv[]){
    printf("FIRST and FOLLOW set automated\n");
    printf("Both lexical and syntax analysis modules implemented\n");
    printf("modules 1,2,3 and 4 work with all the testcases \n");
    int choice = 0; 
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }
    clock_t start_time, end_time;
    double total_CPU_time, total_CPU_time_in_seconds;

    start_time = clock();
    int flag = 1;

    while(1){
        printf("Enter choice: \n"); 
        scanf("%d",&choice);
        switch(choice)
        {
            case 0: 
                printf("Exiting...\n"); 
                return 0; 
                break; 
            case 1:
                removeComments(argv[1],"clean.txt");
                fp = NULL;
                printf("\n");
                break; 
            case 2:
                lineNo = 1;
                initializeBuffers();
                createSymbolTable();
                fp = fopen(argv[1], "r"); 
                if(fp == NULL)
                {
                    printf("Error opening file\n");
                    return -1;
                }
                while (flag)
                    {
                        createSymbolTable();
                        TOKEN token = getToken(fp);
                        if (*token.lexeme == EOF){
                            // printf("*****\n");
                            break;
                        }

                        checkTokenID(token.lexeme, token.tokenId);
                        printTokenInfo(token); 
                    } 
                    destroySymbolTable();
                break;  
            case 3:
                lineNo = 1;
                createSymbolTable();
                create_hashTable();
                fp = fopen(argv[1], "r"); 
                if(fp == NULL)
                {
                    printf("Error opening file\n");
                    return -1;
                }
                fseek(fp,0,SEEK_SET);
                initializeBuffers();
                
                ruleLL *rules = createGrammar("grammar.csv");
                long long int *first_sets = malloc(sizeof(long long int) * NUM_NONTERMINALS);
                long long int *follow_sets = malloc(sizeof(long long int) * NUM_NONTERMINALS);
                computeFirst(first_sets,rules);

                generateFollow(rules,follow_sets,first_sets);
 
                int** pt = makeParseTable(first_sets,follow_sets,rules);                
                Tree * parseTree = parseInputSourceCode(rules,pt,fp); 
                fclose(fp);
                fp = fopen(argv[2], "w"); 
                if(fp == NULL)
                {
                    printf("Error opening file\n");
                    return -1;
                }
                
                printParseTree(parseTree,fp); 
                printf("\n");
                fclose(fp);
                freeGrammar(rules);
                destroySymbolTable(); 
                break; 
            case 4:
                end_time = clock();
                total_CPU_time = (double) (end_time - start_time);
                total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
                printf("Total CPU time: %f\n", total_CPU_time);
                printf("Total CPU time in seconds: %f\n", total_CPU_time_in_seconds);
                break;

        }
    }
    return 0; 

}