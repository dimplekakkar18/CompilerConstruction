#ifndef TREE_H
#define TREE_H
#include "parseDef.h"


typedef struct TreeNode{
    struct TreeNode ** children; 
    struct TreeNode * parent; 
    int numChild;  
    tree_ele val; 
} TreeNode; 

typedef struct Tree{
    TreeNode * root;  
}Tree;

Tree  * createTree(); 
TreeNode * createTreeNode();
void addTreeNode(Tree * parseTree, TreeNode * parent, TreeNode * child);
void printTree(Tree * parseTree, FILE* fp);
void destroyTree(Tree * parseTree);
extern int lineNo; 
#endif