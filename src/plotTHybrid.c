#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "THybrid.h"
#include "tool.h"
#include "color.h"

int main(int argc, char **argv)
{
  THybrid *tfile = NULL;
  
  if (argc == 1)
    tfile = addFileToTHybrid("test/dactylo.txt",tfile);
  else
    {
      if (strcmp(argv[1],"D")==0)
	{
	  if (argv[2]!=NULL)
	    tfile = addDirToTHybrid(argv[2],tfile);
	}
      else if (strcmp(argv[1],"F")==0)
	{
	  if (argv[2]!=NULL)
	    tfile = addFileToTHybrid(argv[2],tfile);
	}
      else
	{
	  printf("You need to specify the option !!!\n");
	  return EXIT_FAILURE;
	}
    }

  /* test GNUPLOT */
  plotTHybrid(tfile);
  freeTHybrid(tfile);

  return EXIT_SUCCESS;
}
