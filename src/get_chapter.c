#include "book.h"

int get_chapter(char* line) {
    int id;
    if (strstr(line, "<chapter") != NULL) {
        if (sscanf(line, "<chapter id=\"%d\">", &id) == 1) {
            return id;
        }
    }
}

//test
void PrintChapter(char* line) {
    int idChapter;
    char titre[200];
    if (strstr(line, "<chapter") != NULL) {
        sscanf(line, "<chapter id=\"%d\">%[^<]s</chapter>", &idChapter, titre);
        printf("Chapitre ID: %d, Titre: %s\n", idChapter, titre);
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

char get_paragraph(char* line) {
    char texte[512];
    if (strstr(line, "<p>") != NULL) {
        if (sscanf(line, "<p>%511[^<]", texte) == 1) {
            return texte;
        }
    }
}

void get_choice(char* line) {
    int idchoice;
    char description[300];
    if (strstr(line, "<choice") != NULL) {
        if (sscanf(line, "<choice idref=\"%d\">%299[^<]", &idchoice, description) == 2) {
            printf("Choix vers le chapitre %d : %s\n", idchoice, description);
        }
    }
}