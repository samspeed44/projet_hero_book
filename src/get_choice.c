#include "book.h"

int* get_choice(char* line, int* nbChoix) {
    int* tab = malloc(sizeof(int) * 3);
    *nbChoix = 0;

    int idchoice;
    char description[300];

    // On analyse si la ligne contient un choix
    if (strstr(line, "<choice") != NULL) {
        if (sscanf(line, "<choice idref=\"%d\">%199[^<]", &idchoice, description) == 2) {
            tab[(*nbChoix)++] = idchoice;
        }
    }

    return tab;
}
