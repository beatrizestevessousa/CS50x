// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int value;
unsigned int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    value = hash(word);
    node *ptr = table[value];

    while (ptr != 0)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, word);
        value = hash(word);

        new_node->next = table[value];
        table[value] = new_node;
        word_count++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *new_node = table[i];

        while (new_node)
        {
            node *tmp = new_node;
            new_node = new_node->next;
            free(tmp);
        }
    }
    return true;
}
