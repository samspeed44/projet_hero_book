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
    int idChapter;                          // Numéro du chapitre
    char title[MAX_TITRE];                  // Titre du chapitre
    char content[MAX_CONTENT];              // Contenu (paragraphes) du chapitre
    int choices[MAX_CHOIX];                 // Numéros des chapitres suivants (jusqu'à 3)
    char texteChoix[MAX_CHOIX][200];        // Descriptions des choix
    int nbChoices;                          // Nombre de choix réellement présents (2 ou 3)
};

// Livre contenant tous les chapitres
struct Book {
    struct Chapitre chapters[MAX_CHAPITRES];
};

// === Prototypes des Fonctions ===
struct Book book_init(); // Initialise le livre

// Fonctions d'extraction ligne par ligne
char* get_title(char* line);
int get_chapter(char* line);
char* get_paragraph(char* line);
int* get_choice(char* line, int* nbChoix);
char** get_choice_text(char* line, int* nbChoix);
void remplir_chapitre(struct Chapitre* chapitre, char* line); // remplit la structure chapitre

// Fonctions d'initialisation de structure
struct Chapitre chapter_init();
struct Book book_init();

#endif
