#include "book.h"

//  get_chapter - Extrait le numéro du chapitre depuis une balise <chapter>
int get_chapter(char* line) {
    int id = -1;
    sscanf(line, "<chapter id=\"%d\">", &id);
    return id;
}

//  get_title - Extrait le titre du chapitre depuis une balise <chapter>
//  Utilise un buffer static (stockage temporaire non libérable mais réutilisable)
char* get_title(char* line) {
    static char titre[200];
    int id;
    titre[0] = '\0';
    sscanf(line, "<chapter id=\"%d\">%199[^<]</chapter>", &id, titre);
    return titre;
}

//  get_paragraph - Extrait le contenu textuel d'un paragraphe <p>...</p>
//  Utilise un buffer static pour retourner une chaîne
char* get_paragraph(char* line) {
    static char texte[512];
    texte[0] = '\0';
    sscanf(line, "<p>%511[^<]", texte);
    return texte;
}

//  get_choice - Récupère le numéro du chapitre vers lequel un choix pointe
//  Renvoie un tableau dynamique de taille 1 avec un entier
int* get_choice(char* line, int* nbChoix) {
    int* tab = malloc(sizeof(int) * 3);
    *nbChoix = 0;

    int idchoice;
    char description[300];
    if (sscanf(line, "<choice idref=\"%d\">%299[^<]", &idchoice, description) == 2) {
        tab[(*nbChoix)++] = idchoice;
    }

    return tab;
}

//  get_choice_text - Extrait le texte visible d’un choix <choice>
//  Renvoie un tableau dynamique de chaînes (1 élément)
char** get_choice_text(char* line, int* nbChoix) {
    char** tab = malloc(sizeof(char*) * 3);
    *nbChoix = 0;

    int id;
    char description[300];
    if (sscanf(line, "<choice idref=\"%d\">%299[^<]", &id, description) == 2) {
        tab[0] = malloc(strlen(description) + 1);
        strcpy(tab[0], description);
        *nbChoix = 1;
    }

    return tab;
}

//  remplir_chapitre - Remplit une structure Chapitre ligne par ligne
//  Détecte automatiquement le type de contenu à analyser
void remplir_chapitre(struct Chapitre* chapitre, char* line) {
    // Chapitre (titre + id)
    if (strstr(line, "<chapter") != NULL) {
        chapitre->idChapter = get_chapter(line);
        char* titre = get_title(line);
        if (titre != NULL) {
            strncpy(chapitre->title, titre, MAX_TITRE - 1);
            chapitre->title[MAX_TITRE - 1] = '\0';
        }
    }
    // Paragraphe (contenu)
    else if (strstr(line, "<p>") != NULL) {
        char* para = get_paragraph(line);
        if (para != NULL && strlen(chapitre->content) + strlen(para) < MAX_CONTENT - 1) {
            strcat(chapitre->content, para);
            strcat(chapitre->content, "\n");
        }
    }
    // Choix (id + texte)
    else if (strstr(line, "<choice") != NULL) {
        int nb1 = 0, nb2 = 0;
        int* ids = get_choice(line, &nb1);
        char** textes = get_choice_text(line, &nb2);

        if (nb1 > 0 && nb2 > 0 && chapitre->nbChoices < MAX_CHOIX) {
            chapitre->choices[chapitre->nbChoices] = ids[0];
            strncpy(chapitre->texteChoix[chapitre->nbChoices], textes[0], 199);
            chapitre->texteChoix[chapitre->nbChoices][199] = '\0';
            chapitre->nbChoices++;
        }

        // Libération mémoire
        free(ids);
        free(textes[0]);
        free(textes);
    }
}
