#include "parseDef.h"
#include "linkedList.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "set.h"

// #define NUM_NONTERMINALS 50
// #define NUM_TERMINALS 56
// #define PRIME 853
// #define HASH_TABLE_SIZE 1024
// long long int follow[NUM_NONTERMINALS];
// long long int first[NUM_NONTERMINALS];

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

Element itoe (int i)
{
    Element e;
    e.int_value = i;
    return e;
}
int kthBitSet(long long int* nullable, int k){
    return ((*nullable)&(1LL<<(k)))!=0;
}
void setKthBit(long long int* n,int k){
    *n=((((long long int)1)<<k)|(*n));
}

char *trim(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
        {
            str[i] = '\0';
            break;
        }
        i++;
    }
    return str;
}

ruleLL *createGrammar(char* grammar_file, hash_ele *hash_table)
{
    FILE* fp = fopen(grammar_file, "r");
    char buffer[128];
    struct LLNode *lhs;
    struct LLNode *rhs;
    ruleLL *grammar = (ruleLL *)malloc(sizeof(ruleLL) * NUMRULES);

    if (fp == NULL)
    {
        printf("Error opening file\n");
    }

    // Allocate memory for each rule
    for (int i = 0; i < NUMRULES; i++)
    {
        grammar[i] = *createLL();
    }
    int i = 0;
    char delim[] = ",\n";

    while (fgets(buffer, 128, fp) != NULL)
    {

        char *tok = strtok(buffer, delim); // Just extracting the lhs from each rule

        int index = getIndex(tok);

        if (hash_table[index].type == NON_TERMINAL)
        {
            lhs = createNewNode(hash_table[index].sym, NON_TERMINAL);
            addNewNode(lhs, &grammar[i]);
        }
        else
        {
            printf("Error: rule starts with a terminal \n");
        }

        tok = strtok(NULL, delim); // NULL in the first entry means it'll start tokenizing from where it left off, i.e RHS
        while (tok != NULL)
        {
            tok = trim(tok);
            int index = getIndex(tok);
            rhs = createNewNode(hash_table[index].sym, hash_table[index].type);
            addNewNode(rhs, &grammar[i]);
            tok = strtok(NULL, delim);
        }
        i++;
    }
    fclose(fp);

    return grammar;
}
// hash function


int addToSet(token_set* sets, int term)
{
    long long int termval = ((long long)1) << term;

    if (sets->set & termval)
        return 0; // this val already set

    sets->set |= termval;
    return 1;
}

int setContains(token_set* sets, int term)
{
    long long int termval = ((long long)1) << term;
    if (sets->set & termval)
        return 1;
    else
        return 0;
}

