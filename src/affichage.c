#include "book.h"
#include <stdio.h>
#include <string.h>

void affichage(struct Book *livre) {
    char filename[30];
    FILE *f;

    for (int i = 0; i < 10; i++) {
        struct Chapitre chap = livre->chapters[i];

        // Créer le nom du fichier HTML : "01.html", "02.html", ...
        sprintf(filename, "../histoire/%02d.html", chap.idChapter);
        f = fopen(filename, "w");

        if (!f) {
            printf("Erreur ouverture fichier %s\n", filename);
            continue;
        }

        // En-tête HTML
        fprintf(f, "<!DOCTYPE html>\n<html lang=\"fr\">\n<head>\n<meta charset=\"UTF-8\">\n");
        fprintf(f, "<title>%s</title>\n", chap.title);
        fprintf(f, "<link rel=\"stylesheet\" href=\"style.css\">\n");
        fprintf(f, "</head>\n<body>\n");
        fprintf(f, "<h1>%s</h1>\n", chap.title);

        // Paragraphes
        char contenu[MAX_CONTENT];
        strcpy(contenu, chap.content);
        char *ligne = strtok(contenu, "\n");
        while (ligne != NULL) {
            fprintf(f, "<p>%s</p>\n", ligne);
            ligne = strtok(NULL, "\n");
        }

        // Choix (plusieurs liens)
        for (int j = 0; j < chap.nbChoices; j++) {
            int cible = chap.choices[j];

            // Nettoyer texteChoix (enlever <a> si présent)
            char texte[256];
            char *pos = strstr(chap.texteChoix[j], "<a>");
            if (pos != NULL) {
                size_t len = pos - chap.texteChoix[j];
                strncpy(texte, chap.texteChoix[j], len);
                texte[len] = '\0';
            } else {
                strcpy(texte, chap.texteChoix[j]);
            }

            // Affichage du choix complet
            fprintf(f, "<p>%s<a href=\"%02d.html\">Chapitre %d</a></p>\n", texte, cible, cible);
        }

        // Fin HTML
        fprintf(f, "</body>\n</html>\n");
        fclose(f);
        printf("%s généré.\n", filename);
    }
}