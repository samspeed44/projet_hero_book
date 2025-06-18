#include "livre.h"


// get_chapter : Extrait le numéro du chapitre depuis une balise <chapter>
int obtenir_chapitre(char* line) {
    int id = -1;
    sscanf(line, "<chapter id=\"%d\">", &id);
    return id;
}


// get_title : Alloue dynamiquement et retourne le titre extrait d'une balise <chapter>
char* obtenir_titre(char* line) {
    int id;
    char buffer[MAX_TITRE];
    if (sscanf(line, "<chapter id=\"%d\">%199[^<]</chapter>", &id, buffer) == 2) {
        char* titre = malloc(strlen(buffer) + 1);
        if (titre != NULL) {
            strcpy(titre, buffer);
            return titre;
        }
    }
    return NULL;
}


// get_paragraph : Alloue dynamiquement le contenu d'un paragraphe <p>...</p>
char* obtenir_paragraph(char* line) {
    char buffer[LINE_SIZE];
    if (sscanf(line, "<p>%511[^<]", buffer) == 1) {
        char* para = malloc(strlen(buffer) + 1);
        if (para != NULL) {
            strcpy(para, buffer);
            return para;
        }
    }
    return NULL;
}


// remplir_chapitre : Remplit une structure Chapitre ligne par ligne
void remplir_chapitre(struct Chapitre* chapitre, char* line) {
    if (strstr(line, "<chapter") != NULL) {
        chapitre->idChapitre = obtenir_chapitre(line);
        char* titre = obtenir_titre(line);
        if (titre != NULL) {
            strncpy(chapitre->titre, titre, MAX_TITRE - 1);
            chapitre->titre[MAX_TITRE - 1] = '\0';
            free(titre);
        }
    }
    else if (strstr(line, "<p>") != NULL) {
        char* para = obtenir_paragraph(line);
        if (para != NULL && strlen(chapitre->contenu) + strlen(para) < MAX_CONTENT - 1) {
            strcat(chapitre->contenu, para);
            strcat(chapitre->contenu, "\n");
            free(para);
        }
    }
    else if (strstr(line, "<choice") != NULL && chapitre->nbChoix < MAX_CHOIX) {
        int id = -1;
        char texte[LINE_SIZE];

        // On extrait le idref et le texte jusqu'à <a>
        if (sscanf(line, "<choice idref=\"%d\">%511[^<]", &id, texte) == 2) {
            chapitre->choix[chapitre->nbChoix] = id;
            strncpy(chapitre->texteChoix[chapitre->nbChoix], texte, 199);
            chapitre->texteChoix[chapitre->nbChoix][199] = '\0';
            chapitre->nbChoix++;
        }
    }
}