// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#ifndef PARSER_H
#define PARSER_H
#include "linkedList.h"
#include "treeADT.h"

int calculateHash(char *word);                                                                    // Computes a hash value for a given word (string) to be used in a parsing table.
int addnonTerm();                                                                                 // Adds a non-terminal to the set of non-terminals in the grammar.
int addTerm();                                                                                    // Adds a terminal to the set of terminals in the grammar.
void create_hashTable();                                                                          // Creates a hash table for efficient indexing of non-terminals and terminals.
int getIndex(char *tok);                                                                          // Retrieves the index of a given token (non-terminal or terminal) from the hash table.
Tree * parseInputSourceCode(ruleLL *grammar, int ** parse_table, FILE * fp, token_set* firstSet); // Parses the input source code using a LL(1) parsing approach and constructs a parse tree.
int ** makeParseTable(token_set* first, token_set* follow, ruleLL* grammar);                      // Constructs and returns the LL(1) parsing table for the given grammar.
ruleLL * createGrammar(char * filename);                                                          // Reads a grammar file and creates a linked list representation of the grammar rules.
void computeFirst(token_set *firstSet, ruleLL* rules);                                            // Computes the FIRST sets for each non-terminal in the grammar.
void generateFollow(ruleLL* grammar, token_set* follow, token_set* first);                        // Generates the FOLLOW sets for each non-terminal in the grammar.


//.............AUXILLARY FUNCTION..................:

// This function adds a symbol to both the parse tree and the stack during the LL(1) parsing process,
// creating a corresponding tree node and stack element with information such as symbol type, line number, 
// and lexeme.
void addToStackAndTree(Tree * parseTree, stack * stk,int sym, SYMBOLTYPE type, TreeNode * parent, int lineNumber, char * lexeme); 

#endif