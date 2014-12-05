#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "BRDtree.h"
#include "color.h"

/*
  =============================================
  Briandais tree primitives.
  =============================================
*/

/* Returns a empty Briandais tree. */
BRDtree *emptyBRDtree()
{
  BRDtree *brd = (BRDtree *) malloc(sizeof(BRDtree));
  brd->key   = '\0';
  brd->child = NULL;
  brd->next  = NULL;
  
#ifdef DEBUG
  dbg;
#endif
  return brd;
}

/* Checks if a Briandais tree is empty. */
int isEmpty(BRDtree *Tree)
{
#ifdef DEBUG
  dbg;
#endif
  if (Tree == NULL ||
      (Tree->key   == '\0' &&
       Tree->child == NULL &&
       Tree->next  == NULL))
    return TRUE;
  else
    return FALSE;
}

/* Returns a Briandais tree (key, child, next). */
BRDtree *newBRDtree(char key, BRDtree *child, BRDtree *next)
{
  BRDtree *brd = (BRDtree *) malloc(sizeof(BRDtree));
  brd->key   = key;
  brd->child = child;
  brd->next  = next;
  
#ifdef DEBUG
  dbg;
#endif
  return brd;
}

/* Returns a Briandais tree build from the Word word. */
BRDtree *buildBRDtree(char *word)
{
#ifdef DEBUG
  dbg;
#endif
  if(strcmp(word,"\0") == 0)
    {
      return emptyBRDtree();
    }
  else
    {
      return newBRDtree(head(word),buildBRDtree(tail(word)), NULL);
    }
}

/* Add the Word word to the Briandais tree. */
BRDtree *addBRDtree(char *word, BRDtree *T)
{
  if(isEmpty(T))
    {
      if(strcmp(word,"\0") == 0)
	{
	  free(word);	
	  return T;
	}
      return buildBRDtree(word);
    }
  
  if(strcmp(word,"\0") == 0)
    {
      if(T->key == '\0'){
	free(word);
	return T;
      }
      return newBRDtree('\0', NULL, T);
    }
  
  if(head(word) - T->key < 0)
    {
      return newBRDtree(head(word), buildBRDtree(tail(word)), T);
    }
  else if(head(word) - T->key > 0)
    {
      return newBRDtree(T->key, T->child, addBRDtree(word,T->next));
    }
  else
    {
      // check if we're the last letter of the word
      if(isEmpty(T->child)){
	if(strcmp(tail(word),"\0") == 0)
	  return T;
	return newBRDtree(T->key, 
			  newBRDtree('\0', NULL, 
				     buildBRDtree(tail(word))), 
			  T->next);
      }
      return newBRDtree(T->key, addBRDtree(tail(word),T->child), T->next);
    }
}

/* Returns the first part of the Word word. */
char head(char *string)
{
#ifdef DEBUG
  dbg;
#endif
  return string[0];
}

/* Returns the rest of the Word word. */
char *tail(char * string)
{
  int n = strlen(string);
  char * new_string = (char *) malloc(sizeof(char) * n);
  int i;
  for(i = 0; i < n; i++)
    {
      new_string[i] = string[i + 1];
    }
  return new_string;
}


/*
  =============================================
  Advanced functions of a Briandais tree.
  =============================================
*/

/* Search the Word word in the tree (return 1 if find else 0). */
int searchBRDtree(char *word, BRDtree *T)
{
  if(strcmp(word, "") == 0)
    {
      return isEmpty(T);
    }
  else if(isEmpty(T)) return FALSE;
  if(head(word) < T->key) return FALSE;
  else if(head(word) == T->key) return searchBRDtree(tail(word), T->child);
  else return searchBRDtree(word, T->next);
}


/* Count the number of word in the tree. */
int countWordsBRDtree(BRDtree *T)
{
  if(T == NULL)
    return 0;
  if(T->key == '\0'){
    return 1 + countWordsBRDtree(T->next);
  }
  return countWordsBRDtree(T->child) + countWordsBRDtree(T->next);
}


