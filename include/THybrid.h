#ifndef THYBRID_H
#define THYBRID_H

#include "tool.h"
#include "BRDtree.h"

/*
  =============================================
  Data structure of a hybrid trie.
  =============================================
*/
typedef struct THybrid
{
  char key;
  char val;
  struct THybrid *inf;
  struct THybrid *eq;
  struct THybrid *sup;
}THybrid;

/*
  =============================================
  Hybrid trie primitives.
  =============================================
*/

/* Returns a hyrbid trie build from the Word word. */
THybrid *buildTHybrid(char *word);

/* Add the Word word to the hybrid trie. */
THybrid *addTHybrid(char *word, THybrid *Trie);

/*
  =============================================
  Advanced functions of a hybrid trie.
  =============================================
*/

/* Search the Word word in the trie (return 1 if find else 0). */
int searchTHybrid(char *word, THybrid *Trie);

/* Count the number of word in the trie. */
int countWordsTHybrid(THybrid *Trie);

/* List the words of the trie in the alphabetical order. */
void insideListWordsTHybrid(THybrid *Trie, wordList **list, char *word);
wordList *listWordsTHybrid(THybrid *Trie);

/* Count the number of NIL pointers in the trie. */
int countNullTHybrid(THybrid *Trie);

/* Returns the height of the trie. */
int heightTHybrid(THybrid *Trie);

/* Returns the average depth of the leaves of the trie. */
void insideAverageTHybrid(THybrid *Trie, int *level, int *count, int currLevel);
double averageLevelTHybrid(THybrid *Trie);

/* Count the numbre of word in the trie having to prefix prefix. */
int countPrefixTHybrid(char *prefix, THybrid *Trie);

/* Delete the Word word from the trie. */
THybrid *delTHybrid(char *word, THybrid *Trie);

/*
  =============================================
  Complex functions of a hybrid trie.
  =============================================
*/

/* Change a hybrid trie in a Briandais tree */
void tmpToBRDtree (THybrid *trie, BRDtree *tree, char *word);
BRDtree *THybridToBRDtree (THybrid *Trie);

/*
  =============================================
  Useful functions of a hybrid trie.
  =============================================
*/

/* Erase the hybrid trie. */
void freeTHybrid(THybrid * Trie);

/* Print the list of word of the hybrid trie */
void printWordsList(wordList *list);

/*
  =============================================
  GNUPLOT
  =============================================
*/

/* Print a hybrid trie for gnuplot */
int width (THybrid *Trie);
int widthR(THybrid *Trie);
int widthL(THybrid *Trie);

void doPlotTHybrid(THybrid *Trie, int X, int Y);
void plotTHybrid(THybrid *Trie);

/*
  =============================================
  INIT WITH FILES
  =============================================
*/

/* Add the file to the hybrid trie */
THybrid *addFileToTHybrid(char *file, THybrid *trie);

#endif
