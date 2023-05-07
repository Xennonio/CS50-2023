// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

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
int new_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
  // Hash word to obtain a hash value
  int hash_value = hash(word);
  node *head = table[hash_value];

  // Access linked list at that index in the hash table
  node *cursor = head;

  // Traverse linked list, looking for the word (strcasecmp)
  while(cursor != NULL)
  {
    if(strcasecmp(cursor->word, word) == 0)
    {
      return true;
    }
    else
    {
      cursor = cursor->next;
    }
  }

  return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
  return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
  // Open dictionary file
  FILE *file = fopen(dictionary, "r");

  if(file == NULL)
  {
    fclose(file);
    return false;
  }

  // Read strings from file one at a time
  char buffer[LENGTH + 1];

  while(fscanf(file, "%s", buffer) != EOF)
  {
    // Create a new node for each word
    node *n = malloc(sizeof(node));

    if(n == NULL)
    {
      free(n);
      return false;
    }

    strcpy(n->word, buffer);
    n->next = NULL;

    // Hash word to obtain a hash value
    int hash_value = hash(n->word);

    // Insert node into hash table at that location
    node *head = table[hash_value];

    n->next = head;
    table[hash_value] = n;
    new_words++;
  }

  fclose(file);

  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
  return new_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
  for(int index = 0; index < N; index++)
  {
    node *head = table[index];
    node *cursor = head;
    node *tmp = head;

    while(cursor != NULL)
    {
      cursor = cursor->next;
      free(tmp);
      tmp = cursor;
    }
  }

  return true;
}
