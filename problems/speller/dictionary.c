// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>



#include "dictionary.h"
// Represents a node in a hash table
const unsigned int N = 27;

typedef struct node
{
    bool is_word;
    struct node *children[N];
    }
node;

// TODO: Choose number of buckets in hash table
void unloadnodes(node *p);


// Hash table
node *Parent;


//number of words in dictonery
int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //printf("i am checking now\n");
    node *current = Parent;
    node *next;
    //printf("current assigned\n");
    int i = 0;
    while (word[i] != '\0')
    {
        //printf("checking letter %i\n", i);


        current = current -> children[hash(&word[i])];

        if (current == NULL)
        {
            return false;
        }

        i++;
    }
    return current -> is_word;
}





// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (*word == 39)
    {
        return 26;
    }
    else
    {
        return (tolower(*word) - 'a');
    }


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    Parent = malloc(sizeof(node));

    for (int i = 0 ; i < N; i++)
    {
        Parent ->  children[i] = NULL;
    }

    // printf("start louding\n");
    FILE *dicFile = fopen(dictionary, "r");

    // printf("Parent was made\n");

    node *current = Parent;
    char c;
    int hash_c;
    node *last;

    // printf("current assignesd\n");

    while (fread(&c, sizeof(char), 1, dicFile))
    {
        if (c == '\n')
        {
            words++;
            current -> is_word = true;
            current = Parent;
        }
        else
        {
            hash_c = hash(&c);

            last = current;

            current = current -> children[hash_c];

            if (current == NULL)
            {
                last -> children[hash_c] = malloc(sizeof(node));

                for (int i = 0 ; i < N; i++)
                {
                    last -> children[hash_c] ->  children[i] = NULL;
                }
                last -> children[hash_c] -> is_word = NULL;


                current =  last -> children[hash_c];
            }

        }
    }



    //free(current);
    fclose(dicFile);
    // printf("end of loud\n");
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
    unloadnodes(Parent);
    return true;
}

void unloadnodes(node *p)
{

    node *child;
    for (int i = 0 ; i < N ; i++)
    {
        child = p -> children[i];
        if (child != NULL)
        {
            unloadnodes(child);
        }
    }
    free(p);
    return;
}



