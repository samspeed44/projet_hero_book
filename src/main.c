#include "livre.h"

// Fonction pour initialiser un chapitre
struct Chapitre chapitre_init() {
    struct Chapitre chap;
    chap.idChapitre = -1;
    chap.nbChoix = 0;
    chap.titre[0] = '\0';
    chap.contenu[0] = '\0';
    for (int i = 0; i < MAX_CHOIX; i++) {
        chap.choix[i] = -1;
        chap.texteChoix[i][0] = '\0';
    }
    return chap;
}

// Fonction pour initialiser un livre
struct Livre livre_init() {
    struct Livre livre;
    for (int i = 0; i < MAX_CHAPITRES; i++) {
        livre.chapitres[i] = chapitre_init();
    }
    return livre;
}

int main() {
    struct Livre monLivre = livre_init();
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
                monLivre.chapitres[chapitreIndex] = chapitre_init();
            }
        }

        if (chapitreIndex >= 0 && chapitreIndex < MAX_CHAPITRES) {
            remplir_chapitre(&monLivre.chapitres[chapitreIndex], line);
        }
    }

    fclose(file);

    // Appelle la fonction pour générer les fichiers HTML
    affichage(&monLivre);

    return 0;
}
