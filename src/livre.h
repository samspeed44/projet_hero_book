#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE     512
#define MAX_TITRE     200
#define MAX_CONTENT   1024
#define MAX_CHAPITRES 10
#define MAX_CHOIX     3

// Structure d’un chapitre
struct Chapitre {
    int idChapitre;                          // Numéro du chapitre
    char titre[MAX_TITRE];                  // Titre du chapitre
    char contenu[MAX_CONTENT];              // Contenu (paragraphes) du chapitre
    int choix[MAX_CHOIX];                 // Numéros des chapitres suivants (jusqu'à 3)
    char texteChoix[MAX_CHOIX][200];        // Descriptions des choix
    int nbChoix;                          // Nombre de choix réellement présents (2 ou 3)
};

// Livre contenant tous les chapitres
struct Livre {
    struct Chapitre chapitres[MAX_CHAPITRES];
};

// === Prototypes des Fonctions ===

void affichage(struct Livre *livre);

// Fonctions d'initialisation de structure
struct Chapitre chapter_init();
struct Livre livre_init();

// Fonctions d'extraction ligne par ligne
int obtenir_chapitre(char* line);
char* obtenir_titre(char* line);
char* obtenir_paragraph(char* line);
void remplir_chapitre(struct Chapitre* chapitre, char* line); // remplit la structure chapitre

// Anciennes fonctions
//int* obtenir_choix(char* line, int* nbChoix);
//char** obtenir_choix_texte(char* line, int* nbChoix);


#endif
