// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#include "treeADT.h"
#include <stdlib.h>

//Allocating memory for the tree 
Tree  * createTree(){
    Tree * parseTree = (Tree *)malloc(sizeof(Tree));  
    parseTree->root = NULL; 
    return parseTree; 
}

TreeNode * createTreeNode(){
    TreeNode * node = (TreeNode * ) malloc(sizeof(TreeNode)); 
    node->parent = NULL; 
    node->children = NULL; 
    node->numChild = 0; 
    node->val.type = NONE; 
    node->lexeme = NULL; 
    return node; 
}

void addTreeNode(Tree * parseTree, TreeNode * parent, TreeNode * child)
{
    
    if(parseTree == NULL) {
        printf("Tree not created! \n");
        return; 
    }
    if(parseTree->root == NULL || parent==NULL)
    {
        parseTree->root = child; 
    }
    else{
        parent->numChild++; 
        parent->children = realloc(parent->children, sizeof(TreeNode *) * parent->numChild);
        parent->children[parent->numChild - 1] = child; 
        //make sure child isn't null 
        child->parent = parent; 
    }
    
}
void printParseTreeNode(TreeNode *node, FILE* fp)
{
    if (node == NULL)
        return;
    if(node->numChild !=0)
        printParseTreeNode(node->children[node->numChild-1],fp);

    if (node->val.type == NON_TERMINAL)
        fprintf(fp,"Lexeme: %-20s Line Number: %-20d Token Name: %-30s Parent Node: %-30s isLeafNode: NO            CurrentNode Symbol: %-30s \n",
               node->lexeme,node->lineNumber,nonterminals[node->val.sym.nonterminal],
               (node->parent != NULL) ? nonterminals[node->parent->val.sym.nonterminal] : "ROOT",nonterminals[node->val.sym.nonterminal]);
    else if (node->val.type == TERMINAL)
        fprintf(fp,"Lexeme: %-20s Line Number: %-20d Token Name: %-30s Parent Node: %-30s isLeafNode: YES           CurrentNode Symbol: %-30s \n",
               node->lexeme,node->lineNumber,terminals[node->val.sym.terminal],
               (node->parent != NULL) ? nonterminals[node->parent->val.sym.nonterminal] : "ROOT",terminals[node->val.sym.nonterminal]);
    else if(node->val.type == __EPSILON)
            fprintf(fp,"Lexeme: %-20s Line Number: %-20d Token Name: %-30s Parent Node: %-30s isLeafNode: YES           CurrentNode Symbol: %-30s\n",
               node->lexeme,node->lineNumber,"EPSILON", 
               (node->parent != NULL) ? nonterminals[node->parent->val.sym.nonterminal] : "ROOT","EPSILON");

    for (int i = node->numChild - 2; i >= 0; i--)
    {
        printParseTreeNode(node->children[i],fp);
    }
}

void printParseTree(Tree *parseTree, FILE* fp)
{
    if (parseTree->root == NULL)
    {
        fprintf(fp,"Tree is empty!\n");
        return;
    }

    printParseTreeNode(parseTree->root,fp);
}


void destroyTreeNode(TreeNode * node)
{
    if(node == NULL) return; 

    for(int i=0; i<node->numChild; i++)
    {
        destroyTreeNode(node->children[i]);
    }
    
    free(node);  
}
void destroyTree(Tree * parseTree){

    destroyTreeNode(parseTree->root); 
    free(parseTree); 
}
