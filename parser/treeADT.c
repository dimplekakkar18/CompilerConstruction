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
        // if(parseTree->root==NULL)printf("******************************************root null\n");
        // else if(parent==NULL)printf("*******************************************parent null\n");
        parseTree->root = child; 
    }
    else{
        parent->numChild++; 
        parent->children = realloc(parent->children, sizeof(TreeNode *) * parent->numChild);
        parent->children[parent->numChild - 1] = child; 
        //make sure child isn't null 
        child->parent = parent; 

        //printf("Parent is %s ",nonterminals[parent->val.sym.nonterminal]);
    }
    
}
void printParseTreeNode(TreeNode *node, int level, FILE* fp)
{
    if (node == NULL)
        return;

    // Print indentation based on the level of the node
    for (int i = 0; i < level; i++)
    {
        fprintf(fp,"    ");
    }

    // if (node->numChild == 0)
    // {
        
    // }

    if (node->val.type == NON_TERMINAL)
        fprintf(fp,"Current Node: %s, Parent Node: %s, Line Number %d\n",
               nonterminals[node->val.sym.nonterminal],
               (node->parent != NULL) ? nonterminals[node->parent->val.sym.nonterminal] : "ROOT",
               lineNo);
    else if (node->val.type == TERMINAL)
           fprintf(fp,"Current Node: %s, Parent Node: %s, Line Number %d\n",
               terminals[node->val.sym.terminal],
               (node->parent != NULL) ? nonterminals[node->parent->val.sym.nonterminal] : "ROOT",
               lineNo);
    else if(node->val.type == __EPSILON)
            fprintf(fp,"Current Node: EPSILON, Parent Node: %s, Line Number %d\n",
               (node->parent != NULL) ? nonterminals[node->parent->val.sym.nonterminal] : "ROOT",
               lineNo);
        
    // else if (node->val.type == TERMINAL)
    //     printf("Current Node: %s, Parent Node: %s, Line Number %d\n",
    //            terminals[node->val.sym.terminal],
    //            (node->parent != NULL) ? nonterminals[node->parent->val.sym.nonterminal] : "ROOT",
    //            lineNo);

    for (int i = 0; i < node->numChild; i++)
    {
        printParseTreeNode(node->children[i], level + 1,fp);
    }
}

void printParseTree(Tree *parseTree, FILE* fp)
{
    if (parseTree->root == NULL)
    {
        fprintf(fp,"Tree is empty!\n");
        return;
    }

    printParseTreeNode(parseTree->root, 0,fp);
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
