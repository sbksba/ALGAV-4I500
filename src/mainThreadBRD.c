#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/times.h>

#include "BRDtree.h"
#include "color.h"

#define TICK ((double)sysconf(_SC_CLK_TCK))

BRDtree *tree;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Tfunc (void *file)
{
  BRDtree *tmp = emptyBRDtree();
  tmp = addFileToBRDtree((char *)file, tmp);
  pthread_mutex_lock(&mutex);
  tree = mergeBRDtree(tree,tmp);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main()
{
  struct tms start, end;
  clock_t start_t, end_t;
  double time, total;
  char *dir = "test/shakespeare", *path;
  DIR *d = opendir(dir);
  struct dirent *in;
  pthread_t tid[256];
  int cpt=0,i;

  if (dir == NULL)
    {
      perror("opendir");
      return EXIT_FAILURE;
    }

  start_t = times(&start);
  while ( (in=readdir(d)) )
    {
      if (!strcmp(in->d_name, ".")) continue;
      if (!strcmp(in->d_name, "..")) continue;
      path = (char *)malloc(sizeof(char)*256);
      strcpy(path, dir);
      strcat(path, "/");
      strcat(path, in->d_name);

      if (pthread_create(&tid[cpt++], NULL, Tfunc, path) == -1)
	{
	  perror("pthread_create");return EXIT_FAILURE;
	}
    }

  end_t = times(&end);
  time = (double)(end.tms_utime - start.tms_utime)/TICK;
  total = (end_t - start_t)/TICK;
  
  closedir(d);
  for (i=0; i<cpt; i++)
    if (pthread_join(tid[i], NULL) != 0) {perror("pthread_join");return EXIT_FAILURE;}
  
  fprintf(stderr,"+[TIME]  user[%f] -- total[%f] (seconds)\n",time,total);
  freeBRDtree(tree);

  return EXIT_SUCCESS;
}
