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

void book_add(struct Book *book){
 book->chapters[0].idChapter=get_chapter();
 
     
 






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
