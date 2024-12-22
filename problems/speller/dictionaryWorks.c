// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <strings.h>



#include "dictionary.h"
// Represents a node in a hash table
const unsigned int N = 26;
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
void unloadnodes(node *p);



// Hash table
node *table[N];

//number of words in dictonery
int words = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    if(table[hash(word)] == NULL)
    {
        return false;
    }

    for(node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp -> next)
    {
        if(strcasecmp(tmp -> word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    return (toupper(word[0]) - 'A');


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dicFile = fopen(dictionary, "r");
    if (dicFile == NULL)
    {
        printf("test1 ");
        return false;
    }

    char c;
    int index = 0;


    node *temp = malloc(sizeof(node));
    temp -> next = NULL;

    if(temp == NULL)
    {
        printf("test2 ");
        return false;
    }

    while(fread(&c, sizeof(char), 1, dicFile))
    {
        if (c == '\n')
        {
            temp -> word[index] = '\0';
            index = 0;
            words++;

            int table_index = hash(temp -> word);

            if(table[table_index] == NULL)
            {
                table[table_index] = temp;
            }
            else
            {
                temp -> next = table[table_index];
                table[table_index] = temp;
            }
            temp = malloc(sizeof(node));
            temp -> next = NULL;
        }
        else
        {
            temp -> word[index] = c;
            index++;
        }

    }

    free(temp);
    fclose(dicFile);
    printf("end of loud\n");
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if(table[i] != NULL)
        {
            unloadnodes(table[i]);
        }
    }
    printf("end of unloud\n");
    return true;
}

void unloadnodes(node *p)
{
    if(p == NULL)
    {
        return;
    }

    unloadnodes(p -> next);

    free(p);

    return;
}



