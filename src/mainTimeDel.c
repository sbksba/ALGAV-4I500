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

void timeDel (char *path)
{
  struct tms startBRD, endBRD, startHYB, endHYB;
  clock_t start_tBRD, end_tBRD, start_tHYB, end_tHYB;
  double timeBRD,totalBRD, timeHYB, totalHYB;
  BRDtree *tree;
  THybrid *trie = NULL;
  int cpt=0;

  /* DEL WORDS */
  #ifdef VERBOSE
  fprintf(stderr,"+[START] del words\n");
  #endif

  /*BRD*/
  tree = emptyBRDtree();
  tree = addDirToBRDtree(path,tree);
  cpt = countWordsBRDtree(tree);
  start_tBRD = times(&startBRD);
  tree = delDirToBRDtree(path, tree);
  end_tBRD = times(&endBRD);
  #ifdef VERBOSE
  fprintf(stderr,"+[END]   del words\n");
  #endif

  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  /*HYB*/
  trie = addDirToTHybrid(path, trie);
  start_tHYB = times(&startHYB);
  trie = delDirToTHybrid(path, trie);
  end_tHYB = times(&endHYB);
  #ifdef VERBOSE
  fprintf(stderr,"+[END]   del words\n");
  #endif

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;
  
  fprintf(stderr,"+[%s]\n",path);
  fprintf(stderr,"+[TIME]  BRD user[%f] -- total[%f] (seconds)\n",timeBRD,totalBRD);
  fprintf(stderr,"+[TIME]  HYB user[%f] -- total[%f] (seconds)\n",timeHYB,totalHYB);
  printf("%d %f %f\n",cpt,totalBRD,totalHYB);

  freeBRDtree(tree);
  freeTHybrid(trie);
}

int main()
{
  fprintf(stderr,"\n-- TIME DEL --\n");
  printf("#timeDel.dat\n#NB_WORDS TIME\n");
  timeDel("test");
  timeDel("test/tmp1");
  /*timeDel("test/tmp2");*/
  /*timeDel("test/tmp3");*/
  timeDel("test/shakespeare");

  return EXIT_SUCCESS;
}