void propogateStackFollow(stack *st, token_set* follow, int * changed)
{
    int temp = pop(st);
    while (st->count > 0)
    {
        int temp2 = pop(st);
        if((follow[temp2].set | follow[temp].set) != follow[temp2].set)
        {
            printf("DEBUGGER*************\n");
            *changed = 1; // setting changed
            //printf("flagged at propogate stack\n");
        }
        follow[temp2].set |= follow[temp].set;
        temp = temp2;
    }
}
void computeFirst(token_set *firstSet, ruleLL* rules)
{
    for (int i = 0; i < NUM_NONTERMINALS; i++)      // all the firstsets are init to 0 (empty set)
    {
        firstSet[i].set = 0;
    }
    int isDone[NUM_RULES];                          // isDone means we are done with that rule
    long long int nullable = 0;                     // the non-terminals which are nullable have the bit set
    for(int i = 0; i < NUM_RULES; i++){
        isDone[i] = 0;
    }
    for(int i = 0; i < NUM_RULES; i++){
        if(rules[i].head->next->type==__EPSILON){               // RHS is EPSILON
            addToken(&firstSet[rules[i].head->sym.nonterminal], EPSILON);   // include EPSILON in first(LHS)
            setKthBit(&nullable, rules[i].head->sym.nonterminal);            // LHS is a nullable non-terminal
            isDone[i] = 1;
            // printf("%lld******************* %d \n", nullable, i);

            // printf("***** %d %lld %lld %d\n", i, nullable, (nullable&(((long long int)1)<<rules[i].head->tnt.nonterm)), rules[i].head->tnt.nonterm);
            // printf("*********%d %d %lld\n", i, rules[i].head->tnt.nonterm, nullable);
        }
        else if(rules[i].head->next->type==TERMINAL){    // RHS is a TERMINAL
            // printf("***** %d %d*******\n", i, rules[i].head->next->tnt.tok);
            addToken(&firstSet[rules[i].head->sym.nonterminal], rules[i].head->next->sym.terminal);   // include this TERMINAL in first(LHS)
            isDone[i] = 1;
        }
    }
    // printf("%lld\n",nullable);
    // printf("%d\n", (nullable&(1LL<<(35)))!=0);
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        // printf("***DEBUGGER %d %d***\n", i, kthBitSet(&nullable, i)!=0);
    }
    // compute nullable
    long long int temp = 0;
    int cnt = 0;
    while(temp!=nullable){
        temp = nullable;
        for(int i = 0; i < NUM_RULES; i++){
            if(!isDone[i]){                                     // this rule is not processed
                LLNODE* node = rules[i].head;
                LLNODE* temp1 = node;
                node = node->next;                              // node points at RHS
                while(node!=NULL){
                    if(node->type==TERMINAL){
                        isDone[i] = 1;
                        break;
                    }
                    else{
                        if(!kthBitSet(&nullable, node->sym.nonterminal)){            // if in RHS there are non-terminal which are yet not nullable, we cannot go ahead with them
                            break;
                        }
                    }
                    node = node->next;
                }
                if(node==NULL){
                    isDone[i] = 1;
                    setKthBit(&nullable, temp1->sym.nonterminal);         // if we have reached the end it means this LHS non term is nullable
                }
            }
        }
    }
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        if(kthBitSet(&nullable, i)){
            addToken(&firstSet[i], EPSILON);
        }
    }
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        // printf("***DEBUGGER %d %d***\n", i, kthBitSet(&nullable, i)!=0);
    }
    //create adjacency list
    long long int adj[NUM_NONTERMINALS];   
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        adj[i] = 0;
    }

    for(int i = 0; i < NUM_RULES; i++){
        // if(!isDone[i]){         // none of A->e , A->T, A->nullable, a->nullable->Terminal => stuck at a non-nullable non-terminal
            LLNODE *node = rules[i].head;
            LLNODE* temp = node;
            node = node->next;
            if(node->type==__EPSILON) continue;
            if(node->type==TERMINAL) continue;
            while(node!=NULL){
                if(node->type==TERMINAL){
                    break;
                }
                else if(!kthBitSet(&nullable, node->sym.nonterminal)){  // non nullable
                    setKthBit(&adj[temp->sym.nonterminal], node->sym.nonterminal);
                    break;
                }
                setKthBit(&adj[temp->sym.nonterminal], node->sym.nonterminal);  // nullable
                node = node->next;
            }
        // }
    }
    // for(int i = 0; i < NUM_NONTERMINALS; i++){
    //     for(int j = 0; j < NUM_NONTERMINALS; j++){
    //         if(kthBitSet(&adj[i], j))
    //             printf("%s -> %s\n", nonterminals[i], nonterminals[j]);
    //     }
    // }
    // do topoSort
    int n = NUM_NONTERMINALS;
    int inDegree[n];
    for(int i = 0; i < n; i++){
        inDegree[i]= 0;
    }
    int itr = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < NUM_NONTERMINALS; j++){
            if(kthBitSet(&adj[i], j)){
                inDegree[j]++;
            }
        }
    }
    Queue* q = createQueue();
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        // printf("%d %d\n", i, inDegree[i]);
        if(inDegree[i]==0){
            enqueue(q, itoe(i));
            // printf("%d\n", front(q)->int_value);
        }
    }
    int topo[NUM_NONTERMINALS];
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        topo[i] = 0;
    }
    while(!isEmptyQ(q)){
        int node = front(q)->int_value;
        dequeue(q);
        topo[itr++] = node;
        // printf("%d\n", itr);
        for(int it = 0; it < NUM_NONTERMINALS; it++){
            if(kthBitSet(&adj[node], it)){
                inDegree[it]--;
                if(inDegree[it]==0)  enqueue(q, itoe(it));
            }
        }
    }
    destroyQueue(q);
    // compute the first in this order
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        // printf("%s\n", nonterminals[topo[i]]);
    }
    for(int i = NUM_NONTERMINALS-1; i >= 0; i--){
        for(int j = 0; j < NUM_RULES; j++){
            LLNODE* node = rules[j].head;             // node points to lhs
            LLNODE* temp1 = node;
            if(node->sym.nonterminal!=topo[i]) continue;
            node = node->next;                                   // node points to rhs
            if(node->type==__EPSILON){
                continue;
            }
            else if(node->type==TERMINAL){
                continue;
            }
            else{
                while(node!=NULL && node->type==NON_TERMINAL && kthBitSet(&nullable, node->sym.nonterminal)){       //nullable
                    token_set temp = firstSet[node->sym.nonterminal];                       
                    removeToken(&temp, EPSILON);                                     
                    firstSet[temp1->sym.nonterminal].set |= temp.set;       
                    node = node->next;
                }
                if(node!=NULL && node->type==NON_TERMINAL){             // reached a non-nullable => include the first of RHS into first of LHS
                    token_set temp = firstSet[node->sym.nonterminal];                       
                    removeToken(&temp, EPSILON);                                     
                    firstSet[temp1->sym.nonterminal].set |= temp.set;       
                }                     
                else if(node!=NULL){
                    firstSet[temp1->sym.nonterminal].set |= (1LL<<(node->sym.terminal));
                }          
            }
        }
    }
}

