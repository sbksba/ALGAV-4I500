#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "THybrid.h"
#include "BRDtree.h"

/*
  =============================================
  Hybrid trie primitives.
  =============================================
*/

/* Returns a hyrbid trie build from the Word word. */
THybrid *buildTHybrid(char *word)
{
  THybrid *thy = (THybrid *) malloc(sizeof(THybrid));
  thy->key = *word;
  thy->val = EMPTY;
  thy->inf = NULL;
  thy->eq  = NULL;
  thy->sup = NULL;

  return thy;
}

/* Add the Word word to the hybrid trie. */
THybrid *addTHybrid(char *word, THybrid *Trie)
{
  if (Trie == NULL)
    {
      Trie = buildTHybrid(word);
    }
    
  if (*word < Trie->key)
    Trie->inf = addTHybrid(word, Trie->inf);
  else if (*word > Trie->key)
    Trie->sup = addTHybrid(word, Trie->sup);
  else
    {
      if (strlen(word) == 1)
	Trie->val = NOTEMPTY;
      else
	Trie->eq = addTHybrid(++word, Trie->eq);
    }

  return Trie;
}

/*
  =============================================
  Advanced functions of a hybrid trie.
  =============================================
*/

/* Search the Word word in the trie (return 1 if find else 0). */
int searchTHybrid(char *word, THybrid *Trie)
{
  #ifdef VERBOSE
  printf("WD [%c]\n",*word);
  #endif
  if (Trie == NULL) return FALSE;
  else if (strcmp(word,"") == 0)
    {
      if (Trie->val == NOTEMPTY) return TRUE;
      else                       return FALSE;
    }
  else
    {
      if (*word < Trie->key)      return searchTHybrid(word, Trie->inf);
      else if (*word > Trie->key) return searchTHybrid(word, Trie->sup);
      else                        return searchTHybrid(++word, Trie->eq);
    }
}

/* Count the number of word in the trie. */
int countWordsTHybrid(THybrid *Trie)
{
  if(Trie == NULL)
    return 0;
  else 
    {
      if(Trie->val == EMPTY)
	return countWordsTHybrid(Trie->eq) 
	  + countWordsTHybrid(Trie->inf) 
	  + countWordsTHybrid(Trie->sup);
      else
	return 1 + countWordsTHybrid(Trie->eq) 
	  + countWordsTHybrid(Trie->inf) 
	  + countWordsTHybrid(Trie->sup);
    }
}

/* List the words of the trie in the alphabetical order. */
void insideListWordsTHybrid(THybrid *Trie, wordList **list, char *word)
{
  if (Trie == NULL) return;
  int size=strlen(word),i;
  char *nw = (char *)malloc(sizeof(char)*(size+1));

  for (i=0; i<size; i++)
    nw[i] = word[i];
  nw[i] = Trie->key;

  if (Trie->val == NOTEMPTY)
    addWordList(nw, list);

  insideListWordsTHybrid(Trie->eq, list, nw);
  insideListWordsTHybrid(Trie->inf, list, nw);
  insideListWordsTHybrid(Trie->sup, list, nw);
}

wordList *listWordsTHybrid(THybrid *Trie)
{
  wordList *list = (wordList *) malloc(sizeof(wordList));
  list->next = NULL;
  insideListWordsTHybrid(Trie, &list, "");
  return list;
}

/* Count the number of NIL pointers in the trie. */
int countNullTHybrid(THybrid *Trie)
{
  if (Trie == NULL) return 1;
  else
    return  countNullTHybrid(Trie->eq)
      + countNullTHybrid(Trie->inf)
      + countNullTHybrid(Trie->sup);
}

/* Returns the height of the trie. */
int heightTHybrid(THybrid *Trie)
{
  if (Trie == NULL) return 0;
  else
    return 1 + maxOfThree(heightTHybrid(Trie->eq), heightTHybrid(Trie->inf), heightTHybrid(Trie->sup));
}

/* Returns the average depth of the leaves of the hybrid trie. */
void insideAverageTHybrid(THybrid *Trie, int *level, int *count, int currLevel)
{
  if(Trie == NULL) return;
  (*level) += currLevel;
  (*count)++;
  if(Trie->inf != NULL)
    insideAverageTHybrid(Trie->inf, level, count, currLevel + 1);
  if(Trie->eq != NULL)
    insideAverageTHybrid(Trie->eq, level, count, currLevel + 1);
  if(Trie->sup != NULL)
    insideAverageTHybrid(Trie->sup, level, count, currLevel + 1);
}

