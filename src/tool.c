#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tool.h"

void addVerbose (char *word)
{
  unsigned int size = strlen(word);
  if (size == 0) exit(0);
  #ifdef VERBOSE
  unsigned int i;
  printf("\t[ADD] ");
  for(i=0; i<size; i++)
    printf("%c",word[i]);
  printf("\n");
  #endif
}

int max (int a, int b)
{
  return a>b?a:b;
}

int maxOfThree (int a, int b, int c)
{
  return ((a>b)?a:b)>c?((a>b)?a:b):c;
}

void addWordList(char *word, wordList **list)
{
  wordList *nwl = (wordList *)malloc(sizeof(wordList));
  nwl->word = word;
  nwl->next = *list;
  *list = nwl;
}

/* Print the list of word of the Briandais tree */
void printWordsList(wordList *list)
{
  while (list != NULL)
    {
      printf("\t-%s\n",list->word);
      list=list->next;
    }
}