void printSet(token_set *set);//remove later
void generateFollow(ruleLL* grammar, token_set* follow, token_set* first)
{
    for (int i = 0; i < NUM_NONTERMINALS; i++)      // all the firstsets are init to 0 (empty set)
    {
        follow[i].set = 0;
    }
    addToSet(&follow[0],END_CODE);
    int changed = 1;
    // int changedNT[NUM_NONTERMINALS] = {0};
    // LLNODE *grammar[NUM_RULES];
    stack *st = getStack();
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < NUM_RULES; i++)
        {
            LLNODE *node = grammar[i].head;
            while (node->next!=NULL)
            {
                node = node->next;
                if (node->type == TERMINAL)
                {
                    continue;
                }

                if (node->type == __EPSILON){
                    break;
                }
                
                // if(i==1)
                // {
                //     printf("%s",nonterminals[node->sym.nonterminal]);
                // }

                // only option for NT left
                if (node->next == NULL)
                {
                    if ((follow[node->sym.nonterminal].set | follow[grammar[i].head->sym.nonterminal].set)!=follow[node->sym.nonterminal].set)
                    {
                        changed = 1;   
                        follow[node->sym.nonterminal].set |= follow[grammar[i].head->sym.nonterminal].set;
                    }
                    
                    push(st, node->sym.nonterminal);
                    propogateStackFollow(st, follow,&changed);
                     //printf("  flagged at next NULL %d\n  ", i);      
                    break;
                }
                // node next is not null

                if (node->next->type == TERMINAL)
                {
                    if (addToSet(&follow[node->sym.nonterminal], node->next->sym.terminal))
                    {
                        changed = 1; // setting changed
                        //printf("  flagged at next is term %d\n  ", i);
                    }
                    push(st, node->sym.nonterminal);
                    propogateStackFollow(st, follow,&changed);
                    continue;
                }
                // handled next being terminal
                long long int temp = follow[node->sym.nonterminal].set | first[node->next->sym.nonterminal].set;
                if(follow[node->sym.nonterminal].set != temp){

                    changed = 1; // setting changed
                    follow[node->sym.nonterminal].set = temp;
                }
                push(st, node->sym.nonterminal);

                if (setContains(&first[node->next->sym.nonterminal], EPSILON))
                {
                    printf("HELLL %d\n",i);
                    //push(st, node->sym.nonterminal);
                    continue;
                }
                // now just need to add follow of next into current
                // long long int temp = follow[node->sym.nonterminal].set | first[node->next->sym.nonterminal].set;
                // if(follow[node->sym.nonterminal].set != temp){
                //     changed = 1; // setting changed
                //     follow[node->sym.nonterminal].set = temp;
                // }
                //push(st, node->sym.nonterminal);
                propogateStackFollow(st, follow, &changed);
            }
        }
    }

    long long int epsv = (long long)1 <<EPSILON; //remove epsilon
    for (int i = 0; i < NUM_RULES; i++)
    {
        follow[i].set &= ~epsv;
    }
}

ruleLL* parseTable[NUM_NONTERMINALS][NUM_TERMINALS];



