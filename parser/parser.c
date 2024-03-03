#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "set.h"
#include "../lexer.h"
#include "parser.h"
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
    "<expPrime>",
    "<lowPrecedenceOperators>",
    "<factor>",
    "<termPrime>",
    "<highPrecedenceOperators>",
    "<booleanExpression>",
    "<logicalOp>",
    "<relationalOp>",
    "<var>",
    "<optionalReturn>",
    "<idList>",
    "<more_ids>",
    "<definetypestmt>",
    "<A>",
    "<elsePart>"};

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
    "TK_AS",
    "TK_ERROR",
    "TK_BIGLENERROR"};

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

ruleLL *createGrammar(char* grammar_file)
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

// void propogateStackFollow(stack *st, token_set* follow, int * changed)
// {
//     int temp = pop(st);
//     while (st->count > 0)
//     {
//         int temp2 = pop(st);
//         if((follow[temp2].set | follow[temp].set) != follow[temp2].set)
//         {
//             printf("DEBUGGER*************\n");
//             *changed = 1; // setting changed
//             //printf("flagged at propogate stack\n");
//         }
//         follow[temp2].set |= follow[temp].set;
//         temp = temp2;
//     }
// }
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

                LLNODE * tempnode=node->next;
                while((tempnode!=NULL)&&(tempnode->type==NON_TERMINAL)&&(setContains(&first[tempnode->sym.nonterminal], EPSILON)))
                {
                    long long int temp = follow[node->sym.nonterminal].set | first[tempnode->sym.nonterminal].set;
                    if(follow[node->sym.nonterminal].set != temp){
                        changed = 1; // setting changed
                        follow[node->sym.nonterminal].set = temp;
                    }
                    
                    tempnode = tempnode->next;
                }

                if (tempnode== NULL)
                {
                    if ((follow[node->sym.nonterminal].set | follow[grammar[i].head->sym.nonterminal].set)!=follow[node->sym.nonterminal].set)
                    {
                        changed = 1;   
                        follow[node->sym.nonterminal].set |= follow[grammar[i].head->sym.nonterminal].set;
                    }
                    continue;
                }
                // node next is not null

                if (tempnode->type == TERMINAL)
                {
                    if (addToSet(&follow[node->sym.nonterminal], tempnode->sym.terminal))
                    {
                        changed = 1; // setting changed
                    }
                    continue;
                }
                // handled next being terminal
                long long int temp = follow[node->sym.nonterminal].set | first[tempnode->sym.nonterminal].set;
                if(follow[node->sym.nonterminal].set != temp){

                    changed = 1; // setting changed
                    follow[node->sym.nonterminal].set = temp;
                }
            }
        }
    }

    long long int epsv = (long long)1 <<EPSILON; //remove epsilon
    for (int i = 0; i < NUM_RULES; i++)
    {
        follow[i].set &= ~epsv;
    }
}



// ruleLL** makeParseTable(token_set* first, token_set* follow,ruleLL* grammar)   //grammar is a pointer to the first ruleLL struct
// {
//     // ruleLL** parseTable = (ruleLL*)malloc(NUM_NONTERMINALS * sizeof(ruleLL));
//     // for(int i=0;i<NUM_NONTERMINALS;i++){
//     //     for(int j=0;j<NUM_TERMINALS;j++){
//     //         parseTable[i][j].head=NULL;
//     //         parseTable[i][j].tail=NULL;
//     //     }
//     // }

//     ruleLL** parseTable = (struct ruleLL*)malloc(NUM_NONTERMINALS * sizeof(struct ruleLL));
//     if (parseTable == NULL) {
//         printf("Memory allocation failed.");
//         // exit(1);
//     }

