#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "BRDtree.h"
#include "THybrid.h"
#include "color.h"

void listInput()
{
  printf("-- List of Input --\n");
  printf("-----------------------------------------\n");
  printf("\t1) create a new tree with a file\n");
  printf("\t2) create a new trie with a file\n");
  printf("\t3) create a new tree with a directory\n");
  printf("\t4) create a new trie with a directory\n");
  printf("\t5) add a word to the tree\n");
  printf("\t6) add a word to the trie\n");
  printf("\t7) del a word to the tree\n");
  printf("\t8) del a word to the trie\n");
  printf("\t9) search a word in the tree\n");
  printf("\t10) search a word in the trie\n");
  printf("\t11) count words of the tree\n");
  printf("\t12) count words of the trie\n");
  printf("\t13) height of the tree\n");
  printf("\t14) height of the trie\n");
  printf("\t15) count the number of prefix (tree)\n");
  printf("\t16) count the number of prefix (trie)\n");
  printf("\t17) EXIT\n");
  printf("-----------------------------------------\n");
}

int main()
{
  int input;
  char filename[100], directory[100], word[100];
  BRDtree *tree = emptyBRDtree();
  THybrid *trie = NULL;
  printf("-- WELCOME --\n");
  
  while(1)
    {
      
      listInput();
      printf("Give your input\n");
      scanf("%d",&input);
      
      switch(input)
	{
	case 1:
	  printf("$> filename : ");
	  scanf("%s",filename);
	  printf("[%s]\n",filename);
	  tree = addFileToBRDtree(filename,tree);
	  break;
	case 2:
	  printf("$> filename : ");
	  scanf("%s",filename);
	  trie = addFileToTHybrid(filename,trie);
	  break;
	case 3:
	  printf("$> directory : ");
	  scanf("%s",directory);
	  tree = addDirToBRDtree(directory,tree);
	  break;
	case 4:
	  printf("$> directory : ");
	  scanf("%s",directory);
	  trie = addDirToTHybrid(directory,trie);
	  break;
	case 5:
	  printf("$> word : ");
	  scanf("%s",word);
	  tree = addBRDtree(word,tree);
	  break;
	case 6:
	  printf("$> word : ");
	  scanf("%s",word);
	  trie = addTHybrid(word,trie);
	  break;
	case 7:
	  printf("$> word : ");
	  scanf("%s",word);
	  tree = delBRDtree(word,tree);
	  break;
	case 8:
	  printf("$> word : ");
	  scanf("%s",word);
	  trie = delTHybrid(word,trie);
	  break;
	case 9:
	  printf("$> word : ");
	  scanf("%s",word);
	  if (searchBRDtree(word,tree) == 0)
	    printf("++ We find your word ++\n\n");
	  else
	    printf("++ Sorry we doesn't your word ++\n\n");
	  break;
	case 10:
	  printf("$> word : ");
	  scanf("%s",word);
	  if (searchTHybrid(word,trie) == TRUE)
	    printf("++ We find your word ++\n\n");
	  else
	    printf("++ Sorry we doesn't your word ++\n\n");
	  break;
	case 17:
	  return EXIT_SUCCESS;
	}
    }

  return EXIT_SUCCESS;
}
