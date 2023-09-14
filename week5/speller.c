#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in the hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Compute the hash value for the word
    unsigned int index = hash(word);

    // Traverse the linked list at the hash table index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare the word with the current node's word
        if (strcasecmp(word, cursor->word) == 0)
        {
            // Word found in the dictionary
            return true;
        }
        cursor = cursor->next;
    }

    // Word not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Compute the hash value by summing the ASCII values of the first two characters
    // and taking the modulo of the number of buckets
    return (toupper(word[0]) + toupper(word[1])) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Unable to open dictionary file.\n");
        return false;
    }

    // Clear the hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer to store each word read from the file
    char word[LENGTH + 1];

    // Read words from the file and insert them into the hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for the word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            printf("Memory allocation failed.\n");
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Compute the hash value for the word
        unsigned int index = hash(word);

        // Insert the new node into the hash table
        if (table[index] == NULL)
        {
            // The bucket is empty, insert the new node directly
            table[index] = new_node;
        }
        else
        {
            // There is already a node in the bucket, append the new node at the beginning
            new_node->next = table[index];
            table[index] = new_node;
        }
    }

    // Close the dictionary file
    fclose(file);

    // Loading successful
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int word_count = 0;

    // Traverse the hash table
    for (int i = 0; i < N; i++)
    {
        // Count the nodes in each bucket
        node *cursor = table[i];
        while (cursor != NULL)
        {
            word_count++;
            cursor = cursor->next;
        }
    }

    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Traverse the hash table
    for (int i = 0; i < N; i++)
    {
        // Free the nodes in each bucket
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    // Unloading successful
    return true;
}
