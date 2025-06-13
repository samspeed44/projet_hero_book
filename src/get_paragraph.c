#include "book.h"
char get_paragraph(char* line) {
    char paragraph[520];
    if (strstr(line, "<p") != NULL) {
        sscanf(line, "<chapter id=\"%d\">%[^<]s</chapter>", paragraph);
        printf("Chapitre ID: %d, Titre: %s\n", paragraph);
        return paragraph;
    }
}