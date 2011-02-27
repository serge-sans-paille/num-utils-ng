#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int typeIsWrong(FILE* stream);
int fileIsEmpty(FILE* stream);
int interval(FILE* stream);


int main(int argc,char *argv[]){
  FILE* stream = NULL; 
  if (argc>optind){
    stream = fopen(argv[optind], "r");
    if (stream==NULL){
      fprintf(stderr,"the file can't be opened, see \"errno\" for more infromation");
      return 4;
    }
    if (typeIsWrong(stream))
      return 2;
    if (fileIsEmpty(stream))
      return 1;
    interval(stream);
    if (fclose(stream)!=0){
      fprintf(stderr,"the file can't be closed, see \"errno\" for more infromation");
      return 5;
    }
  }
  else 
    interval(stdin);
  return 0;
}


int fileIsEmpty(FILE* stream){				//this function tests if the file is empty.
  long pos;
  fseek(stream, 0L, SEEK_END);
  pos=ftell(stream);
  rewind(stream);
  if (pos==0){
    fprintf(stderr,"The file is empty\n");
    return 1;
  }
  else 
    return 0;
}

int typeIsWrong(FILE* stream){				//this function tests if there is letters in the file.
  char d;
  while(!feof(stream)){
    fscanf(stream, "%c",&d);
    if ((d>57) || ((d<48) && (d>32) && (d!=46))) { 
      fprintf(stderr,"The type of the file is wrong\n");
      return 1;
    }
  }
  rewind(stream);
  return 0;
}


int interval(FILE* stream){ 	
  double o,n;
  double *tab=NULL;
  int i=1;
  int l;
  fscanf(stream,"%lf",&o);
  tab=(double*) malloc(sizeof(double));
  if (tab==NULL)
    fprintf(stderr, "malloc fail");
  while(!feof(stream)){
    tab=(double*) realloc(tab,(i+1)*sizeof(double));
    if (tab==NULL)
      fprintf(stderr, "realloc fail");
    fscanf(stream,"%lf",&n);
    tab[i-1]=n-o;
    o=n;
    i++;
  }
  l=i;
  for(i=0;i<l-2;i++){
  printf("%lf\n",tab[i]);
  }
  free(tab);
  return 0;
}