//     // Allocate memory for each row of structs
//     for (int i = 0; i < NUM_NONTERMINALS; ++i) {
//         parseTable[i] = (struct ruleLL*)malloc(NUM_TERMINALS * sizeof(struct ruleLL));
//         if (parseTable[i] == NULL) {
//             printf("Memory allocation failed.");
//             // exit(1);
//         }
//     }
//     // printf("hi\n");
//     for(int i=0; i<NUMRULES; i++)
//     {
//         // printf("reached2\n");   
//         LLNODE* node = grammar[i].head;
//         // printf("reached3\n");   
//         // if(node==NULL){printf("HI");}
//         //  printf("reached3\n");   
//         // printf("%s",node->type);
//         int flag=1;
//         SYMBOL nt=node->sym;
//         // printf("reached3\n");   

//         node = node->next;
//         // printf("hi2\n");
//         while(flag &&( node != NULL))
//         {
//             // printf("check1\n");
//             flag=0;
//             if(node->type == TERMINAL){
//                 parseTable[nt.nonterminal][node->sym.terminal]=grammar[i];
//                 if(parseTable[nt.nonterminal][node->sym.terminal].head != NULL) printf("value stored\n");               
//             }
//             else if(node->type == __EPSILON)
//             {
//                 // printf("check\n");
//                 long long int num = follow[node->sym.nonterminal].set;
//                 int index = 0;
//                 while (num) {
//                     if (num & 1) {
//                         parseTable[nt.nonterminal][index]=grammar[i];
//                         if(parseTable[nt.nonterminal][node->sym.terminal].head != NULL) printf("value stored\n");  
//                     }
//                     num >>= 1;  // Right shift to check the next bit
//                     ++index;
//                 }
                             
                
//             }
//             else if(node->type == NON_TERMINAL)
//             {
//                 long long int num = first[node->sym.nonterminal].set;
//                 int index = 0;
//                 while (num) {
//                     if(index == EPSILON && (num&1))
//                     {
//                         // printf("DEBUGER\n");
//                         flag=1;
//                         num>>=1;
//                         continue;
//                     }
//                     if (num & 1) {
//                         // printf("DEBUGER\n");
//                         parseTable[nt.nonterminal][index]=grammar[i];
//                         if(parseTable[nt.nonterminal][node->sym.terminal].head != NULL) printf("value stored\n");  
//                     }
//                     num >>= 1;  // Right shift to check the next bit
//                     ++index;
//                 }

//                 // if(parseTable[nt.nonterminal][node->sym.terminal].head == NULL) printf("value not stored\n");
//             }
//             else{
//                 printf("ignored\n");
//             }

//             if(flag==1) node=node->next;
//         }

//         if(flag){
//             long long int num = follow[node->sym.nonterminal].set;
//                 int index = 0;
//                 while (num) {
//                     if (num & 1) {
//                         parseTable[nt.nonterminal][index]=grammar[i];
//                     }
//                     num >>= 1;  // Right shift to check the next bit
//                     ++index;
//                 }
//         }

//     }
//     return parseTable;
// }