void makeParseTable(token_set* first, token_set* follow,ruleLL* grammar)
{
    for(int i=0;i<NUM_NONTERMINALS;i++){
        for(int j=0;j<NUM_TERMINALS;j++){
            parseTable[i][j]=NULL;
        }
    }

    for(int i=0; i<NUMRULES; i++)
    {
        LLNODE* node = grammar[i].head;
        int flag=1;
        SYMBOL nt=node->sym;

        node = node->next;

        while(flag && node != NULL)
        {
            flag=0;
            if(node->type == TERMINAL){
                parseTable[nt.nonterminal][node->sym.terminal]=&grammar[i];            
            }
            else if(node->type == __EPSILON)
            {
                long long int num = follow[node->sym.nonterminal].set;
                int index = 0;
                while (num) {
                    if (num & 1) {
                        parseTable[nt.nonterminal][index]=&grammar[i];
                    }
                    num >>= 1;  // Right shift to check the next bit
                    ++index;
                }
            }
            else if(node->type == NON_TERMINAL)
            {
                long long int num = first[node->sym.nonterminal].set;
                int index = 0;
                while (num) {
                    if(index == EPSILON && (num&1))
                    {
                        flag=1;
                        continue;
                    }
                    if (num & 1) {
                        parseTable[nt.nonterminal][index]=&grammar[i];
                    }
                    num >>= 1;  // Right shift to check the next bit
                    ++index;
                }
            }

            if(flag==1) node=node->next;
        }

        if(flag){
            long long int num = follow[node->sym.nonterminal].set;
                int index = 0;
                while (num) {
                    if (num & 1) {
                        parseTable[nt.nonterminal][index]=&grammar[i];
                    }
                    num >>= 1;  // Right shift to check the next bit
                    ++index;
                }
        }

    }
}
void printLinkedList(LLNODE* node) {
    while (node != NULL) {
        if(node->type == TERMINAL)
        {
        printf("%d -> ", node->sym.terminal);
        node = node->next;
        }
        if(node->type == NON_TERMINAL)
        {
        printf("%d -> ", node->sym.nonterminal);
        node = node->next;
        }
        if(node->type == __EPSILON)
        {
        printf("%s -> ", "E");
        node = node->next;
        }
    }
    printf("NULL\n");
}

void printParseTable(ruleLL*** parseTable)
{
    for(int i=0;i<NUM_NONTERMINALS;i++)
    {
        for(int j=0;j<NUM_TERMINALS;j++)
        {
           
            printf("reached 1");
            ruleLL* ptr=parseTable[i][j];

            printf("reached 2");
            if(ptr->head->type==TERMINAL){
                printf("%d",((ptr->head)->sym).terminal);
            }
            else if(ptr->head->type==NON_TERMINAL){
                printf("%d",((ptr->head)->sym).nonterminal);
            }
            // printf("%d",(ptr->head)->sym);
        }
    }
}

void print_rules(ruleLL* rules)
{
    for (int i = 0; i < NUM_RULES; i++)
    {
        LLNODE *temp = rules[i].head;
        printf("%d: %s --> ", i, nonterminals[temp->sym.nonterminal]);
        temp = temp->next;
        if (temp == NULL)
        {
            printf("EPSILON");
        }
        while (temp != NULL)
        {
            if (temp->type == NON_TERMINAL)
            {
                printf("%s ", nonterminals[temp->sym.nonterminal]);
            }
            else if (temp->type == TERMINAL)
            {
                printf("%s ", terminals[temp->sym.terminal]);
            }
            else if (temp->type == __EPSILON)
            {
                printf("EPSILON ");
            }
            temp = temp->next;
        }
        printf("\n");
    }
}

void printSet(token_set *set)
{
    long long cur = set->set;
    if (cur == 0)
    {
        printf("EMPTY SET");
        return;
    }
    for (int i = 0; i < NUM_TERMINALS; i++)
    {
        if (cur & 1)
        {
            printf("%s ", terminals[i]);
        }
        cur = cur >> 1;
    }
    if (isMember(set, EPSILON))
    {
        printf("EPSILON");
    }
    if (isMember(set, END_CODE))
    {
        printf("$");
    }
}

int main()
{
    create_hashTable();
    ruleLL *rules = createGrammar("grammar.csv", hash_table);
    print_rules(rules);
    token_set *first_sets = malloc(sizeof(token_set) * NUM_NONTERMINALS);
    token_set *follow_sets = malloc(sizeof(token_set) * NUM_NONTERMINALS);
    computeFirst(first_sets,rules);
    for (int i = 0; i < NUM_NONTERMINALS; i++)
    {
        printf("First(%s): ", nonterminals[i]);
        printSet(&first_sets[i]);
        printf("\n");
    }
    generateFollow(rules,follow_sets,first_sets);
    for (int i = 0; i < NUM_NONTERMINALS; i++)
    {
        printf("First(%s): ", nonterminals[i]);
        printSet(&first_sets[i]);
        printf("\n");
    }

    for (int i = 0; i < NUM_NONTERMINALS; i++)
    {
        printf("Follow(%s): ", nonterminals[i]);
        printSet(&follow_sets[i]);
        printf("\n");
    }
    printf("hello\n");
    makeParseTable(first_sets,follow_sets,rules);
    printf("hi\n");
    // printParseTable(&parseTable);


    // printf("Enter the buffer size: ");
    // scanf("%d", &bufferSize);
    // parseInputSourceCode("../../tests/t5.txt", "parseTree.txt");
    return 0;
}