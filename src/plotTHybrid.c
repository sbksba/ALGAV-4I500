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
  THybrid *t1 = NULL;
  t1 = addFileToTHybrid("test/dactylo",t1);

  /* test GNUPLOT */
  plotTHybrid(t1);
  freeTHybrid(t1);

  return EXIT_SUCCESS;
}
