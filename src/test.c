#include <stdio.h>
#include <stdlib.h>

FILE* file = fopen(filename, "r");
if (file == NULL) {
  printf("Unable to open file <%s>\n", filename);
  exit(EXIT_FAILURE);
}

char line[512];
while(fgets(line, sizeof(line), file)) {
  // ...
}



