// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#ifndef TREE_H
#define TREE_H
#include "parseDef.h"


typedef struct TreeNode{
    struct TreeNode ** children; 
    struct TreeNode * parent; 
    int numChild;  
    tree_ele val; 
    int lineNumber;
    char * lexeme;  
} TreeNode; 

typedef struct Tree{
    TreeNode * root;  
}Tree;

Tree  * createTree(); 
TreeNode * createTreeNode();
void addTreeNode(Tree * parseTree, TreeNode * parent, TreeNode * child);
void printParseTree(Tree * parseTree, FILE* fp);
void destroyTree(Tree * parseTree);
extern int lineNo; 
#endif