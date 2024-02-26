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
    node->children = NULL; 
    node->numChild = 0; 
    node->val.type = NONE; 
}

void addTreeNode(Tree * parseTree, TreeNode * parent, TreeNode * child)
{
    if(parseTree == NULL) {
        printf("Tree not created! \n");
        return; 
    }
    if(parseTree->root == NULL || parent == NULL)
    {
        parseTree->root = child; 
    }
    else{
        parent->numChild++; 
        parent->children = realloc(parent->children, sizeof(TreeNode *) * parent->numChild);
        parent->children[parent->numChild - 1] = child; 
    }
}

void printTreeNode(TreeNode * node)
{
    if(node == NULL) return;

    if(node->numChild == 0)
    {
        if(node->val.type == NON_TERMINAL)
            printf("%s \t",nonterminals[node->val.sym.nonterminal]);

        else if(node->val.type == TERMINAL)
            printf("%s \t",terminals[node->val.sym.terminal]);   
        
        return;
    }

    printTreeNode(node->children[0]); 

    if(node->val.type == NON_TERMINAL)
        printf("%s \t",nonterminals[node->val.sym.nonterminal]);
    else if(node->val.type == TERMINAL)
        printf("%s \t",terminals[node->val.sym.terminal]); 

    for(int i=1; i<node->numChild; i++)
    {
        printTreeNode(node->children[i]); 
    }
    return; 

}

void printTree(Tree * parseTree)
{
    if(parseTree->root == NULL)
    {
        printf("Tree is empty! \n");
        return;
    }
    printTreeNode(parseTree->root); 
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