#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/times.h>

#include "BRDtree.h"
#include "color.h"

#define TICK ((double)sysconf(_SC_CLK_TCK))

void timeDel (char *path)
{
  struct tms start, end;
  clock_t start_t, end_t;
  double time,total;
  BRDtree *tree;
  int cpt=0;

  /* DEL WORDS */
  fprintf(stderr,"+[START] del words\n");
  tree = emptyBRDtree();
  tree = addDirToBRDtree(path, tree);
  cpt = countWordsBRDtree(tree);
  start_t = times(&start);
  tree = delDirToBRDtree(path, tree);
  end_t = times(&end);
  fprintf(stderr,"+[END]   del words\n");

  time = (double)(end.tms_utime - start.tms_utime)/TICK;
  total = (end_t - start_t)/TICK;
  
  fprintf(stderr,"+[%s]\n",path);
  fprintf(stderr,"+[TIME]  user[%f] -- total[%f] (seconds)\n",time,total);
  printf("%d %f\n",cpt,total);
  freeBRDtree(tree);
}

int main()
{
  printf("#timeDelBRD.dat\n#NB_WORDS TIME\n");
  timeDel("test");
  timeDel("test/tmp1");
  /*timeDel("test/tmp2");*/
  /*timeDel("test/tmp3");*/
  timeDel("test/shakespeare");

  return EXIT_SUCCESS;
}
