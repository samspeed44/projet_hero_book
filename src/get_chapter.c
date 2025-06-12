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