/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int lwd = 0;
int uwd = 0;

typedef struct node
{
  char val[47];
  struct node* forwd;
}node;

node* hashar[26];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
  // TODO
  int n;
  size_t sz = strlen(word);
  char* x = malloc(sizeof(char) * sz + 1);
  if(x == NULL)
  {
    exit(-1);
  }
  for(int i = 0; i < sz; i++)
  {
    x[i] = tolower(word[i]);
  }
  x[sz] = '\0';
  n = x[0] - 'a';
  node* srh = hashar[n];

  while(srh != NULL)
  {
    if(!(strcmp(srh->val, x)))
    {
      free(x);
      return true;
    }
    srh = srh->forwd;
  }
  free(x);
  return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    for(int i = 0; i < 26; i++)
    {
      hashar[i] = NULL;
    }

    char str[47];
    FILE* fl = fopen(dictionary, "r");
    while(fgets(str, sizeof(char) * 47, fl) != NULL)
    {
      int n;
      n = str[0] - 'a';
      int sz = strlen(str);
      node* new = malloc(sizeof(node));
      if(new == NULL)
      {
        exit(-1);
      }
      new->forwd = NULL;
      strncpy(new->val, str, sz - 1);
      if(hashar[n]== 0x00)
      {
        hashar[n] = new;
        lwd++;
      }
      else
      {
        node* tmp = hashar[n];
        while(tmp->forwd != NULL)
        {
          tmp = tmp->forwd; 
        }
        tmp->forwd = new;
        lwd++;
      }
    }
    fclose(fl);

    if(feof)
    {
      return true;
    }
    lwd = 0;
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return lwd;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for(int i = 0; i < 26; i++)
    {
      if(hashar[i] != 0x00)
      {
        node* t = hashar[i];
        node* pt;
        while(t != NULL)
        {
          pt = t;
          t = t->forwd;
          free(pt);
          uwd++;
        }
      }
    }
    if(lwd == uwd)
    {
      return true;
    }
    else
    {
      uwd = 0;
      return false;
    }
}
