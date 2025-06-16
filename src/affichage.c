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

        // Découpe du contenu par paragraphe (\n)
        char contenu[MAX_CONTENT];
        strcpy(contenu, chap.content);
        char *ligne = strtok(contenu, "\n");

        while (ligne != NULL) {
            fprintf(f, "<p>%s</p>\n", ligne);
            ligne = strtok(NULL, "\n");
        }

        // Ajout des choix
        for (int j = 0; j < chap.nbChoices; j++) {
            // Extraire l'index du chapitre cible
            int idCible = chap.choices[j];

            // Nettoyer le texte du choix pour supprimer la balise <a> incluse
            char texteNettoye[256];
            char *pos = strstr(chap.texteChoix[j], "<a>");
            if (pos != NULL) {
                // Copier jusqu'à la balise <a>
                size_t len = pos - chap.texteChoix[j];
                strncpy(texteNettoye, chap.texteChoix[j], len);
                texteNettoye[len] = '\0';
            } else {
                // Aucun lien trouvé, on prend tout
                strcpy(texteNettoye, chap.texteChoix[j]);
            }

            // Écrire le choix avec lien propre
            fprintf(f, "<p>%s<a href=\"%02d.html\">Chapitre %d</a></p>\n",
                    texteNettoye, idCible, idCible);
        }

        fprintf(f, "</body>\n</html>");
        fclose(f);

        printf("%s généré.\n", filename);
    }
}