/* List the words of the tree in the alphabetical order. */
void insideListWordsBRDtree(BRDtree *Tree, wordList **list, char *word)
{
  if (Tree == NULL) return;
  int size = strlen(word),i;
  char *nw = (char *)malloc(sizeof(char) * (size+1));
  
  for (i=0; i<size; i++)
    nw[i] = word[i];
  nw[i] = Tree->key;

  if (Tree->key == '\0') addWordList(nw, list);
  
  insideListWordsBRDtree(Tree->child, list, nw);
  insideListWordsBRDtree(Tree->next, list, word);
}

wordList *listWordsBRDtree(BRDtree *Tree)
{
  wordList *list = (wordList *)malloc(sizeof(wordList));
  list->word = "";
  list->next = NULL;
  insideListWordsBRDtree(Tree, &list, "");
  
  return list;
}

/* Count the number of NIL pointers in the tree. */
int countNullBRDtree(BRDtree *Tree)
{
  if (Tree == NULL) return 1;
  if (isEmpty(Tree)) return 2;
  return countNullBRDtree(Tree->child) + countNullBRDtree(Tree->next);
}

/* Returns the height of the tree. */
int heightBRDtree(BRDtree *Tree)
{
  if (isEmpty(Tree)) return 0;
  return max(1 + heightBRDtree(Tree->child), heightBRDtree(Tree->next));
}

/* Returns the average depth of the leaves of the tree. */
void insideAverageBRDtree(BRDtree *Tree, int *level, int *count, int currLevel)
{
  if (Tree == NULL) return;
  (*level) += currLevel;
  (*count)++;
  if (Tree->child != NULL) insideAverageBRDtree(Tree->child, level, count, currLevel+1);
  if (Tree->next != NULL)  insideAverageBRDtree(Tree->next, level, count, currLevel);
}

double averageLevelBRDtree(BRDtree *Tree)
{
  int level=0, count=0, currLevel=1;
  insideAverageBRDtree(Tree, &level, &count, currLevel);
  if (count == 0) return (double)FALSE;
  return (double) level/count;
}

/* Count the numbre of word in the tree having to prefix prefix. */
int countPrefixBRDtree(char *prefix, BRDtree *Tree)
{
  if (strcmp(prefix, "") == 0) return countWordsBRDtree(Tree);
  if (head(prefix) < Tree->key) return FALSE;
  else if (head(prefix) > Tree->key) return countPrefixBRDtree(prefix, Tree->next);
  else return countPrefixBRDtree(tail(prefix), Tree->child);
}

/* Delete the Word word from the tree. */
BRDtree *delBRDtree(char *word, BRDtree *Tree)
{
  if (Tree == NULL) return NULL;
  if (isEmpty(Tree) && strcmp(word, "") == 0) return Tree->next;
  if (Tree->key == head(word))
    {
      BRDtree *child = delBRDtree(tail(word), Tree->child);
      if (child == NULL) return Tree->next;
      else return newBRDtree(Tree->key, child, Tree->next);
    }
  else if (Tree->key > head(word)) return Tree;
  else return newBRDtree(Tree->key, Tree->child, delBRDtree(word, Tree->next));
}

/*
  =============================================
  Complex functions of a Briandais tree.
  =============================================
*/

/* Merge two Briandais tree in one */
BRDtree *mergeBRDtree(BRDtree *Tree1, BRDtree *Tree2)
{
  if(Tree1 == NULL) return Tree2;
  if(Tree2 == NULL) return Tree1;
  
  if(Tree2->key < Tree1->key)
    return newBRDtree(Tree2->key, Tree2->child, mergeBRDtree(Tree1, Tree2->next));
  else if(Tree2->key > Tree1->key)
    return newBRDtree(Tree1->key, Tree1->child, mergeBRDtree(Tree1->next, Tree2));
  else
    return newBRDtree(Tree1->key, mergeBRDtree(Tree1->child, Tree2->child),
		                  mergeBRDtree(Tree1->next, Tree2->next));
}

