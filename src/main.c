#include "book.h"

#define LINE_SIZE 512


struct Book book_init(){
    struct chapitre *newmalloc=(10*sizeof(struct chapitre));
    if (newmalloc==NULL){
        exit(1);
    }
    struct Book book={.chapters=newmalloc};
    return book;
}


void Book_affiche(struct Book *book){
  for(int i=0; i < 10; i++){
       if (book->chapters[i].idChapter==i+1){
          
           sprintf(filename, "O%d.html", i);
           f = fopen(filename, "w");
           if (f == NULL) {
                printf("Erreur d'ouverture du fichier %s\n", filename);
                exit(1);
            }
            fprintf(f, "<!DOCTYPE html>\n<html lang=\"fr\">\n<head>\n");
            fprintf(f, "<meta charset=\"UTF-8\">\n<title>%s</title>\n</head>\n", book->chapters.title);
            fprintf(f, "<body>\n<h1>%s</h1>\n", book->chapters.title);
            fprintf(f, "<p>%s</p>\n", book->chapters.content);

            
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
