#include "book.h"


// get_chapter : Extrait le numéro du chapitre depuis une balise <chapter>
int get_chapter(char* line) {
    int id = -1;
    sscanf(line, "<chapter id=\"%d\">", &id);
    return id;
}


// get_title : Alloue dynamiquement et retourne le titre extrait d'une balise <chapter>
char* get_title(char* line) {
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

char* get_paragraph(char* line) {
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


// get_choice : Retourne un tableau dynamique contenant les idref d'une ligne <choice>
int* get_choice(char* line, int* nbChoix) {
    int* tab = malloc(sizeof(int) * MAX_CHOIX);
    *nbChoix = 0;

    int idchoice;
    char description[LINE_SIZE];

    if (sscanf(line, "<choice idref=\"%d\">%511[^<]", &idchoice, description) == 2) {
        tab[(*nbChoix)++] = idchoice;
    }

    return tab;
}


// get_choice_text : Retourne un tableau dynamique contenant les textes visibles des choix

char** get_choice_text(char* line, int* nbChoix) {
    char** tab = malloc(sizeof(char*) * MAX_CHOIX);
    *nbChoix = 0;

    int id;
    char buffer[LINE_SIZE];

    if (sscanf(line, "<choice idref=\"%d\">%511[^<]", &id, buffer) == 2) {
        tab[0] = malloc(strlen(buffer) + 1);
        if (tab[0] != NULL) {
            strcpy(tab[0], buffer);
            *nbChoix = 1;
        }
    }

    return tab;
}


// remplir_chapitre : Remplit une structure Chapitre ligne par ligne
void remplir_chapitre(struct Chapitre* chapitre, char* line) {
    // Si c'est un début de chapitre, extraire id et titre
    if (strstr(line, "<chapter") != NULL) {
        chapitre->idChapter = get_chapter(line);
        char* titre = get_title(line);
        if (titre != NULL) {
            strncpy(chapitre->title, titre, MAX_TITRE - 1);
            chapitre->title[MAX_TITRE - 1] = '\0';
            free(titre);
        }
    }
    // Si c'est un paragraphe, concaténer au contenu du chapitre
    else if (strstr(line, "<p>") != NULL) {
        char* para = get_paragraph(line);
        if (para != NULL && strlen(chapitre->content) + strlen(para) < MAX_CONTENT - 1) {
            strcat(chapitre->content, para);
            strcat(chapitre->content, "\n");
            free(para);
        }
    }
    // Si c'est un choix, ajouter id et texte au tableau de choix
    else if (strstr(line, "<choice") != NULL) {
        if (chapitre->nbChoices < MAX_CHOIX) {
            int id = -1;
            char texte[LINE_SIZE];

            if (sscanf(line, "<choice idref=\"%d\">%511[^<]", &id, texte) == 2) {
                chapitre->choices[chapitre->nbChoices] = id;
                strncpy(chapitre->texteChoix[chapitre->nbChoices], texte, LINE_SIZE - 1);
                chapitre->texteChoix[chapitre->nbChoices][LINE_SIZE - 1] = '\0';
                chapitre->nbChoices++;
            }
        }
    }
}
