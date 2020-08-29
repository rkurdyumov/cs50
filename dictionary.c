// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 131072;  // 2^17, large dict has 143091 words.

// Hash table
node *table[N];  // Default initialized to NULL.

int num_words_loaded = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *curr = table[hash(word)];
    while (curr) {
        if (strcasecmp(curr->word, word) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++) {
        hash = ((hash << 5) + hash) + tolower(word[i]);  // djb2 hash function
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open dictionary file %s.\n", dictionary);
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF) {
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            fprintf(stderr, "Failed to allocate node memory.\n");
            fclose(file);
            unload();
            return false;
        }
        strcpy(n->word, word);
        int i = hash(n->word);
        n->next = table[i];
        table[i] = n;
        num_words_loaded++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num_words_loaded;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++) {
        node *curr = table[i];
        while (curr) {
            node *next = curr->next;
            free(curr);
            curr = next;
        }
    }
    return true;
}
