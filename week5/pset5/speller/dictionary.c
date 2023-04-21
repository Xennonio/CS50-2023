// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

#define N 28

// Represents a node in a hash table
typedef struct node
{
  char word[LENGTH + 1];
  struct node *next;
}
node;

// Number of words in hash table
unsigned int nw = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
  node *cursor = table[hash(word)]->next;
  while(cursor != NULL)
  {
    if(strcasecmp(cursor->word, word) == 0)
    {
      return true;
    }
    cursor = cursor->next;
  }
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
  // input: a word
  // output: an index between 0 and N - 1 to use in table[index]
  for(int i = 0; i < 26; i++){
    if(tolower(word[0]) == 'a' + i)
    {
      return i;
    }
  }
  if(tolower(word[0]) == 39)
  {
    return 26;
  }
  return 27;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
  // Open the dictionary file
  FILE *file = fopen(dictionary, "r");

  if(file == NULL)
  {
    return false;
  }

  char buffer[LENGTH + 1];

  for(int i = 0; i < N; i++)
  {
    table[i]->next = NULL;
  }

  // Read the strings of the file one at a time
  while(fscanf(file, "%s", buffer) != EOF)
  {
    // Creates a new node to each readed string
    node *n = malloc(sizeof(node));

    if(n != NULL)
    {
      strcpy(n->word, buffer);
    }
    else
    {
      return false;
    }

    // Insert a node in the Hash Table on the specified location by the Hash Value
    n->next = table[hash(n->word)]->next;
    table[hash(n->word)]->next = n;
    nw++;
  }

  fclose(file);

  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
  return nw;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
  node *cursor = malloc(sizeof(node));
  node *tmp = malloc(sizeof(node));
  if(cursor == NULL || tmp == NULL)
  {
    return false;
  }

  for(int i = 0; i < N; i++)
  {
    tmp = table[i]->next;
    cursor = tmp->next;
    while(cursor != NULL)
    {
      free(tmp);
      tmp = cursor;
      cursor = tmp->next;
    }
  }
  return true;
}