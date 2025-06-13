#include "book.h"

int get_chapter(char* line) {
    int id;
    if (strstr(line, "<chapter") != NULL) {
        if (sscanf(line, "<chapter id=\"%d\">", &id) == 1) {
            return id;
        }
    }
}