double averageLevelTHybrid(THybrid *Trie)
{
  int level=0, count=0, currLevel=0;
  insideAverageTHybrid(Trie, &level, &count, currLevel);
  if (count == 0) return (double) 0;
  return (double) level/count;
}

/* Count the numbre of word in the trie having to prefix prefix. */
int countPrefixTHybrid(char *prefix, THybrid *Trie)
{
  if (strcmp(prefix,"") == 0)
    {
      return countWordsTHybrid(Trie);
    }
  if (*prefix < Trie->key)
    {
      return countPrefixTHybrid(prefix, Trie->inf);
    }
  else if (*prefix > Trie->key)
    {
      return countPrefixTHybrid(prefix, Trie->sup);
    }
  else
    {
      return countPrefixTHybrid(++prefix, Trie->eq);
    }
}

/* Delete the Word word from the trie. */
THybrid *delTHybrid(char *word, THybrid *Trie)
{
  if(Trie == NULL)
    return NULL;
  else if(strcmp(word,"") == 0)
    {
      if(Trie->val == NOTEMPTY)
	{
	  if(Trie->eq != NULL)
	    {
	      Trie->val = EMPTY;
	    }
	  else if(Trie->inf != NULL)
	    {
	      Trie->val = EMPTY;
	      Trie->eq = Trie->inf;
	      Trie->inf = NULL;
	    }
	  else if(Trie->sup != NULL)
	    {
	      Trie->val = EMPTY;
	      Trie->eq = Trie->sup;
	      Trie->sup = NULL;
	    }
	  else
	    {
	      free(Trie);
	      Trie = NULL;
	    }
	}
      return Trie;
    }
  else
    {
      if(*word < Trie->key)
	{
	  Trie->inf = delTHybrid(word, Trie->inf);
	}
      else if(*word > Trie->key)
	{
	  Trie->sup = delTHybrid(word, Trie->sup);
	}
      else
	{
	  Trie->eq = delTHybrid(++word, Trie->eq);
	}
      if(Trie->inf == NULL && Trie->sup == NULL && Trie->eq == NULL)
	{
	  free(Trie);
	  Trie = NULL;
	}
      else if(Trie->eq == NULL && Trie->inf != NULL)
	{
	  Trie->eq = Trie->inf;
	  Trie->inf = NULL;
	}
      else if(Trie->eq == NULL && Trie->sup != NULL)
	{
	  Trie->eq = Trie->sup;
	  Trie->sup = NULL;
	}
      return Trie;
    }
}

/*
  =============================================
  Complex functions of a hybrid trie.
  =============================================
*/

/* Change a hybrid trie in a Briandais tree */
void tmpToBRDtree (THybrid *trie, BRDtree *tree, char *word)
{
  char *nw;
  int size,i;
  
  if (trie == NULL){return;}
 
  size = strlen(word);
  nw = (char *)malloc(sizeof(char)*(size+1));
  
  for (i=0; i<size; i++)
    nw[i] = word[i];
  nw[i] = trie->key;
  
  if (trie->val == NOTEMPTY)
    tree = addBRDtree(nw,tree);
  
  tmpToBRDtree(trie->eq, tree, nw);
  tmpToBRDtree(trie->inf, tree, word);
  tmpToBRDtree(trie->sup, tree, word);
}

BRDtree *THybridToBRDtree (THybrid *Trie)
{
  BRDtree *brd = emptyBRDtree();
  tmpToBRDtree(Trie, brd, "");
  return brd;
}

/* Test if a hybrid trie is balanced */
int isBalancing (THybrid *trie)
{
  if (trie == NULL)
    return TRUE;
  else
    {
      if (trie->val == EMPTY)
	return TRUE;
      if (isBalancing(trie->eq) && isBalancing(trie->inf) && isBalancing(trie->sup) && fabs(heightTHybrid(trie->sup) - heightTHybrid(trie->inf)) )
	return TRUE;
      else
	return FALSE;
    }
}

void leftRotate (char n){ (void)n;}
void rightRotate (char n){(void)n;}
void *rebalancing (THybrid *trie){}
THybrid *addTHybridRebalancing (THybrid *trie, char *word)
{
  return trie;
}

/*
  =============================================
  Useful functions of a hybrid trie.
  =============================================
*/

/* Erase the Briandais tree. */
void freeTHybrid(THybrid * Trie)
{
  if (Trie == NULL) return;
  else
    {
      freeTHybrid(Trie->inf);
      freeTHybrid(Trie->eq);
      freeTHybrid(Trie->sup);
      free(Trie);
    }
}

/*
  =============================================
  GNUPLOT
  =============================================
*/

