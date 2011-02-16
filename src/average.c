#include <stdlib.h>
#include <stdio.h>

double mean(FILE*);
int fileIsEmpty(FILE*);

int fileIsEmpty(FILE* stream){
  long pos;
  fseek(stream, 0L, SEEK_END);
  pos=ftell(stream);
  rewind(stream);
  if (pos==0)
    return 1;
  else 
    return 0;
}

double mean(FILE *stream){
  double l=0;
  double moyenne=0;
  double chiffre=0;
  while(!feof(stream)){
    moyenne+=chiffre;
    fscanf(stream,"%lf",&chiffre);
    l++;
  }
  moyenne/=(l-1);
  return moyenne;
}

int main(int argc,char *argv[]){
  FILE* tab = NULL;   
  if (argc > 1){
    tab = fopen(argv[1], "r");
    if (fileIsEmpty(tab)){
      printf("The file is empty \n");
      return 1;	
    }
    printf("The average number is %lf \n",mean(tab));
    fclose(tab);
  }
  else 
    printf("The average number is %lf \n",mean(stdin));
  return 0;
}
