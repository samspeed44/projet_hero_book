#include "book.h"

void PrintChapter(char* line) {
    int idChapter;
    char titre[200];
    if (strstr(line, "<chapter") != NULL) {
        sscanf(line, "<chapter id=\"%d\">%[^<]s</chapter>", &idChapter, titre);
        printf("Chapitre ID: %d, Titre: %s\n", idChapter, titre);
    }
}

int get_chapter(char* line) {
    int id_chapter;
    char titre[200];
    if (strstr(line, "<chapter id=") != NULL) {
        sscanf(line, "<chapter id=\"%d\">%[^<]s</chapter>", &id_chapter);
        printf("Chapitre ID: %d\n", id_chapter);
    }
}

//test
void get_chapter(char* line) {
    int id;
    if (strstr(line, "<chapter") != NULL) {
        if (sscanf(line, "<chapter id=\"%d\">", &id) == 1) {
            printf("Numéro de chapitre : %d\n", id);
        }
    }
}

void get_title(char* line) {
    int id;
    char titre[200];
    if (strstr(line, "<chapter") != NULL) {
        if (sscanf(line, "<chapter id=\"%d\">%199[^<]</chapter>", &id, titre) == 2) {
            printf("Titre : %s\n", titre);
        }
    }
}

void get_paragraph(char* line) {
    char texte[512];
    if (strstr(line, "<p>") != NULL) {
        if (sscanf(line, "<p>%511[^<]", texte) == 1) {
            printf("Paragraphe : %s\n", texte);
        }
    }
}

void get_choice(char* line) {
    int idref;
    char description[300];
    if (strstr(line, "<choice") != NULL) {
        if (sscanf(line, "<choice idref=\"%d\">%299[^<]", &idref, description) == 2) {
            printf("Choix vers le chapitre %d : %s\n", idref, description);
        }
    }
}