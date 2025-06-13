#include "book.h"

#define LINE_SIZE 512


struct Book book_init(){
    struct chapitre *newmalloc=(10*sizeof(struct chapitre));
    if (newmalloc==NULL){
        exit(1);
    }
    struct Book B={.chapitres=newmalloc};
    return B;
}


void Book_affiche(struct Book *B){
  for(int i=1; i<10;i++){
       if (B->chapter.idChapter==i){
          
           sprintf(filename, "O%d.html", i);
           f = fopen(filename, "w");
           if (f == NULL) {
                printf("Erreur d'ouverture du fichier %s\n", filename);
                exit(1);
            }
            fprintf(f, "<!DOCTYPE html>\n<html lang=\"fr\">\n<head>\n");
            fprintf(f, "<meta charset=\"UTF-8\">\n<title>%s</title>\n</head>\n", B->chapter.titre);
            fprintf(f, "<body>\n<h1>%s</h1>\n", B->chapter.titre);
            fprintf(f, "<p>%s</p>\n", B->chapter.content);

            
            fprintf(f, "</body>\n</html>");
            fclose(f);
        } 
    } 
} 

int main() {

  
    FILE* file = fopen("book.txt", "r");

    const char* filename = "book.txt";
    if (file == NULL) {
      printf("Unable to open file <%s>\n", filename);
      exit(EXIT_FAILURE);
    }

    char line[LINE_SIZE];

    while (fgets(line, sizeof(line), file)) {
        PrintChapter(line);
        get_paragraph(line);
    }

    fclose(file);
}
