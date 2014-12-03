#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "BRDtree.h"
#include "tool.h"
#include "color.h"

int main(int argc, char **argv)
{
  BRDtree *tfile = emptyBRDtree();

  if (argc == 1)
    tfile = addFileToBRDtree("test/dactylo",tfile);
  else
    {
      if (strcmp(argv[1],"D")==0)
	{
	  if (argv[2]!=NULL)
	    tfile = addDirToBRDtree(argv[2],tfile);
	}
      else if (strcmp(argv[1],"F")==0)
	{
	  if (argv[2]!=NULL)
	    tfile = addFileToBRDtree(argv[2],tfile);
	}
      else
	{
	  printf("You need to specify the option !!!\n");
	  return EXIT_FAILURE;
	}
    }

  /* test GNUPLOT */
  plotBRDtree(tfile);
  freeBRDtree(tfile);

  return EXIT_SUCCESS;
}
