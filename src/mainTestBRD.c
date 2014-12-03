#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "BRDtree.h"
#include "color.h"

int main()
{
  int cpt1=0,cpt2=0;
  BRDtree * t1 = emptyBRDtree();

  printf("T1 is empty           ");
  if (isEmpty(t1))
    printf(OK);
  else
    printf(FAILED);

  t1 = addBRDtree("a", t1);addVerbose("a");cpt1++;
  t1 = addBRDtree("z", t1);addVerbose("z");cpt1++;
  t1 = addBRDtree("the", t1);addVerbose("the");cpt1++;
  t1 = addBRDtree("t", t1);addVerbose("t");cpt1++;
  t1 = addBRDtree("at", t1);addVerbose("at");cpt1++;
  printf("[ADD] value T1        ");
  if (cpt1==5)
    printf(OK);
  else
    printf(FAILED);
	
  BRDtree * t2 = emptyBRDtree();
  printf("\nT2 is empty           ");
  if (isEmpty(t2))
    printf(OK);
  else
    printf(FAILED);

  t2 = addBRDtree("ba", t2);addVerbose("ba");cpt2++;
  t2 = addBRDtree("ate", t2);addVerbose("ate");cpt2++;
  t2 = addBRDtree("thdde", t2);addVerbose("thdde");cpt2++;
  t2 = addBRDtree("bonjour", t2);addVerbose("bonjour");cpt2++;
  t2 = addBRDtree("atqsdqd", t2);addVerbose("atqsqd");cpt2++;
  printf("[ADD] value T2        ");
  if (cpt2==5)
    printf(OK);
  else
    printf(FAILED);

  /*
    ===============
    TESTS FUNCTIONS
    ===============
  */
  
  BRDtree *tvide = emptyBRDtree();

  printf("\n-- TEST SEARCH --\n");
  if (searchBRDtree("",tvide) == TRUE) {printf("TVIDE : vide FIND     ");printf(OK);}
  else {printf("TVIDE : vide FIND  ");printf(FAILED);}

  tvide = addBRDtree("coucou",tvide);

  if (searchBRDtree("",tvide) == TRUE) {printf("TVIDE : empty word    ");printf(FAILED);}
  else {printf("TVIDE : empty word    ");printf(OK);}

  if (searchBRDtree("at",t1) == TRUE) {printf("T1 : at FIND          ");printf(OK);}
  else {printf("T1 : at FIND  ");printf(FAILED);}

  if (searchBRDtree("bonjour",t1) == TRUE) {printf("T1 : bonjour NOT FIND ");printf("FAILED");}
  else {printf("T1 : bonjour NOT FIND ");printf(OK);}

  if (searchBRDtree("bonjour",t2) == TRUE) {printf("T2 : bonjour FIND     ");printf(OK);}
  else {printf("T2 : bonjour FIND     ");printf(FAILED);}

  if (searchBRDtree("at",t2) == TRUE) {printf("T2 : at NOT FIND      ");printf(FAILED);}
  else {printf("T2 : at NOT FIND      ");printf(OK);}

  /* test count word */
  printf("\n-- TEST COUNT WORDS --\n");
  int ct1 = countWordsBRDtree(t1);
  int ct2 = countWordsBRDtree(t2);

  printf("NB words t1 : %d       ",ct1);
  if (ct1 == 5) printf(OK);
  else printf(FAILED);
  printf("NB words t2 : %d       ",ct2);
  if (ct2 == 5) printf(OK);
  else printf(FAILED);

  /* test count null */
  printf("\n-- TEST COUNT NULL --\n");
  ct1 = countNullBRDtree(t1);
  ct2 = countNullBRDtree(t2);

  printf("NB null t1 : %d       ",ct1);
  if (ct1 == 12) printf(OK); /*5*/
  else printf(FAILED);
  printf("NB null t2 : %d       ",ct2);
  if (ct2 == 27) printf(OK); /*5*/
  else printf(FAILED);

  /* test list word */
  printf("\n-- TEST WORDLIST --\n");
  wordList *list = listWordsBRDtree(t1);
  printf("Create wordList       ");
  if (list == NULL) /* !NULL */
    printf(FAILED);
  else
    printf(OK);

  /* test tree size */
  printf("\n-- TEST TREE SIZE --\n");
  int height = heightBRDtree(t1);
  printf("T1 Height : %d         ",height);
  if (height == 3)
    printf(OK);
  else
    printf(FAILED);

  height = heightBRDtree(t2);
  printf("T2 Height : %d         ",height);
  if (height == 7)
    printf(OK);
  else
    printf(FAILED);

  int level = averageLevelBRDtree(t1);
  printf("T1 Level  : %d         ",level);
  if (level == 2)
    printf(OK);
  else
    printf(FAILED);

  level = averageLevelBRDtree(t2);
  printf("T2 Level  : %d         ",level);
  if (level == 4)
    printf(OK);
  else
    printf(FAILED);

  /* test count prefix */
  printf("\n-- TEST COUNT PREFIX --\n");
  int prefix = countPrefixBRDtree("a",t1);
  printf("T1 NB prefix : %d      ",prefix);
  if (prefix == 2)
    printf(OK);
  else
    printf(FAILED);

  prefix = countPrefixBRDtree("bonjour",t2);
  printf("T2 NB prefix : %d      ",prefix);
  if (prefix == 1)
    printf(OK);
  else
    printf(FAILED);
  
  /* test del word */
  printf("\n-- TEST DEL WORD --\n");
  ct1 = countWordsBRDtree(t1);
  ct2 = countWordsBRDtree(t2);
  #ifdef VERBOSE
  printf("BEFORE | T1 [%d] -- T2 [%d]\n",ct1,ct2);
  printf("T1\n");
  wordList *l = listWordsBRDtree(t1);
  printWordsList(l);
  printf("T2\n");
  l = listWordsBRDtree(t2);
  printWordsList(l);
  #endif
  t1 = delBRDtree("z",t1);
  t2 = delBRDtree("thdde",t2);

  #ifdef VERBOSE
  printf("AFTER  | T1 [%d] -- T2 [%d]\n",countWordsBRDtree(t1),countWordsBRDtree(t2));
  printf("T1\n");
  l = listWordsBRDtree(t1);
  printWordsList(l);
  printf("T2\n");
  l = listWordsBRDtree(t2);
  printWordsList(l);
  #endif
  printf("T1 DEL word 'z'       ");
  if (countWordsBRDtree(t1) == (ct1-1))
    printf(OK);
  else
    printf(FAILED);

  printf("T2 DEL word 'thdde'   ");
  if (countWordsBRDtree(t2) == (ct2-1))
    printf(OK);
  else
    printf(FAILED);

  /* test del word */
  printf("\n-- TEST MERGE TREE --\n");
  BRDtree *t3 = mergeBRDtree(t1,t2);
  int cptT3 = countWordsBRDtree(t3);
  int cptMerge = (countWordsBRDtree(t1))+(countWordsBRDtree(t2));
  printf("T3 MERGE TREE         ");
  if (cptT3 == cptMerge)
    printf(OK);
  else
    printf(FAILED);

  /* test print word */
  printf("\n-- TEST PRINT TREE --\n");
  #ifdef VERBOSE
  l = listWordsBRDtree(t3);
  printWordsList(l);
  printf("---------------\n");
  #endif
  printBRDtree(t3);
  printf("T3 PRINT TREE         ");printf(OK);

  /* test files */
  printf("\n-- TEST ADD FILE --\n");
  BRDtree *tfile = emptyBRDtree(); 
  tfile = addDirToBRDtree("test",tfile);
    
  /* test free tree */
  printf("\n-- TEST FREE TREE --\n");
  cpt1=0;cpt2=0;
  freeBRDtree(t1);cpt1++;
  freeBRDtree(t2);cpt2++;

  printf("T1 Free tree          ");
  if (cpt1 == 1) printf(OK);
  else printf(FAILED);

  printf("T2 Free tree          ");
  if (cpt2 == 1) printf(OK);
  else printf(FAILED);

  return EXIT_SUCCESS;	
} 
