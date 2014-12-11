#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "THybrid.h"
#include "BRDtree.h"
#include "color.h"

int main()
{
  int cpt1=0;
  THybrid *t1=NULL;
  
  t1 = addTHybrid("a", t1);addVerbose("a");cpt1++;
  t1 = addTHybrid("z", t1);addVerbose("z");cpt1++;
  t1 = addTHybrid("the", t1);addVerbose("the");cpt1++;
  t1 = addTHybrid("t", t1);addVerbose("t");cpt1++;
  t1 = addTHybrid("at", t1);addVerbose("at");cpt1++;
  printf("[ADD] value T1        ");
  if (cpt1==5)
    printf(OK);
  else
    printf(FAILED);

  /*
    ===============
    TESTS FUNCTIONS
    ===============
  */
  
  printf("\n-- TEST SEARCH --\n");
  if (searchTHybrid("at",t1) == TRUE) {printf("T1 : at FIND          ");printf(OK);}
  else {printf("T1 : at FIND          ");printf(FAILED);}

  if (searchTHybrid("bonjour",t1) == TRUE) {printf("T1 : bonjour NOT FIND ");printf(FAILED);}
  else {printf("T1 : bonjour NOT FIND ");printf(OK);}

  if (searchTHybrid("the",t1) == TRUE) {printf("T1 : the FIND         ");printf(OK);}
  else {printf("T1 : the FIND         ");printf(FAILED);}

  if (searchTHybrid("a",t1) == TRUE) {printf("T1 : a FIND           ");printf(OK);}
  else {printf("T1 : a FIND           ");printf(FAILED);}

  /* test count word */
  printf("\n-- TEST COUNT WORDS --\n");
  THybrid *tvide=NULL;
  int ct1 = countWordsTHybrid(t1);
  int ctvide = countWordsTHybrid(tvide);

  printf("NB words t1    : %d    ",ct1);
  if (ct1 == 5) printf(OK);
  else printf(FAILED);
  
  printf("NB words tvide : %d    ",ctvide);
  if (ctvide == 0) printf(OK);
  else printf(FAILED);

    /* test count null */
  printf("\n-- TEST COUNT NULL --\n");
  ct1 = countNullTHybrid(t1);
  ctvide = countNullTHybrid(tvide);
  THybrid *ttest = buildTHybrid("test");
  int cttest = countNullTHybrid(ttest);

  printf("NB null t1    : %d    ",ct1);
  if (ct1 == 13) printf(OK);
  else printf(FAILED);

  printf("NB null tvide : %d     ",ctvide);
  if (ctvide == 1) printf(OK);
  else printf(FAILED);

  printf("NB null ttest : %d     ",cttest);
  if (cttest == 3) printf(OK);
  else printf(FAILED);

  /* test height */
  printf("\n-- TEST HEIGHT --\n");
  int height = heightTHybrid(t1);
  int heightVide = heightTHybrid(tvide);

  printf("T1 height     : %d     ",height);
  if (height == 5) printf(OK);
  else printf(FAILED);

  printf("TVIDE height  : %d     ",heightVide);
  if (heightVide == 0) printf(OK);
  else printf(FAILED);

  int level = averageLevelTHybrid(t1);
  printf("T1 Level      : %d     ",level);
  if (level == 1)  printf(OK);
  else  printf(FAILED);

  level = averageLevelTHybrid(tvide);
  printf("TVIDE Level   : %d     ",level);
  if (level == 0)  printf(OK);
  else  printf(FAILED);


  /* test count prefix */
  printf("\n-- TEST COUNT PREFIX --\n");
  int prefix = countPrefixTHybrid("a",t1);
  printf("T1 NB 'a' prefix : %d  ",prefix);
  if (prefix == 2) printf(OK);
  else  printf(FAILED);

  /* test print word */
  printf("\n-- TEST PRINT TRIE --\n");
  wordList *l = listWordsTHybrid(t1);
  printWordsList(l);
  printf("---------------\n");
  printf("T1 PRINT TRIE         ");printf(OK);

  /* test del word */
  printf("\n-- TEST DEL WORD --\n");
  ct1 = countWordsTHybrid(t1);
  #ifdef VERBOSE
  printf("BEFORE [%d]\n",ct1);
  #endif
  t1 = delTHybrid("a",t1);
  #ifdef VERBOSE
  printf("AFTER  [%d]\n",countWordsTHybrid(t1));
  #endif
  printf("T1 DEL word 'a'       ");
  if (4 ==  countWordsTHybrid(t1))
    printf(OK);
  else
    printf(FAILED);

  /* test change */
  printf("\n-- TEST CHANGE --\n");
  BRDtree *brd = emptyBRDtree();
  brd = THybridToBRDtree(t1);
  l = listWordsBRDtree(brd);
  printBRDtree(brd);

  /* test files */
  printf("\n-- TEST ADD FILE --\n");
  THybrid *tfile = NULL; 
  printf("add file\n");
  tfile = addFileToTHybrid("test/dactylo",tfile);
  printf("add dir\n");
  tfile = addDirToTHybrid("test/shakespeare",tfile);
  
  int cfile = countWordsTHybrid(tfile);
  printf("+NB WORDS [%d]     ",cfile);
  if (cfile == 23106) printf(OK);
  else printf(FAILED);

  tfile = delTHybrid("a",tfile);

  printf("del file\n");
  tfile = delFileToTHybrid("test/dactylo",tfile);
  printf("del dir\n");
  tfile = delDirToTHybrid("test/shakespeare",tfile);

  tfile = delTHybrid("a",tfile);

  cfile = countWordsTHybrid(tfile);
  printf("+NB WORDS [%d]         ",cfile);
  if (cfile == 0) printf(OK);
  else printf(FAILED);

  /* test balancing*/
   printf("\n-- TEST BALANCING --\n");
   if (isBalancing(t1) == TRUE) {printf("BALANCING         ");printf(FAILED);}
   else {printf("NOT BALANCING         ");printf(OK);}

  /* test free tree */
  printf("\n-- TEST FREE TREE --\n");
  cpt1=0;int cpt2=0;int cpt3=0;
  freeTHybrid(t1);cpt1++;
  freeTHybrid(tvide);cpt2++;
  freeTHybrid(ttest);cpt3++;

  printf("T1 Free trie          ");
  if (cpt1 == 1) printf(OK);
  else printf(FAILED);

  printf("TVIDE Free trie       ");
  if (cpt2 == 1) printf(OK);
  else printf(FAILED);
  
  printf("TTEST Free trie       ");
  if (cpt3 == 1) printf(OK);
  else printf(FAILED);
  
  return EXIT_SUCCESS;
}
