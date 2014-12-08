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

int main()
{
  struct tms startBRD, endBRD, startHYB, endHYB;
  clock_t start_tBRD, end_tBRD, start_tHYB, end_tHYB;
  double timeBRD,totalBRD, timeHYB, totalHYB;

  BRDtree *tree = emptyBRDtree();
  THybrid *trie = NULL;

  /* ADD WORDS */
  tree = addDirToBRDtree("test/shakespeare",tree);
  trie = addDirToTHybrid("test/shakespeare",trie);

  /* SEARCH */
  start_tBRD = times(&startBRD);
  if (searchBRDtree("what",tree) == 0)
    fprintf(stderr,"BRD FIND WORD\n");
  else
    fprintf(stderr,"BRD NOT FIND WORD\n");
  end_tBRD = times(&endBRD);

  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  start_tHYB = times(&startHYB);
  if (searchTHybrid("what",trie) == 0)
    fprintf(stderr,"HYB FIND WORD\n");
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  printf("[SEARCH] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);

  freeBRDtree(tree);
  freeTHybrid(trie);

  return EXIT_SUCCESS;
}