int** makeParseTable2(token_set* first, token_set* follow, ruleLL* grammar) {
    // FILE* file = fopen("followSets.txt", "r");
    // if (file == NULL) {
    //     perror("Error opening file");
    //     // exit(EXIT_FAILURE);
    // }
    // int index = 0;
    // while (index!=NUM_NONTERMINALS) {
    //     fscanf(file, "%lld", &follow[index].set);
    //     index++;
    //     if (index >= NUM_NONTERMINALS) {
    //         break; // Prevent reading more lines than the size of the followset array
    //     }
    // }

    // fclose(file);

    int** parseTable = (int**)malloc(NUM_NONTERMINALS * sizeof(int*));
    if (parseTable == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }

    for (int i = 0; i < NUM_NONTERMINALS; ++i) {
        parseTable[i] = (int*)malloc(NUM_TERMINALS * sizeof(int));
        if (parseTable[i] == NULL) {
            printf("Memory allocation failed.");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < NUM_TERMINALS; j++) {
            parseTable[i][j] = -1; // Initialize all cells to some default value
        }
    }

    for (int i = 0; i < NUMRULES; i++) {
        LLNODE* node = grammar[i].head;
        int flag = 1;
        SYMBOL nt = node->sym;

        node = node->next;

        while (flag && (node != NULL)) {
            flag = 0;
            if (node->type == TERMINAL) {
                parseTable[nt.nonterminal][node->sym.terminal] = i; // Store the rule index instead of grammar[i]
            } else if (node->type == __EPSILON) {
                long long int num = follow[nt.nonterminal].set;
                int index = 0;
                while (num) {
                    if (num & 1) {
                        parseTable[nt.nonterminal][index] = i;
                    }
                    num >>= 1; // Right shift to check the next bit
                    ++index;
                }
            } else if (node->type == NON_TERMINAL) {
                long long int num = first[node->sym.nonterminal].set;
                int index = 0;
                while (num) {
                    if (index == EPSILON && (num & 1)) {
                        flag = 1;
                        num >>= 1;
                        continue;
                    }
                    if (num & 1) {
                        parseTable[nt.nonterminal][index] = i;
                    }
                    num >>= 1; // Right shift to check the next bit
                    ++index;
                }
            }

            if (flag == 1)
                node = node->next;
        }

        if (flag) {
            long long int num = follow[node->sym.nonterminal].set;
            int index = 0;
            while (num) {
                if (num & 1) {
                    parseTable[nt.nonterminal][index] = i;
                }
                num >>= 1; // Right shift to check the next bit
                ++index;
            }
        }
    }
        for(int i=0;i<NUM_NONTERMINALS;i++)
        {
            long long int nont = follow[i].set;
            for(int j=0;j<NUM_TERMINALS;j++)
            {
                if(parseTable[i][j]==-1){
                    if(nont & 1){
                        parseTable[i][j]=-2; //-2 stands for synch 
                    }
                }
                nont>>=1;
            }
        }
        for(int i=0;i<NUM_NONTERMINALS;i++)
        {
            for(int j=0;j<NUM_TERMINALS;j++)
            {
                // if(parseTable[i][j]==-1 && (j == TK_END || j == TK_ENDRECORD || j == TK_ENDUNION || j == TK_ENDIF || j == TK_ENDWHILE || j == TK_SEM || j == TK_SQR || j == TK_CL ))
                // {
                //     parseTable[i][j]=-2; //-2 stands for synch 
                // }
                if((parseTable[i][j]==-1 || parseTable[i][j]==-2) && (j == TK_ELSE || j == TK_IF || j == TK_WHILE || j == TK_UNION|| j == TK_RECORD || j == TK_FUNID || j == TK_MAIN || j == TK_THEN || j == TK_DEFINETYPE || j == TK_READ || j == TK_WRITE || j == TK_RETURN || j == TK_END || j == TK_ENDIF || j == TK_ENDRECORD || j == TK_ENDUNION || j == TK_ENDWHILE))
                {
                    parseTable[i][j]=-3; //-2 stands for synch 
                }
            }
        }

    return parseTable;
}

