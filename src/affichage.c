#include "book.h"
#include <stdio.h>
#include <string.h>

void affichage(Book livre) {
    char filename[20];
    FILE *f;

    for (int i = 0; i < 10; i++) {
        Chapitre chap = livre.chapitres[i];

        // Créer le nom de fichier (ex : "01.html")
        sprintf(filename, "%02d.html", chap.idChapter);
        f = fopen(filename, "w");

        if (!f) {
            printf("❌ Erreur ouverture fichier %s\n", filename);
            continue;
        }

        // Début HTML
        fprintf(f, "<!DOCTYPE html>\n<html lang=\"fr\">\n<head>\n<meta charset=\"UTF-8\">\n");
        fprintf(f, "<title>%s</title>\n</head>\n<body>\n", chap.titre);
        fprintf(f, "<h1>%s</h1>\n", chap.titre);

        // Découpe du contenu par paragraphe (\n)
        char contenu[MAX_CONTENT];
        strcpy(contenu, chap.content);
        char *ligne = strtok(contenu, "\n");

        while (ligne != NULL) {
            fprintf(f, "<p>%s</p>\n", ligne);
            ligne = strtok(NULL, "\n");
        }

        // Ajout des choix avec liens
        for (int j = 0; j < chap.nbChoix; j++) {
            fprintf(f, "<p>%s <a href=\"%02d.html\">Chapitre %d</a></p>\n",
                chap.texteChoix[j], chap.choix[j], chap.choix[j]);
        }

        fprintf(f, "</body>\n</html>");
        fclose(f);

        printf("✅ %s généré.\n", filename);
    }
}