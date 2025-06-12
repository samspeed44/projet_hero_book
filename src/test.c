#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 512

struct chapitre{ 
  int idChapter;
  char titre[200];
  char content[520];
  char choice1;
  char choice2;
};

struct Book{
  struct chapitre *chapitre;
  };


struct Book book_init(){
    struct chapitre *newmalloc=(10*sizeof(struct chapitre));
    if (newmalloc==NULL){
        exit(1);
    }
    struct Book B={.chapitre=newmalloc,chapter_number=10};
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











void PrintChapter(char* line) {
    int idChapter;
    char titre[200];
    if (strstr(line, "<chapter") != NULL) {
        sscanf(line, "<chapter id=\"%d\">%[^<]s</chapter>", &idChapter, titre);
        printf("Chapitre ID: %d, Titre: %s\n", idChapter, titre);
    }
}

int main() {

  
    FILE* file = fopen("book.txt", "r");

    if (file == NULL) {
      printf("Unable to open file <%s>\n", filename);
      exit(EXIT_FAILURE);
    }

    char line[LINE_SIZE];

    while (fgets(line, sizeof(line), file)) {
        PrintChapter(line);
    }

    fclose(file);
}
