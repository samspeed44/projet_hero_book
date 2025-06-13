// main.c
#include "book.h"




int main() {
    struct Book monLivre;
    char line[LINE_SIZE];
    int chapitreIndex = -1;

    FILE* file = fopen("book.txt", "r");
    if (!file) {
        perror("Erreur lors de l'ouverture de book.txt");
        return EXIT_FAILURE;
    }

    // Initialise tous les chapitres à zéro (contenu vide, id -1, nbChoices 0)
    for (int i = 0; i < MAX_CHAPITRES; i++) {
        monLivre.chapters[i].idChapter = -1;
        monLivre.chapters[i].nbChoices = 0;
        monLivre.chapters[i].title[0] = '\0';
        monLivre.chapters[i].content[0] = '\0';
        for (int j = 0; j < MAX_CHOIX; j++) {
            monLivre.chapters[i].choices[j] = -1;
            monLivre.chapters[i].texteChoix[j][0] = '\0';
        }
    }

    // Lecture ligne par ligne du fichier
    while (fgets(line, LINE_SIZE, file)) {
        // Lorsqu'on rencontre une balise <chapter>, on passe à un nouveau chapitre
        if (strstr(line, "<chapter") != NULL) {
            chapitreIndex++;
            if (chapitreIndex < MAX_CHAPITRES) {
                monLivre.chapters[chapitreIndex].idChapter = -1;
                monLivre.chapters[chapitreIndex].nbChoices = 0;
                monLivre.chapters[chapitreIndex].title[0] = '\0';
                monLivre.chapters[chapitreIndex].content[0] = '\0';
                for (int j = 0; j < MAX_CHOIX; j++) {
                    monLivre.chapters[chapitreIndex].choices[j] = -1;
                    monLivre.chapters[chapitreIndex].texteChoix[j][0] = '\0';
                }
            }
        }

        // Appelle la fonction qui remplit les données du chapitre ligne par ligne
        if (chapitreIndex >= 0 && chapitreIndex < MAX_CHAPITRES) {
            remplir_chapitre(&monLivre.chapters[chapitreIndex], line);
        }
    }

    fclose(file);

    // Affichage de vérification
    for (int i = 0; i <= chapitreIndex; i++) {
        struct Chapitre* ch = &monLivre.chapters[i];
        printf("\nChapitre %d : %s\n", ch->idChapter, ch->title);
        printf("Contenu :\n%s\n", ch->content);
        for (int j = 0; j < ch->nbChoices; j++) {
            printf("Choix %d -> Chapitre %d : %s\n", j+1, ch->choices[j], ch->texteChoix[j]);
        }
    }

    return 0;
}
