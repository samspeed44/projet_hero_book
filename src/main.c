#include "book.h"

// Fonction pour initialiser un chapitre
struct Chapitre chapter_init() {
    struct Chapitre chap;
    chap.idChapter = -1;
    chap.nbChoices = 0;
    chap.title[0] = '\0';
    chap.content[0] = '\0';
    for (int i = 0; i < MAX_CHOIX; i++) {
        chap.choices[i] = -1;
        chap.texteChoix[i][0] = '\0';
    }
    return chap;
}

// Fonction pour initialiser un livre
struct Book book_init() {
    struct Book livre;
    for (int i = 0; i < MAX_CHAPITRES; i++) {
        livre.chapters[i] = chapter_init();
    }
    return livre;
}

int main() {
    struct Book monLivre = book_init();
    char line[LINE_SIZE];
    int chapitreIndex = -1;

    FILE* file = fopen("book.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture de book.txt");
        return EXIT_FAILURE;
    }

    // Lecture ligne par ligne du fichier texte
    while (fgets(line, LINE_SIZE, file)) {
        if (strstr(line, "<chapter") != NULL) {
            chapitreIndex++;
            if (chapitreIndex < MAX_CHAPITRES) {
                monLivre.chapters[chapitreIndex] = chapter_init();
            }
        }

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
            printf("Choix %d -> Chapitre %d : %s\n", j + 1, ch->choices[j], ch->texteChoix[j]);
        }
    }

    return 0;
} 
