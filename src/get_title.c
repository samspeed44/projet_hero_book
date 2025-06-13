#include "book.h"

void get_title(char* line) {
    int id;
    char titre[200];
    if (strstr(line, "<chapter") != NULL) {
        if (sscanf(line, "<chapter id=\"%d\">%199[^<]</chapter>", &id, titre) == 2) {
            printf("Titre : %s\n", titre);
        }
    }
}