#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITRE     200
#define MAX_CONTENT   1024
#define MAX_CHAPITRES 10
#define MAX_CHOIX     3  // Adapté pour accueillir jusqu'à 3 choix par chapitre

// Structure d’un chapitre
struct chapitre {
    int idChapter;                         // Numéro du chapitre
    char title[MAX_TITRE];                // Titre du chapitre
    char content[MAX_CONTENT];            // Contenu (paragraphes) du chapitre
    int choices[MAX_CHOIX];                 // Numéros des chapitres suivants (jusqu'à 3)
    char texteChoix[MAX_CHOIX][200];      // Descriptions des choix
    int nbChoices;                          // Nombre de choix réellement présents (2 ou 3)
};

// Livre contenant tous les chapitres
struct Book {
    struct chapitre chapters[MAX_CHAPITRES];
};

// === Prototypes des Fonctions ===
struct Book book_init(); // Initialise le livre

// Fonctions d'extraction ligne par ligne
void get_title(char* line);
void get_chapter(char* line);
void get_paragraph(char* line);
void get_choice(char* line);

void PrintChapter(char* line);  // Fonction de test

#endif // BOOK_H
