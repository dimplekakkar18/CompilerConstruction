// Group - 29
// Dimple - 2020B4A70632P
// Raunak Bhalla - 2020B4A70859P
// Shrestha Sharma - 2020B3A70817P
// Radhika Gupta - 2020B4A70600P
// Yasaswini Reddy S - 2020B1A71892
// Akshat Shetye - 2021A7PS2426

#include <stdlib.h>

#include "set.h"

token_set *createTokenSet()
{
    token_set *ts = (token_set *)malloc(sizeof(token_set));
    ts->set = 0LL;
    return ts;
}

void addToken(token_set *ts, enum TOKENS tok)
{
    ts->set |= (1LL << tok);
}

void removeToken(token_set *ts, enum TOKENS tok)
{
    ts->set &= ~(1LL << tok);
}

int isMember(token_set *ts, enum TOKENS tok)
{
    return (ts->set & (1LL << tok)) != 0LL;
}