void addToStackAndTree(Tree * parseTree, stack * stk,int sym, SYMBOLTYPE type, TreeNode * parent)
{
    if(type==__EPSILON) return;
    TreeNode * tnode = createTreeNode(); 
    if(type == NON_TERMINAL)
        tnode->val.sym.nonterminal = sym; 
    else if(type==TERMINAL)
        tnode->val.sym.terminal = sym; 
    tnode->val.type = type;  
    addTreeNode(parseTree, parent, tnode); 
    
    
    stackNODE * stkele = createStackEle(); 
    stkele = createStackEle(); 
    if(type == NON_TERMINAL)
        stkele->val.sym.nonterminal = sym;
    else if(type==TERMINAL)
        stkele->val.sym.terminal = sym;
    stkele->val.type = type; 
    stkele->treeref = tnode; 
    push(stk, stkele); 

}
Tree * makeParseTree(ruleLL *grammar, int ** parse_table, FILE * fp, FILE * errorfile, token_set* firstSet){
    stack * stk = getStack(); 
    Tree * parseTree = createTree(); 

    stackNODE * stkele = createStackEle(); 
    stkele->val.sym.terminal = END_CODE;
    stkele->val.type = __ENDCODE;  
    push(stk, stkele); 

    addToStackAndTree(parseTree, stk, STARTSYMBOL, NON_TERMINAL, NULL);
    TOKEN tok = getToken(fp, errorfile); 
    int flag = 1;
    while(*(tok.lexeme) != EOF )
    //for(int i = 0;i<400;i++)
    {
        // printf("DEBUGXY    %s",tok.lexeme);
        if(tok.tokenId==TK_COMMENT){
            tok = getToken(fp, errorfile);
            continue;
        }

        if(tok.tokenId==TK_EOF)
        {
            break;
        }
        if(tok.tokenId==TK_ERROR || tok.tokenId == TK_BIGLENERROR){
            tok = getToken(fp, errorfile);
            continue;
        }
        
         
        
        stackEle TOS = top(stk)->val;
        if(TOS.type == __ENDCODE) return parseTree;
        TreeNode *treeref = top(stk)->treeref;
        // printf("%s\n", terminals[tok.tokenId]);
     //   if(TOS.type==NON_TERMINAL)printf("Top of stck %s  Input at %s \n",nonterminals[TOS.sym.nonterminal],terminals[tok.tokenId]);
       // else if(TOS.type==TERMINAL)printf("Top of stack %s  Input at %s \n",terminals[TOS.sym.terminal],terminals[tok.tokenId]);
        //if(parseTree->root->val.type==NON_TERMINAL)printf("Tree root is %s\n", nonterminals[parseTree->root->val.sym.nonterminal]);
        //else if(parseTree->root->val.type==TERMINAL)printf("Tree root is %s\n", terminals[parseTree->root->val.sym.terminal]);
        if(TOS.type == NON_TERMINAL)
        {
            
            int index = parse_table[TOS.sym.nonterminal][tok.tokenId];
            if(index < 0){
                // if(kthBitSet(&firstSet[TOS.sym.nonterminal].set, EPSILON)){
                //     TreeNode * tnode = createTreeNode(); 
                //     tnode->val.type = __EPSILON;  
                //     addTreeNode(parseTree, top(stk)->treeref, tnode); 
                //     pop(stk);
                //     continue;
                // }
            }
            if(index == -1)
            {
                if(flag!=0)
                    fprintf(errorfile,"Line %d Error: Invalid Token %s encountered with value %s stack top %s \n", lineNo, terminals[tok.tokenId],tok.lexeme,nonterminals[TOS.sym.nonterminal]); 
                tok = getToken(fp, errorfile); 
            }
            else if(index == -2)
            {
                // if(kthBitSet(&firstSet[TOS.sym.nonterminal].set, EPSILON)){
                //     TreeNode * tnode = createTreeNode(); 
                //     tnode->val.type = __EPSILON;  
                //     addTreeNode(parseTree, top(stk)->treeref, tnode); 
                //     pop(stk);
                //     continue;
                // }
                if(flag!=0)
                    fprintf(errorfile,"Line %d Error: Invalid Token %s encountered with value %s stack top %s \n", lineNo, terminals[tok.tokenId],tok.lexeme,nonterminals[TOS.sym.nonterminal]); 
                pop(stk); 
            }
            else if(index == -3)
            {
                if(flag!=0)
                    fprintf(errorfile,"Line %d Error: Invalid Token %s encountered with value %s stack top %s \n", lineNo-1, terminals[tok.tokenId],tok.lexeme,nonterminals[TOS.sym.nonterminal]); 
                pop(stk); 
            }
            if(index<0){
                flag = 0;
            }
            else 
            {
                flag = 1;
                LLNODE * temp = grammar[index].tail; 
                pop(stk); 
                int i =0;
                //printf("Inside while");
                while(temp->prev!=NULL)
                {
                    //printf("%d \n",temp->type);
                    //if(TOS.type==NON_TERMINAL)printf("Top of stck %s   \n",nonterminals[TOS.sym.nonterminal]);
                    //else if(TOS.type==TERMINAL)printf("Top of stack %s \n",terminals[TOS.sym.terminal]);
                    if(temp->type == NON_TERMINAL)
                        addToStackAndTree(parseTree, stk, temp->sym.nonterminal, temp->type, treeref); 
                    else if(temp->type == TERMINAL)
                        addToStackAndTree(parseTree, stk, temp->sym.terminal, temp->type,treeref); 
                    else if(temp->type == __EPSILON)
                        {
                            TreeNode * tnode = createTreeNode(); 
                            tnode->val.type = temp->type;  
                            addTreeNode(parseTree, treeref, tnode);                            
                        }

                    temp = temp->prev; 
                    
                }
            } 
        }
        else
        {
            
            if(tok.tokenId == TOS.sym.terminal)
            {
                pop(stk);
                tok = getToken(fp, errorfile); 
                //printf("lexeme is %s line no is %d \n",tok.lexeme,tok.lineNo);
            }
            else
            {
                
                fprintf(errorfile, "Line %d Error: The token %s for lexeme %s does not match with the expected token %s \n", lineNo, terminals[tok.tokenId], tok.lexeme, terminals[TOS.sym.terminal]); 
                pop(stk); 
            }
        }
    }
    return parseTree; 
   
}


