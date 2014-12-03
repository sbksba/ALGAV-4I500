#ifndef TOOL_H
#define TOOL_H

/* 
  =============================================
  Data structure of a list of words.
  =============================================
*/
typedef struct wordList
{
  char * word;
  struct wordList * next;
}wordList;

/*
  =============================================
  Boolean value
  =============================================
*/
#define TRUE 1
#define FALSE 0

/*
  =============================================
  Value for THybrid
  =============================================
*/
#define ONE 1
#define EMPTY '0'
#define NOTEMPTY '1'

/*
  =============================================
  JUMP value for gnuplot
  =============================================
*/
#define JMP_X 10
#define JMP_Y 10

#define dbg printf("FILE : %s -- FUNCTION : %s -- LINE [%d]\n",__FILE__,__FUNCTION__,__LINE__)

void addVerbose (char *word);
int max (int a, int b);
int maxOfThree (int a, int b, int c);

void addWordList(char *word, wordList **list);

/* Print the list of word of the Briandais tree */
void printWordsList(wordList *list);

#endif
