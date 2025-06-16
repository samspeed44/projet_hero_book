#include "book.h"
#include <stdio.h>
#include <string.h>

void affichage(struct Book *livre) {
    char filename[20];
    FILE *f;

    for (int i = 0; i < 10; i++) {
        struct Chapitre chap = livre->chapters[i];

        // Créer le nom de fichier (ex : "01.html")
        sprintf(filename, "../histoire/%02d.html", chap.idChapter);
        f = fopen(filename, "w");

        if (!f) {
            printf("Erreur ouverture fichier %s\n", filename);
            continue;
        }

        // Début HTML
        fprintf(f, "<!DOCTYPE html>\n<html lang=\"fr\">\n<head>\n<meta charset=\"UTF-8\">\n");
        fprintf(f, "<title>%s</title>\n", chap.title);
        fprintf(f, "<link rel=\"stylesheet\" href=\"style.css\">\n");  
        fprintf(f, "</head>\n<body>\n");
        fprintf(f, "<h1>%s</h1>\n", chap.title);

        // Affichage des paragraphes
        char contenu[MAX_CONTENT];
        strcpy(contenu, chap.content);
        char *ligne = strtok(contenu, "\n");

        while (ligne != NULL) {
            fprintf(f, "<p>%s</p>\n", ligne);
            ligne = strtok(NULL, "\n");
        }

        // Affichage des choix multiples
        for (int j = 0; j < chap.nbChoices; j++) {
            int idCible = chap.choices[j];

            // Extraire le texte sans la balise <a>
            char texteNettoye[256];
            char *pos = strstr(chap.texteChoix[j], "<a>");
            if (pos != NULL) {
                size_t len = pos - chap.texteChoix[j];
                strncpy(texteNettoye, chap.texteChoix[j], len);
                texteNettoye[len] = '\0';
            } else {
                strcpy(texteNettoye, chap.texteChoix[j]);
            }

            // Générer le choix avec lien
            fprintf(f, "<p>%s<a href=\"%02d.html\">Chapitre %d</a></p>\n",
                    texteNettoye, idCible, idCible);
        }

        // Fin du fichier HTML
        fprintf(f, "</body>\n</html>");
        fclose(f);

        printf("%s généré.\n", filename);
    }
}