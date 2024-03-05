// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "lexer.h"
#include "linkedList.h"
#include "treeADT.h"

int calculateHash(char *word);
int addnonTerm();
int addTerm();
void create_hashTable();
int getIndex(char *tok);
Tree * parseInputSourceCode(ruleLL *grammar, int ** parse_table, FILE * fp);
int** makeParseTable(long long int* first, long long int* follow, ruleLL* grammar); 
ruleLL * createGrammar(char * filename); 
void computeFirst(long long int *firstSet, ruleLL* rules);
void generateFollow(ruleLL* grammar, long long int* follow, long long int* first); 
void print_rules(ruleLL* rules);


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
    "TK_BIGLENERROR","TK_BIGFIELDERROR"};

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

char * removeWhitespace(char * tok)
{
    int index = 0;
    while (tok[index] != '\0')
    {
        if (tok[index] == '\n' || tok[index] == '\r' || tok[index] == ' ' || tok[index] == '\t')
        {
            tok[index] = '\0';
            break;
        }
        index++;
    }
    return tok;
}

ruleLL *createGrammar(char* grammar_file)
{
    FILE* fp = fopen(grammar_file, "r");
    char buffer[128];
    struct LLNode *left;
    struct LLNode *right;
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

        char *tok = strtok(buffer, delim); // Just extracting the left hand side of each rule, i.e the nonterminal

        int index = getIndex(tok);

        if (hash_table[index].type == NON_TERMINAL)
        {
            left = createNewNode(hash_table[index].sym, NON_TERMINAL);
            addNewNode(left, &grammar[i]);
        }
        else
        {
            printf("Error: rule starts with a terminal \n");
        }

        tok = strtok(NULL, delim); // NULL in the first entry means it'll start tokenizing from where it left off, i.e RHS
        while (tok != NULL)
        {
            tok = removeWhitespace(tok);
            int index = getIndex(tok);
            right = createNewNode(hash_table[index].sym, hash_table[index].type);
            addNewNode(right, &grammar[i]);
            tok = strtok(NULL, delim);
        }
        i++;
    }
    fclose(fp);

    return grammar;
}


int addToSet(long long int* set, int term)
{
    long long int termval = ((long long)1) << term;

    if (*set & termval)
        return 0; // this val already set

    *set |= termval;
    return 1;
}

int setContains(long long int* sets, int term)
{
    long long int termval = ((long long)1) << term;
    if (*sets & termval)
        return 1;
    else
        return 0;
}

void removeFromSet(long long int *ts, enum TOKENS tok)
{
    *ts &= ~((long long)1 << tok);
}

