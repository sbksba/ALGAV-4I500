#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/times.h>

#include "BRDtree.h"
#include "THybrid.h"
#include "color.h"

#define TICK ((double)sysconf(_SC_CLK_TCK))

void timeAdd (char *path)
{
  struct tms startBRD, endBRD, startHYB, endHYB;
  clock_t start_tBRD, end_tBRD, start_tHYB, end_tHYB;
  double timeBRD,totalBRD, timeHYB, totalHYB;
  BRDtree *tree;
  THybrid *trie = NULL;

  /* ADD WORDS */
  #ifdef VERBOSE
  fprintf(stderr,"+[START] add words\n");
  #endif

  /*BRD*/
  tree = emptyBRDtree();
  start_tBRD = times(&startBRD);
  tree = addDirToBRDtree(path, tree);
  end_tBRD = times(&endBRD);
  #ifdef VERBOSE
  fprintf(stderr,"+[END]   add words\n");
  #endif

  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  /*HYB*/
  start_tHYB = times(&startHYB);
  trie = addDirToTHybrid(path, trie);
  end_tHYB = times(&endHYB);
  #ifdef VERBOSE
  fprintf(stderr,"+[END]   add words\n");
  #endif

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;
  
  fprintf(stderr,"+[%s]\n",path);
  fprintf(stderr,"+[TIME]  BRD user[%f] -- total[%f] (seconds)\n",timeBRD,totalBRD);
  fprintf(stderr,"+[TIME]  HYB user[%f] -- total[%f] (seconds)\n",timeHYB,totalHYB);
  printf("%d %f %f\n",countWordsBRDtree(tree),totalBRD,totalHYB);

  freeBRDtree(tree);
  freeTHybrid(trie);
}

int main()
{
  fprintf(stderr,"\n-- TIME ADD --\n");
  printf("#timeAddBRD.dat\n#NB_WORDS TIME\n");
  timeAdd("test");
  timeAdd("test/tmp1");
  timeAdd("test/tmp2");
  timeAdd("test/tmp3");
  timeAdd("test/shakespeare");

  return EXIT_SUCCESS;
}
