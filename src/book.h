#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct chapitre{ 
  int idChapter;
  char titre[200];
  char content[520];
  char choice1;
  char choice2;
};

struct Book{
  struct chapitre *chapitre;
  };