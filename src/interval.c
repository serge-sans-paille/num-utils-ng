#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int fileTest(FILE* stream);
int typeIsWrong(FILE* stream);
int fileIsEmpty(FILE* stream);
int interval(FILE* stream);

int fileTest(FILE* stream){				//this function triggers every tests on the file.
    if (fileIsEmpty(stream)){
      fprintf(stderr,"The file is empty \n");
      return 1;	
    }
    if (typeIsWrong(stream)){
      fprintf(stderr,"the type of the file is wrong \n");
      return 1;
    }
    return 0;
}

int typeIsWrong(FILE* stream){				//this function tests if there is letters in the file.
  char d;
  while(!feof(stream)){
    fscanf(stream, "%c",&d);
    if ((d>57) || ((d<48) && (d>32) && (d!=46)))  
      return 1;
  }
  rewind(stream);
  return 0;
}


int fileIsEmpty(FILE* stream){				//this function tests if the file is empty.
  long pos;
  fseek(stream, 0L, SEEK_END);
  pos=ftell(stream);
  rewind(stream);
  if (pos==0)
    return 1;
  else 
    return 0;
}


int interval(FILE* stream){ 	
  double o,n;
  double *tab=NULL;
  int i=1;
  int l;
  fscanf(stream,"%lf",&o);
  tab=(double*) malloc(sizeof(double));
  while(!feof(stream)){
    tab=(double*) realloc(tab,(i+1)*sizeof(double));
    fscanf(stream,"%lf",&n);
    tab[i-1]=n-o;
    o=n;
    i++;
  }
  l=i;
  for(i=0;i<l-2;i++){
  printf("%lf \n",tab[i]);
  }
  free(tab);
  return 0;
}


int main(int argc,char *argv[]){
  FILE* tab = NULL; 
  if (argc>optind){
    tab = fopen(argv[optind], "r");
    if (fileTest(tab))
      return 0;
    interval(tab);
    fclose(tab);
    }  
  else 
    interval(stdin);
  return 0;
}
