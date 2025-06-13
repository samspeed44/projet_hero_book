#include "book.h"

int* get_choice(char* line, int* nbChoix) {
    int* tab = malloc(sizeof(int) * 3);
    *nbChoix = 0;

    int idchoice;
    char description[300];

    // On analyse si la ligne contient un choix
    if (strstr(line, "<choice") != NULL) {
        if (sscanf(line, "<choice idref=\"%d\">%199[^<]", &idchoice, description) == 2) {
            tab[(*nbChoix)++] = idchoice;
        }
    }

    return tab;
}

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