void computeFirst(long long int *firstSet, ruleLL* rules)
{
    for (int i = 0; i < NUM_NONTERMINALS; i++)      // all the firstsets are init to 0 (empty set)
    {
        firstSet[i] = 0;
    }
    int isDone[NUM_RULES];                          // isDone means we are done with that rule
    long long int nullable = 0;                     // the non-terminals which are nullable have the bit set
    for(int i = 0; i < NUM_RULES; i++){
        isDone[i] = 0;
    }
    for(int i = 0; i < NUM_RULES; i++){
        if(rules[i].head->next->type==__EPSILON){               // RHS is EPSILON
            addToSet(&firstSet[rules[i].head->sym.nonterminal], EPSILON);   // include EPSILON in first(LHS)
            addToSet(&nullable, rules[i].head->sym.nonterminal);            // LHS is a nullable non-terminal
            isDone[i] = 1;
        }
        else if(rules[i].head->next->type==TERMINAL){    // RHS is a TERMINAL
            addToSet(&firstSet[rules[i].head->sym.nonterminal], rules[i].head->next->sym.terminal);   // include this TERMINAL in first(LHS)
            isDone[i] = 1;
        }
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
                        if(!setContains(&nullable, node->sym.nonterminal)){            // if in RHS there are non-terminal which are yet not nullable, we cannot go ahead with them
                            break;
                        }
                    }
                    node = node->next;
                }
                if(node==NULL){
                    isDone[i] = 1;
                    addToSet(&nullable, temp1->sym.nonterminal);         // if we have reached the end it means this LHS non term is nullable
                }
            }
        }
    }
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        if(setContains(&nullable, i)){
            addToSet(&firstSet[i], EPSILON);
        }
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
                else if(!setContains(&nullable, node->sym.nonterminal)){  // non nullable
                    addToSet(&adj[temp->sym.nonterminal], node->sym.nonterminal);
                    break;
                }
                addToSet(&adj[temp->sym.nonterminal], node->sym.nonterminal);  // nullable
                node = node->next;
            }
        // }
    }

    // do topoSort
    int n = NUM_NONTERMINALS;
    int inDegree[NUM_NONTERMINALS];
    for(int i = 0; i < n; i++){
        inDegree[i]= 0;
    }
    int itr = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < NUM_NONTERMINALS; j++){
            if(setContains(&adj[i], j)){
                inDegree[j]++;
            }
        }
    }
    Queue* q = createQueue();
    for(int i = 0; i < NUM_NONTERMINALS; i++){
        if(inDegree[i]==0){
            enqueue(q, itoe(i));
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
        for(int it = 0; it < NUM_NONTERMINALS; it++){
            if(setContains(&adj[node], it)){
                inDegree[it]--;
                if(inDegree[it]==0)  enqueue(q, itoe(it));
            }
        }
    }
    destroyQueue(q);
    // compute the first in this order

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
                while(node!=NULL && node->type==NON_TERMINAL && setContains(&nullable, node->sym.nonterminal)){       //nullable
                    long long int temp = firstSet[node->sym.nonterminal];                       
                    removeFromSet(&temp, EPSILON);                                     
                    firstSet[temp1->sym.nonterminal] |= temp;       
                    node = node->next;
                }
                if(node!=NULL && node->type==NON_TERMINAL){             // reached a non-nullable => include the first of RHS into first of LHS
                    long long int temp = firstSet[node->sym.nonterminal];                       
                    removeFromSet(&temp, EPSILON);                                     
                    firstSet[temp1->sym.nonterminal] |= temp;       
                }                     
                else if(node!=NULL){
                    firstSet[temp1->sym.nonterminal] |= (1LL<<(node->sym.terminal));
                }          
            }
        }
    }
}

void generateFollow(ruleLL* grammar, long long int* follow, long long int* first)
{
    for (int i = 0; i < NUM_NONTERMINALS; i++)      // all the firstsets are init to 0 (empty set)
    {
        follow[i] = 0;
    }
    addToSet(&follow[0],END_CODE);
    int changed = 1;
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
                    long long int temp = follow[node->sym.nonterminal] | first[tempnode->sym.nonterminal];
                    if(follow[node->sym.nonterminal] != temp){
                        changed = 1; // setting changed
                        follow[node->sym.nonterminal] = temp;
                    }
                    
                    tempnode = tempnode->next;
                }

                if (tempnode== NULL)
                {
                    if ((follow[node->sym.nonterminal] | follow[grammar[i].head->sym.nonterminal])!=follow[node->sym.nonterminal])
                    {
                        changed = 1;   
                        follow[node->sym.nonterminal] |= follow[grammar[i].head->sym.nonterminal];
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
                long long int temp = follow[node->sym.nonterminal] | first[tempnode->sym.nonterminal];
                if(follow[node->sym.nonterminal] != temp){

                    changed = 1; // setting changed
                    follow[node->sym.nonterminal] = temp;
                }
            }
        }
    }

    long long int epsv = (long long)1 <<EPSILON; //remove epsilon
    for (int i = 0; i < NUM_RULES; i++)
    {
        follow[i] &= ~epsv;
    }
}

