#include <stdlib.h>
#include <stdio.h>

double mean(FILE*);
int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);

int typeIsWrong(FILE* stream){
  char d;
  while(!feof(stream)){
    fscanf(stream, "%c",&d);
    if ((d>57) || ((d<48) && (d>32) && (d!=46)))  
  return 1;
  }
  rewind(stream);
  return 0;
}


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
      fprintf(stderr,"The file is empty \n");
      return 0;	
    }
    if (typeIsWrong(tab)){
      fprintf(stderr,"the type of the file is wrong \n");
      return 0;
    }
    fprintf(stderr,"The average number is %lf \n",mean(tab));
    fclose(tab);
  }
  else 
    printf("The average number is %lf \n",mean(stdin));
  return 0;
}
