#ifndef TREE_H
#define TREE_H
#include "parseDef.h"


typedef struct TreeNode{
    struct TreeNode ** children; 
    int numChild;  
    tree_ele val; 
} TreeNode; 

typedef struct Tree{
    TreeNode * root;  
}Tree;

Tree  * createTree(); 
TreeNode * createTreeNode();
void addTreeNode(Tree * parseTree, TreeNode * parent, TreeNode * child);
void printTree(Tree * parseTree);
void destroyTree(Tree * parseTree);

#endif