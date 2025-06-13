#include "book.h"

char get_paragraph(char* line) {
    char texte[512];
    if (strstr(line, "<p>") != NULL) {
        if (sscanf(line, "<p>%511[^<]", texte) == 1) {
            return texte;
        }
    }
}

