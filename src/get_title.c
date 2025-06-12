#include "book.h"
void PrintChapter(char* line) {
    int idChapter;
    char titre[200];
    if (strstr(line, "<chapter") != NULL) {
        sscanf(line, "<chapter id=\"%d\">%[^<]s</chapter>", &idChapter, titre);
        printf("Chapitre ID: %d, Titre: %s\n", idChapter, titre);
    }
}