/* Print a hybrid trie for gnuplot */
int width (THybrid *Trie)
{
  if (Trie == NULL) return 0;
  else
    {
      if (Trie->inf == NULL && Trie->eq == NULL && Trie->sup == NULL) return 1;
      else return (width(Trie->inf) + width(Trie->eq) + width(Trie->sup));
    }
}

int widthR(THybrid *Trie)
{
  if (Trie == NULL) return 0;
  else return widthR(Trie->eq) + width(Trie->sup);
}

int widthL(THybrid *Trie)
{
  if (Trie == NULL) return 0;
  else return widthL(Trie->eq) + width(Trie->sup);
}

void doPlotTHybrid(THybrid *Trie, int X, int Y)
{
  if(Trie == NULL)
    return;
  printf("%c %d %d\n", Trie->key, X, Y);
  doPlotTHybrid(Trie->inf, X - (widthL(Trie->eq) + widthR(Trie->inf) + 1) * JMP_X, Y + JMP_Y);
  
  printf("%c %d %d\n", Trie->key, X, Y);
  doPlotTHybrid(Trie->eq, X, Y + JMP_Y);
  
  printf("%c %d %d\n", Trie->key, X, Y);
  
  doPlotTHybrid(Trie->sup, X + (widthR(Trie->eq) + widthL(Trie->sup)+ 1) * JMP_X, Y + JMP_Y);
  printf("\n");
}

void plotTHybrid(THybrid *Trie)
{
  doPlotTHybrid(Trie,0,0);
}

/*
  =============================================
  INIT WITH FILES
  =============================================
*/

/* Add the file to the hybrid trie */
THybrid *addFileToTHybrid(char *file, THybrid *trie)
{
  FILE *f = fopen(file, "r");
  char *buffer;
  int i;
  if (f == NULL)
    {
      fprintf(stderr,"fopen failed : %s\n",file);
      return NULL;
    }
  buffer = malloc(sizeof(char)*128);
  for(i = 0; i < 128; i++) buffer[i] = '\0';
  while(fscanf(f,"%s", buffer) != EOF)
    {
      trie = addTHybrid(buffer, trie);
      for(i = 0; i < 128; i++) buffer[i] = '\0';
    }
  fclose(f);
  #ifdef VERBOSE
  fprintf(stderr,"+[Add] %s\n", file);
  #endif
  return trie;
}

/* Add files of the directory dir to the hybrid trie */
THybrid *addDirToTHybrid(char *dir, THybrid *trie)
{
  #ifdef VERBOSE
  fprintf(stderr,"\n-- ADD DIR THYBRIDE --\n");
  #endif

  DIR *d = opendir(dir);
  struct dirent *entry;
  char path [256];
  if(d == NULL)
    {
      fprintf(stderr,"opendir failed\n");
      return NULL;
    }
  
  while((entry = readdir(d)))
    {
      if(!strcmp(entry->d_name, "."))
	continue;
      if(!strcmp(entry->d_name, ".."))
	continue;
  
      strcpy(path, dir);
      strcat(path, "/");
      strcat(path, entry->d_name);
      trie = addFileToTHybrid(path, trie);
  }
  
  closedir(d);
  return trie;
}

/* Delete the words in the hybrid trie of the File file */
THybrid *delFileToTHybrid(char *file, THybrid *trie)
{
  FILE *f;
  char *buffer;
  int i;
  
  f = fopen(file,"r");
  if (f == NULL)
    {
      fprintf(stderr,"fopen failed\n");return NULL;
    }
  
  buffer = malloc(sizeof(char) * 128);
  for (i=0; i<128; i++) buffer[i] = '\0';
  while (fscanf(f, "%s", buffer) != EOF)
    {
      trie = delTHybrid(buffer, trie);
      for (i=0; i<128; i++) buffer[i] = '\0';
    }

  fclose(f);
  #ifdef VERBOSE
  fprintf(stderr,"+[Del] %s\n",file);
  #endif
  return trie;
}

/* Delete the words in the hybrid trie of files of the directory */
THybrid *delDirToTHybrid(char *dir, THybrid *trie)
{
  DIR *d = opendir(dir);
  struct dirent *in;
  char path[256];
  
  #ifdef VERBOSE
  fprintf(stderr,"\n-- DEL DIR THYBRIDE --\n");
  #endif

  if (dir == NULL)
    {
      fprintf(stderr,"opendir failed\n");
      return NULL;
    }

  while ( (in = readdir(d)) )
    {
      if (!strcmp(in->d_name, ".")) continue;
      if (!strcmp(in->d_name, "..")) continue;
      sprintf(path, "%s/%s", dir, in->d_name);
      trie = delFileToTHybrid(path,trie);
    }

  closedir(d);
  return trie;
}
