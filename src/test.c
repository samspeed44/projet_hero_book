#include <stdio.h>
#include <stdlib.h>

FILE* file = fopen(book.txt, "r");
if (file == NULL) {
  printf("Unable to open file <%s>\n", filename);
  exit(EXIT_FAILURE);
}

char line[512];
while(fgets(line, sizeof(line), file)) {
  int id;
  char titre[200];
  sscanf(line,"<chapter id=\"%d\">%s<|chapter>",&id,titre);     
  // Ligne que je cherche  sscanf(8,"<chapter id=\"%d\">%s<|chapter>"),2,La Forêt de Bois-Perdu);
  return        
}
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

  
} /*