void printParseTable2(int** parseTable)
{
    printf("Parse Table:\n");
    for (int i = 0; i < NUM_NONTERMINALS; i++)
    {
        for (int j = 0; j < NUM_TERMINALS; j++)
        {
            printf("%d ", parseTable[i][j]);
        }
        printf("\n");
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

void printParseTable(ruleLL** parseTable)
{
    // parseTable[0][0];
    // printf("hii\n");

    for(int i=0;i<NUM_NONTERMINALS;i++)
    {
        for(int j=0;j<NUM_TERMINALS;j++)
        {
           
            // printf("reached 1\n");
            ruleLL ptr = parseTable[i][j];
            // printf("%s", nonterminals[i]);
            // printf("reached 2\n");
            if(ptr.head==NULL)
            {
                printf("error");
            }
            else if(ptr.head->type==TERMINAL){
                printf("%s", terminals[((ptr.head)->sym).terminal]);
                // printf("%s",terminals[j]);
                // printf("%s",);
                // printf("%d",((ptr.head)->sym).terminal);
            }
            else if(ptr.head->type==NON_TERMINAL){
                // printf("gone");
                printf("%s",nonterminals[((ptr.head)->sym).nonterminal]);
                // printf("%d",((ptr.head)->sym).nonterminal);
            }
            // printf("%d",(ptr->head)->sym);
            
        }
        printf("\n");
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

// int main()
// {
//     create_hashTable();
//     ruleLL *rules = createGrammar("grammar.csv");
//     print_rules(rules);
//     token_set *first_sets = malloc(sizeof(token_set) * NUM_NONTERMINALS);
//     token_set *follow_sets = malloc(sizeof(token_set) * NUM_NONTERMINALS);
//     computeFirst(first_sets,rules);
//     for (int i = 0; i < NUM_NONTERMINALS; i++)
//     {
//         printf("First(%s): ", nonterminals[i]);
//         printSet(&first_sets[i]);
//         printf("\n");
//     }

//     generateFollow(rules,follow_sets,first_sets);
//         for (int i = 0; i < NUM_NONTERMINALS; i++)
//     {
//         printf("Follow(%s): ", nonterminals[i]);
//         printSet(&follow_sets[i]);
//         printf("\n");
//     }
//     int** pt = makeParseTable2(first_sets,follow_sets,rules);
//     printParseTable2(pt);
//     // for (int i = 0; i < NUM_NONTERMINALS; i++)
//     // {
//     //     printf("First(%s): ", nonterminals[i]);
//     //     printSet(&first_sets[i]);
//     //     printf("\n");
//     // }


//     // ruleLL** pt = makeParseTable(first_sets,follow_sets,rules);

//     // printf("hi\n");
//     // pt[0][0];
//     // printParseTable(pt);


//     // printf("Enter the buffer size: ");
//     // scanf("%d", &bufferSize);
//     // parseInputSourceCode("../../tests/t5.txt", "parseTree.txt");
//     return 0;
// }