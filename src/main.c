#include "book.h"

#define LINE_SIZE 512


struct Book book_init(){
    struct chapitre *newmalloc=(10*sizeof(struct chapitre));
    if (newmalloc==NULL){
        exit(1);
    }
    struct Book B={.chapitre=newmalloc};
    return B;
}


/*void Book_affiche(struct Book *B){
  for(int i=0; i<11;i++){}
  if (B->chapter.idChapter==1){
    fopen("O1.html","w")
    fprintf("<h1>",B->chapter.titre;"</h1>")
    fprint("<p>",B->chapter.content,"</p>")
  }

  
} */

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
