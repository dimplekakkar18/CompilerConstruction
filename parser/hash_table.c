#include "linkedList.h"
#include <string.h>
#include <stdio.h>

int calculateHash(char *word)
{
    int hash_value = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash_value = (hash_value * PRIME + word[i]) % HASH_TABLE_SIZE;
        // hash_value = ((hash_value << 5) + hash_value) + kwname[i];
    }
    return hash_value;
}

int addnonTerm(){
    
    int num_collisions = 0;
    for (int i = 0; i < NUM_NONTERMINALS; i++)
    {
        int index = calculateHash(nonterminals[i]);

        if (hash_table[index].type == NONE)
        {
            hash_table[index].type = NON_TERMINAL;
            hash_table[index].sym.nonterminal = i;
        }

        else
        {
            int probe = 1;
            int newIndex;
            while (1)
            {
                num_collisions++;
                newIndex = (index + probe * probe) % HASH_TABLE_SIZE;
                if (hash_table[newIndex].type == NONE)
                {
                    hash_table[newIndex].type = NON_TERMINAL;
                    hash_table[newIndex].sym.nonterminal = i;
                    break;
                }
                probe++;
            }
        }
    }
    return num_collisions;
}

int addTerm(){
    int num_collisions = 0;
    for (int i = 0; i < NUM_TERMINALS; i++)
    {
        int index = calculateHash(terminals[i]);

        if (hash_table[index].type == NONE)
        {
            hash_table[index].type = TERMINAL;
            hash_table[index].sym.terminal = i;
        }

        else
        {
            int probe = 1;
            int newIndex;
            while (1)
            {
                num_collisions++;
                newIndex = (index + probe * probe) % HASH_TABLE_SIZE;
                if (hash_table[newIndex].type == NONE)
                {
                    hash_table[newIndex].type = TERMINAL;
                    hash_table[newIndex].sym.terminal = i;
                    break;
                }
                probe++;
            }
        }
    }
    return num_collisions;
}

void create_hashTable()
{
    int num_collisions = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hash_table[i].type = NONE;
    }


    num_collisions += addnonTerm();
    num_collisions += addTerm();

    char *eps = "EPSILON";
    int eps_index = calculateHash(eps);
    if (hash_table[eps_index].type == NONE)
    {
        hash_table[eps_index].type = __EPSILON;
    }
    else
    {

        int probe = 1;
        int newIndex;
        while (1)
        {
            num_collisions++;
            newIndex = (eps_index + probe * probe) % HASH_TABLE_SIZE;
            if (hash_table[newIndex].type == NONE)
            {
                hash_table[newIndex].type = __EPSILON;
                break;
            }
            probe++;
        }
    }

    printf("Collisions : %d", num_collisions);
}

int getIndex(char *tok)
{
    int currIndex = calculateHash(tok);

    // check if the token exists at the calculated index
    if (hash_table[currIndex].type != NONE)
    {
        if (hash_table[currIndex].type == TERMINAL)
        {
            if (strcmp(terminals[hash_table[currIndex].sym.terminal], tok) == 0)
                return currIndex;
        }
        else if (hash_table[currIndex].type == NON_TERMINAL)
        {
            if (strcmp(nonterminals[hash_table[currIndex].sym.nonterminal], tok) == 0)
                return currIndex;
        }
        else if (hash_table[currIndex].type == EPSILON)
        {
            if (strcmp("EPSILON", tok) == 0)
                return currIndex;
        }
    }

    int probe = 1;
    int newIndex;

    while (1)
    {
        newIndex = (currIndex + probe * probe) % HASH_TABLE_SIZE;
        if (hash_table[newIndex].type == NONE)
        {
            return -1;
        }
        else if (hash_table[newIndex].type == TERMINAL && strcmp(terminals[hash_table[newIndex].sym.terminal], tok) == 0)
        {
            return newIndex;
        }
        else if (hash_table[newIndex].type == NON_TERMINAL && strcmp(nonterminals[hash_table[newIndex].sym.nonterminal], tok) == 0)
        {
            return newIndex;
        }
        else if (hash_table[newIndex].type == EPSILON && strcmp("EPSILON", tok) == 0)
        {
            return newIndex;
        }
        probe++;
    }
}