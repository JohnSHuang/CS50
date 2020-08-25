// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int key = hash(word);
    for (node *tempNode = table[key]; tempNode != NULL; tempNode = tempNode->next)
    {
        if (strcasecmp(word, tempNode->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    int n = tolower(word[0]);
    return n % 26;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char tempWord[LENGTH + 1];
    while (fscanf(file, "%s", tempWord) != EOF)
    {
        node *tempNode = malloc(sizeof(node));

        strcpy(tempNode->word, tempWord);

        int key = hash(tempWord);

        if (table[key] == NULL)
        {
            tempNode->next = NULL;
            table[key] = tempNode;
        }
        else
        {
            tempNode->next = table[key];
            table[key] = tempNode;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *tempNode = table[i]; tempNode != NULL; tempNode = tempNode->next)
        {
            count++;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tempNode = table[i];
        while (tempNode != NULL)
        {
            node *ttempNode = tempNode->next;
            free(tempNode);
            tempNode = ttempNode;
        }
        table[i] = NULL;
    }
    return true;
}
