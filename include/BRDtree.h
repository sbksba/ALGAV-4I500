#ifndef BRDTREE_H
#define BRDTREE_H

#include "tool.h"

/*
  =============================================
  Data structure of a Briandais tree.
  =============================================
*/
typedef struct BRDtree
{
  char key; 
  struct BRDtree *child; 
  struct BRDtree *next; 
}BRDtree;


/*
  =============================================
  Briandais tree primitives.
  =============================================
*/

/* Returns a empty Briandais tree. */
BRDtree *emptyBRDtree();

/* Checks if a Briandais tree is empty. */
int isEmpty(BRDtree *Tree);

/* Returns a Briandais tree (key, child, next). */
BRDtree *newBRDtree(char key, BRDtree *child, BRDtree *next);

/* Returns a Briandais tree build from the Word word. */
BRDtree *buildBRDtree(char *word);

/* Add the Word word to the Briandais tree. */
BRDtree *addBRDtree(char *word, BRDtree *Tree);

/* Returns the first part of the Word word. */
char head(char *string);

/* Returns the rest of the Word word. */
char *tail(char *string);

/*
  =============================================
  Advanced functions of a Briandais tree.
  =============================================
*/

/* Search the Word word in the tree (return 1 if find else 0). */
int searchBRDtree(char *word, BRDtree *T);

/* Count the number of word in the tree. */
int countWordsBRDtree(BRDtree *T);

/* List the words of the tree in the alphabetical order. */
void insideListWordsBRDtree(BRDtree *Tree, wordList **list, char *word);
wordList *listWordsBRDtree(BRDtree *Tree);

/* Count the number of NIL pointers in the tree. */
int countNullBRDtree(BRDtree *Tree);

/* Returns the height of the tree. */
int heightBRDtree(BRDtree *Tree);

/* Returns the average depth of the leaves of the tree. */
void insideAverageBRDtree(BRDtree *Tree, int *level, int *count, int currLevel);
double averageLevelBRDtree(BRDtree *Tree);

/* Count the numbre of word in the tree having to prefix prefix. */
int countPrefixBRDtree(char *prefix, BRDtree *Tree);

/* Delete the Word word from the tree. */
BRDtree *delBRDtree(char *word, BRDtree *Tree);

/*
  =============================================
  Complex functions of a Briandais tree.
  =============================================
*/

/* Merge two Briandais tree in one */
BRDtree *mergeBRDtree(BRDtree *Tree1, BRDtree *Tree2);

/*
  =============================================
  Useful functions of a Briandais tree.
  =============================================
*/

/* Erase the Briandais tree. */
void freeBRDtree(BRDtree *T);

/* Print the Briandais tree */
void printBRDtree(BRDtree *Tree);

/*
  =============================================
  GNUPLOT
  =============================================
*/

/* Print a Briandais tree for gnuplot */
int doPlotBRDtree(BRDtree *Tree, long X, long Y, int next);
void plotBRDtree(BRDtree *Tree);

/*
  =============================================
  INIT WITH FILES
  =============================================
*/

/* Add the file to the Briandais tree */
BRDtree *addFileToBRDtree(char *file, BRDtree *tree);

/* Add files of the directory dir to the Briandais tree */
BRDtree *addDirToBRDtree(char *dir, BRDtree *tree);


#endif
