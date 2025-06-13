

void Book_affiche(struct Book *book){
  for(int i=0; i < 10; i++){
    struct chapitre *chap = &livre->chapitres[i];

        // Nom de fichier : 01.html, 02.html, ...
        sprintf(filename, "%02d.html", chap->idChapter);
        f = fopen(filename, "w");

        if (f == NULL) {
            printf("Erreur : impossible de créer le fichier %s\n", filename);
            continue;
        }

        // Début du fichier HTML
        fprintf(f, "<!DOCTYPE html>\n<html lang=\"fr\">\n<head>\n<meta charset=\"UTF-8\">\n");
        fprintf(f, "<title>%s</title>\n</head>\n<body>\n", chap->titre);
        fprintf(f, "<h1>%s</h1>\n", chap->titre);
        // Fin du fichier
        fprintf(f, "</body>\n</html>");
        fclose(f);

        printf(" Fichier %s généré.\n", filename);
        
      }

      }