/*
  =============================================
  Useful functions of a Briandais tree.
  =============================================
*/

/* Erase the Briandais tree. */
void freeBRDtree(BRDtree * T)
{
  if(T == NULL)
    return;
  else
    {
      freeBRDtree(T->child);
      freeBRDtree(T->next);
      free(T);
    }
}

/* Print the Briandais tree */
void printBRDtree(BRDtree *Tree)
{
  if (Tree == NULL) return;
  if (Tree->key == '\0' && Tree->child == NULL) printf("\\0\n");
  else
    printf("%c",Tree->key);
  printBRDtree(Tree->child);
  printBRDtree(Tree->next);
}

/*
  =============================================
  GNUPLOT
  =============================================
*/

/* Print a Briandais tree for gnuplot */
int doPlotBRDtree(BRDtree *Tree, long X, long Y, int next)
{
  int widthChild;
  if (Tree == NULL) return EXIT_SUCCESS;
  if (next == 1)
    {
      if (Tree->key == '\0') printf(". %ld %ld\n\n",X,Y);
      else                   printf("%c %ld %ld\n\n",Tree->key, X, Y);
    }

  if (Tree->key == '\0') printf(". %ld %ld\n",X,Y);
  else                   printf("%c %ld %ld\n",Tree->key, X, Y);
  
  widthChild = doPlotBRDtree(Tree->child, X, Y + JMP_Y, 0);
  widthChild = widthChild < 10?10:widthChild;
  printf("\n");
  
  if (Tree->key == '\0') printf(". %ld %ld\n",X,Y);
  else                   printf("%c %ld %ld\n",Tree->key, X, Y);

  return (widthChild) + doPlotBRDtree(Tree->next, (X+widthChild), Y, 1);
}

void plotBRDtree(BRDtree *Tree)
{
  doPlotBRDtree(Tree,0,0,0);
}

/*
  =============================================
  INIT WITH FILES
  =============================================
*/

/* Add the file to the Briandais tree */
BRDtree *addFileToBRDtree(char *file, BRDtree *tree)
{
  FILE *f = fopen(file, "r");
  char *buffer;
  int i;
  
  if(f == NULL)
    {
      fprintf(stderr,"fopen failed : %s\n", file);
      return NULL;
    }
  
  buffer = malloc(sizeof(char) * 128);
  for(i = 0; i < 128; i++) buffer[i] = '\0';
  while(fscanf(f,"%s", buffer) != EOF)
    {
      tree = addBRDtree(buffer, tree);
      for(i = 0; i < 128; i++) buffer[i] = '\0';
    }
  
  fclose(f);
  #ifdef VERBOSE
  fprintf(stderr,"+[Add] %s\n",file);
  #endif
  return tree;
}

/* Add files of the directory dir to the Briandais tree */
BRDtree *addDirToBRDtree(char *dir, BRDtree *tree)
{
  #ifdef DEBUG
  dbg;
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
      tree = addFileToBRDtree(path, tree);
  }
  
  closedir(d);
  return tree;
}

/* Delete the words in the Briandais tree of the File file */
BRDtree *delFileToBRDtree(char *file, BRDtree *tree)
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
      tree = delBRDtree(buffer, tree);
      for (i=0; i<128; i++) buffer[i] = '\0';
    }

  fclose(f);
  #ifdef VERBOSE
  fprintf(stderr,"+[Del] %s\n",file);
  #endif
  return tree;
}

/* Delete the words in the Briandais tree of files of the directory */
BRDtree *delDirToBRDtree(char *dir, BRDtree *tree)
{
  DIR *d = opendir(dir);
  struct dirent *in;
  char path[256];
  
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
      tree = delFileToBRDtree(path,tree);
    }

  closedir(d);
  return tree;
}
