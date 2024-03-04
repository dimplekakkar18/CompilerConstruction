// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#ifndef SET_H
#define SET_H
#include "lexerDef.h"

// We have used a long long int as a bitset to implement set.
// This is the most efficient implementation of a set as it occupies very less memory
// and makes our code faster in terms of time complexity.
// We have 58 tokens in the code representation of our grammar,
// since 58 < 64 we can use this implementation.
// a bit = 0 represents that token corresponding to corresponding position is not present in the set
// and a bit = 1 represents that token corresponding to corresponding position is present in the set
struct token_set
{
    long long int set;
};
typedef struct token_set token_set;

token_set *createTokenSet(); // returns a pointer to a new token_set initialized to the empty set (0)
void addToken(token_set *ts, enum TOKENS tok); // adds tok to ts if not already present, else does nothing
void removeToken(token_set *ts, enum TOKENS tok); // removes tok from ts if present, else does nothing
int isMember(token_set *ts, enum TOKENS tok); // returns 1 if tok is in ts, 0 otherwise

#endif