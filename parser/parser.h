#include <stdio.h>
#include <parseDef.h>
#include <linkedList.h>
#include <stack.h>
#define numNTS 57
#define numRules 90
#define EPSILON 57//need to change acc

long long int follow[numNTS];
long long int first[numNTS];



void createGrammar(FILE * fp)
{

}

int addToSet(long long int* set, int term)
{
    long long int termval = ((long long)1)<<term;

    if(*set&termval)
        return 0;//this val already set
    
    *set |= termval;
    return 1;
}

int setContains(long long int set, int term)
{
    long long int termval = ((long long)1)<<term;
    if(set&termval)
        return 0
}

void propogateStack()
{

}

void generateFollow()
{
    int changed = 0;
    int changedNT[numNTS] = {0};
    LLNODE *grammar[numRules];
    stack * st = getStack();
    while(changed)
    for(int i = 0; i<numRules; i++)
    {
        LLNODE * node = grammar[i];
        
        while((node = node->next)!=NULL)
        {
            if(node->type == TERMINAL)
                continue;
            
            if(node->type == EPSILON)
                break;
            
            //only option for NT left
            if(node->next == NULL)
            {
                if(follow[node->type]==follow[i])
                    break;

                follow[node->type] |= follow[i];
                changed = 1;
                break;
            }
            //node next is not null
            if(node->next->type == TERMINAL)
            {
                if(addToSet(&follow[node->sym.nonterminal],node->next->sym.terminal));
                    changed = 1;
                continue;
            }

            if(setContains(follow[node->next->sym.nonterminal],EPSILON))
            {
                push(st,node->next->sym.nonterminal);
                continue;
            }
            //now just need to add follow of next into current
            follow[node->sym.nonterminal] |= follow[node->next->sym.nonterminal];
            changed = 1;
        }
    }
}

