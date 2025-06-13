#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct chapitre{      //structure qui contient les informations d’un seul chapitre
  int idChapter;      // numéro du chapitre
  char titre[200];    // titre du chapitre
  char content[520];  // les paragraphes qui composent le chapitre (contenu de l'histoire)
  char choice1;       // premier choix
  char choice2;       // deuxième choix
};

struct Book{          //contient tous les chapitres (total de 10 chapitres)
  struct chapitre *chapitre;
  };