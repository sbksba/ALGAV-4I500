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
  int cptBRD,cptHYB;

  BRDtree *tree = emptyBRDtree();
  THybrid *trie = NULL;

  printf("#compare.dat\n#FUNC BRD HYB\n");
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
  if (searchTHybrid("what",trie) == TRUE)
    fprintf(stderr,"HYB FIND WORD\n");
  else
    fprintf(stderr,"HYB NOT FIND WORD\n");
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  fprintf(stderr,"[SEARCH] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);
  printf("search %f %f\n",totalBRD,totalHYB);

  /* COUNT WORDS */
  cptBRD=0;
  cptHYB=0;
  start_tBRD = times(&startBRD);
  cptBRD = countWordsBRDtree(tree);
  end_tBRD = times(&endBRD);
  
  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  start_tHYB = times(&startHYB);
  cptHYB = countWordsTHybrid(trie);
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  fprintf(stderr,"[COUNTW] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);
  printf("countw %f %f\n",totalBRD,totalHYB);

  /* LIST WORDS */
  start_tBRD = times(&startBRD);
  wordList *lB = listWordsBRDtree(tree);
  end_tBRD = times(&endBRD);
  
  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  start_tHYB = times(&startHYB);
  wordList *lH = listWordsTHybrid(trie);
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  fprintf(stderr,"[LISTWO] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);
  printf("listwo %f %f\n",totalBRD,totalHYB);

  /* COUNT NIL */
  cptBRD=0;
  cptHYB=0;
  start_tBRD = times(&startBRD);
  cptBRD = countNullBRDtree(tree);
  end_tBRD = times(&endBRD);
  
  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  start_tHYB = times(&startHYB);
  cptHYB = countNullTHybrid(trie);
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  fprintf(stderr,"[COUNTN] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);
  printf("countn %f %f\n",totalBRD,totalHYB);

  /* HEIGHT */
  cptBRD=0;
  cptHYB=0;
  start_tBRD = times(&startBRD);
  cptBRD = heightBRDtree(tree);
  end_tBRD = times(&endBRD);
  
  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  start_tHYB = times(&startHYB);
  cptHYB = heightTHybrid(trie);
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  fprintf(stderr,"[HEIGHT] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);
  printf("height %f %f\n",totalBRD,totalHYB);

  /* DEPHT */
  cptBRD=0;
  cptHYB=0;
  start_tBRD = times(&startBRD);
  cptBRD = averageLevelBRDtree(tree);
  end_tBRD = times(&endBRD);
  
  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  start_tHYB = times(&startHYB);
  cptHYB = averageLevelTHybrid(trie);
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  fprintf(stderr,"[DEPHTT] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);
  printf("dephtt %f %f\n",totalBRD,totalHYB);

  /* PREFIX */
  cptBRD=0;
  cptHYB=0;
  start_tBRD = times(&startBRD);
  cptBRD = countPrefixBRDtree("a",tree);
  end_tBRD = times(&endBRD);
  
  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  start_tHYB = times(&startHYB);
  cptHYB = countPrefixTHybrid("a",trie);
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  fprintf(stderr,"[PREFIX] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);
  printf("prefix %f %f\n",totalBRD,totalHYB);

  /* DELETE */
  start_tBRD = times(&startBRD);
  tree = delBRDtree("what",tree);
  end_tBRD = times(&endBRD);
  
  timeBRD = (double)(endBRD.tms_utime - startBRD.tms_utime)/TICK;
  totalBRD = (end_tBRD - start_tBRD)/TICK;

  start_tHYB = times(&startHYB);
  trie = delTHybrid("what",trie);
  end_tHYB = times(&endHYB);

  timeHYB = (double)(endHYB.tms_utime - startHYB.tms_utime)/TICK;
  totalHYB = (end_tHYB - start_tHYB)/TICK;

  fprintf(stderr,"[DELETE] : BRD[%f - %f] -- HYB[%f- %f]\n",timeBRD,totalBRD,timeHYB,totalHYB);
  printf("delete %f %f\n",totalBRD,totalHYB);

  
  /* 
     HASTA LA VISTA BABY !!! 
                       ______
                     <((((((\\\
                     /      . }\
                     ;--..--._|}
  (\                 '--/\--'  )
   \\                | '-'  :'|
    \\               . -==- .-|
     \\               \.__.'   \--._
     [\\          __.--|       //  _/'--.
     \ \\       .'-._ ('-----'/ __/      \
      \ \\     /   __>|      | '--.       |
       \ \\   |   \   |     /    /       /
        \ '\ /     \  |     |  _/       /
         \  \       \ |     | /        /
          \  \      \        /
   */
  FILE *skynet = fopen("/dev/null","w");
  fprintf(skynet,"%d %d %s %s",cptBRD,cptHYB,(char*)lB,(char*)lH);
  
  freeBRDtree(tree);
  freeTHybrid(trie);

  return EXIT_SUCCESS;
}
