#include "book.h"


/*

Les fonction ci-dessous prennent en argument un seule ligne et analyse cette dernière pour retourner
certaines informations

L'objectif est d'ensuite pouvoir remplir une structure Chaptitre avec les informations requises pour
en compléter une pour chaque Chapitre.

*/




// Renvoie le numéro du chapitre
int get_chapter(char* line) {
    int id;
    if (strstr(line, "<chapter") != NULL) {
        if (sscanf(line, "<chapter id=\"%d\">", &id) == 1) {
            return id;
        }
    }
}

// Renvoie le titre du chapitre
void get_title(char* line) {
    int id;
    char titre[200];
    if (strstr(line, "<chapter") != NULL) {
        if (sscanf(line, "<chapter id=\"%d\">%199[^<]</chapter>", &id, titre) == 2) {
            printf("Titre : %s\n", titre);
        }
    }
}

// Renvoie le contenu textuel du chapitre
char get_paragraph(char* line) {
    char texte[512];
    if (strstr(line, "<p>") != NULL) {
        if (sscanf(line, "<p>%511[^<]", texte) == 1) {
            return texte;
        }
    }
}

// Renvoie le numéro du chapitre du choix
int* get_choice(char* line, int* nbChoix) {
    int* tab = malloc(sizeof(int) * 3);
    *nbChoix = 0;

    int idchoice;
    char description[300];

    if (strstr(line, "<choice") != NULL) {
        if (sscanf(line, "<choice idref=\"%d\">%199[^<]", &idchoice, description) == 2) {
            tab[(*nbChoix)++] = idchoice;
        }
    }

    return tab;
}

// Renvoie le contenue textuel du choix
char** get_choice_text(char* line, int* nbChoix) {
    char** tab = malloc(sizeof(char*) * 3);  
    *nbChoix = 0;

    int id;
    char description[300]; // le texte du choix

    if (strstr(line, "<choice") != NULL) {
        if (sscanf(line, "<choice idref=\"%d\">%299[^<]", &id, description) == 2) {
            // Alloue dynamiquement une chaîne pour stocker le texte du choix
            tab[*nbChoix] = malloc(strlen(description) + 1);
            strcpy(tab[*nbChoix], description); // Copie le texte extrait dans le tableau
            (*nbChoix)++;
        }
    }

    return tab;