int** makeParseTable(long long int* first, long long int* follow, ruleLL* grammar) {
    //each cell stores the corresponding grammar rule number
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
                parseTable[nt.nonterminal][node->sym.terminal] = i; // Store the rule index
            } else if (node->type == __EPSILON) {
                long long int num = follow[nt.nonterminal];
                int index = 0;
                while (num) {
                    if (num & 1) { //set rule number for all terminals in follow of the nonterminal
                        parseTable[nt.nonterminal][index] = i;
                    }
                    num >>= 1; // Right shift to check the next bit
                    ++index;
                }
            } else if (node->type == NON_TERMINAL) {
                long long int num = first[node->sym.nonterminal];
                int index = 0;
                while (num) {
                    if (index == EPSILON && (num & 1)) { //set flag if the first set contains epsilon 
                        flag = 1;
                        num >>= 1;
                        continue;
                    }
                    if (num & 1) { //set rule number for all terminals in first of the non-terminal
                        parseTable[nt.nonterminal][index] = i;
                    }
                    num >>= 1; // Right shift to check the next bit
                    ++index;
                }
            }
            if (flag == 1)
                node = node->next;
        }

        if (flag) { // if the first of RHS of a rule contains epsilon
            long long int num = follow[node->sym.nonterminal];
            int index = 0;
            while (num) {
                if (num & 1) { //set rule for all terminals in follow of the nonterminal(LHS)
                    parseTable[nt.nonterminal][index] = i;
                }
                num >>= 1; // Right shift to check the next bit
                ++index;
            }
        }
    }
    for(int i=0;i<NUM_NONTERMINALS;i++)
    {
        long long int nont = follow[i];
        for(int j=0;j<NUM_TERMINALS;j++)
        {
            if(parseTable[i][j]==-1){ 
                if(nont & 1){       // populating synchronizing tokens obtained from FOLLOW set of the nonterminal
                    parseTable[i][j]=-2; //-2 stands for synch tokens
                }
            }
            nont>>=1;
        }
    }
    
    for(int i=0;i<NUM_NONTERMINALS;i++)
    {
        for(int j=0;j<NUM_TERMINALS;j++)
        {
            if((parseTable[i][j]==-1 || parseTable[i][j]==-2) && (j == TK_ELSE || j == TK_IF || j == TK_WHILE || j == TK_UNION|| j == TK_RECORD || j == TK_FUNID || j == TK_MAIN || j == TK_THEN || j == TK_DEFINETYPE || j == TK_READ || j == TK_WRITE || j == TK_RETURN || j == TK_END || j == TK_ENDIF || j == TK_ENDRECORD || j == TK_ENDUNION || j == TK_ENDWHILE || j == TK_TYPE || j == TK_FUNID || j == TK_MAIN))
            {
                parseTable[i][j]=-3; //-3 stands for additional tokens marking the beginning of a new statement 
            }
        }
    }

    return parseTable;
}
void addToStackAndTree(Tree * parseTree, stack * stk,int sym, SYMBOLTYPE type, TreeNode * parent, int lineNumber, char * lexeme)
{
    if(type==__EPSILON) return;
    TreeNode * tnode = createTreeNode(); 
    if(type == NON_TERMINAL)
        tnode->val.sym.nonterminal = sym; 
    else if(type==TERMINAL)
        tnode->val.sym.terminal = sym; 
    tnode->val.type = type;  
    tnode->lineNumber = lineNumber; 
    tnode->lexeme = lexeme; 
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
Tree * parseInputSourceCode(ruleLL *grammar, int ** parse_table, FILE * fp){ //long long int* firstSet){
    stack * stk = getStack(); 
    Tree * parseTree = createTree(); 

    stackNODE * stkele = createStackEle(); 
    stkele->val.sym.terminal = END_CODE;
    stkele->val.type = __ENDCODE;  
    push(stk, stkele); 

    addToStackAndTree(parseTree, stk, STARTSYMBOL, NON_TERMINAL, NULL, 0, "---");
    TOKEN tok = getToken(fp); 
    int flag = 1;
    int errflag=0;
    while(*(tok.lexeme) != EOF )
    {
        if(tok.tokenId==TK_COMMENT){
            tok = getToken(fp);
            continue;
        }

        if(tok.tokenId==TK_EOF)
        {
            break;
        }
        if(tok.tokenId==TK_ERROR || tok.tokenId == TK_BIGLENERROR || tok.tokenId==TK_BIGFIELDERROR){
            printTokenInfo(tok);
            tok = getToken(fp);
            
            continue;
        }
        
         
        
        stackEle TOS = top(stk)->val;
        if(TOS.type == __ENDCODE) return parseTree;
        TreeNode *treeref = top(stk)->treeref;
 
        if(TOS.type == NON_TERMINAL)
        {
            
            int index = parse_table[TOS.sym.nonterminal][tok.tokenId];
            if(index == -1)
            {
                if(flag!=0)
                    printf("Line %d Error: Invalid Token %s encountered with value %s stack top %s \n", lineNo, terminals[tok.tokenId],tok.lexeme,nonterminals[TOS.sym.nonterminal]); 
                tok = getToken(fp); 
            }
            else if(index == -2)
            {
                if(flag!=0)
                    printf("Line %d Error: Invalid Token %s encountered with value %s stack top %s \n", lineNo, terminals[tok.tokenId],tok.lexeme,nonterminals[TOS.sym.nonterminal]); 
                pop(stk); 
            }
            else if(index == -3)
            {
                if(flag!=0)
                    printf("Line %d Error: Invalid Token %s encountered with value %s stack top %s \n", lineNo-1, terminals[tok.tokenId],tok.lexeme,nonterminals[TOS.sym.nonterminal]); 
                pop(stk); 
            }
            if(index<0){
                flag = 0;
                errflag=1;
            }
            else 
            {
                flag = 1;
                LLNODE * temp = grammar[index].tail; 
                pop(stk); 
                int i =0;
                while(temp->prev!=NULL)
                {
                    if(temp->type == NON_TERMINAL)
                        addToStackAndTree(parseTree, stk, temp->sym.nonterminal, temp->type, treeref, tok.lineNo, "---"); 
                    else if(temp->type == TERMINAL)
                        addToStackAndTree(parseTree, stk, temp->sym.terminal, temp->type,treeref,tok.lineNo,tok.lexeme); 
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
                treeref->lexeme = tok.lexeme; 
                pop(stk);
                tok = getToken(fp); 
            }
            else
            {
                if((TOS.sym.terminal == TK_SEM || TOS.sym.terminal == TK_SQR || TOS.sym.terminal == TK_CL) && (tok.tokenId == TK_ELSE || tok.tokenId == TK_IF || tok.tokenId == TK_WHILE || tok.tokenId == TK_UNION|| tok.tokenId == TK_RECORD || tok.tokenId == TK_FUNID || tok.tokenId == TK_MAIN || tok.tokenId == TK_THEN || tok.tokenId == TK_DEFINETYPE || tok.tokenId == TK_READ || tok.tokenId == TK_WRITE || tok.tokenId == TK_RETURN || tok.tokenId == TK_END || tok.tokenId == TK_ENDIF || tok.tokenId == TK_ENDRECORD || tok.tokenId == TK_ENDUNION || tok.tokenId == TK_ENDWHILE || tok.tokenId == TK_TYPE || tok.tokenId == TK_FUNID || tok.tokenId == TK_MAIN)){
                    printf("Line %d Error: The token %s for lexeme %s does not match with the expected token %s \n", lineNo-1, terminals[tok.tokenId], tok.lexeme, terminals[TOS.sym.terminal]); 
                    flag = 0; //changed
                }
                else if (flag!=0)//changed
                {
                    printf("Line %d Error: The token %s for lexeme %s does not match with the expected token %s \n", lineNo, terminals[tok.tokenId], tok.lexeme, terminals[TOS.sym.terminal]); 
                    flag = 0; //changed
                }
                pop(stk); 
            }
        }
    }
    if(errflag == 0) {
        printf("\nInput source code is syntactically correct...........\n");
        printf("Parse Tree created successfully! \n");
    }
    else printf("\nParse tree could not be constructed, the input file is NOT syntactially correct........\n");
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

    for(int i=0;i<NUM_NONTERMINALS;i++)
    {
        for(int j=0;j<NUM_TERMINALS;j++)
        {
            ruleLL ptr = parseTable[i][j];
            if(ptr.head==NULL)
            {
                printf("error");
            }
            else if(ptr.head->type==TERMINAL){
                printf("%s", terminals[((ptr.head)->sym).terminal]);
            }
            else if(ptr.head->type==NON_TERMINAL){
                printf("%s",nonterminals[((ptr.head)->sym).nonterminal]);
            }
            
        }
        printf("\n");
    }
}

