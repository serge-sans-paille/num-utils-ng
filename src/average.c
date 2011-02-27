#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double mean(FILE*);
int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);
double median(FILE*,int);
double mode(FILE*);
double decimalPortion(double);

int main(int argc,char *argv[]){
  int opt;
  int m=0;				// for options (average, median and mode).
  int s=0;				// for options (normal, integer portion and decimal portion).
  int low=0;
  double res;
  FILE *stream=stdin;				// input stream (stdin or file).
  while((opt=getopt(argc,argv,"iIMml"))!=-1){
    switch(opt) {
      case 'i': 				// option "-i" (integer portion of the average)
        s=1;
      break;

      case 'I': 				//option "-I" (decimal portion of the average)
        s=2;
      break;

      case 'M':					//option "-M" (median)
        m=1;
      break;

      case 'l':					//option "-l" (median)
        low=1;
      break;

      case 'm':					//option "-m" (mode)
        m=2;
      break;

      default :				//option fail.
        fprintf(stderr, "invalid option\n");
        return 3;
      break;
    }
  }
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
  }  
  
  if (m==0)
  res=mean(stream);
  if (m==1){
    if (low==1)
      res=median(stream,1);
    else
      res=median(stream,0);
  }
  if (m==2)
  res=mode(stream);

  if (argc>1){
    if (fclose(stream)!=0){
      fprintf(stderr,"the file can't be closed, see \"errno\" for more infromation");
      return 5;
    }
  }

  if (s==0)
  printf("result : %lf\n",res);
  if (s==1)
  printf("result : %d\n",(int) res);
  if (s==2)
  printf("result : %lf\n",decimalPortion(res));
  return 0;
}

double decimalPortion(double d){
  int i;
  double res;
  i= (int) d;
  res= d- (double) i;
  return res;
}

double median(FILE* stream,int b){ 				//this function calculates the median.
  int l=0;
  double med;
  double *tab=NULL;
  tab=(double*) malloc(sizeof(double));
  if (tab==NULL)
    fprintf(stderr, "malloc fail");
  while(!feof(stream)){
    tab=(double*) realloc(tab,(l+1)*sizeof(double));
    if (tab==NULL)
      fprintf(stderr, "realloc fail");
    fscanf(stream,"%lf",&tab[l]);
    l++;
  }
  if (b==0){
    med=tab[(int) ((l-1)/2)];
    free(tab);
    return med;
  }
  else{
    med=tab[(int) ((l-2)/2)];
    free(tab);
    return med;
  }
}

double mode(FILE* stream){				//this functionn calculates the mode.
  int *nb=NULL;
  double *tab=NULL;
  double d;
  int i =0;
  int l =1;
  int nbmod=0;
  double mod;
  tab=(double*) malloc(sizeof(double));
  if (tab==NULL)
    fprintf(stderr, "malloc fail");
  nb=(int*) malloc(sizeof(int));
  if (tab==NULL)
    fprintf(stderr, "malloc fail");
  while(!feof(stream)){
    fscanf(stream,"%lf",&d);
    i=0;
    while(i<l){
      if (d==tab[i])
        nb[i]++;
      else {
        tab=(double*) realloc(tab,(l+2)*sizeof(double));
        if (tab==NULL)
          fprintf(stderr, "realloc fail");
        tab[l+1]=d;
        nb=(int*) realloc(nb,(l+2)*sizeof(int));
        if (tab==NULL)
          fprintf(stderr, "realloc fail");
        nb[l+1]=1;
        l++;
      }
    i++;
    }
  }
  i=0;
  while(i<l){
    if (nb[i]>nb[nbmod])
      nbmod=i;
    i++;
  }
  mod=tab[nbmod];
  free(tab);
  free(nb);
  return mod;
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


double mean(FILE *stream){				//this function calculates the average from a File or stdin depending on the argument.
  double l=0;
  double moyenne=0;
  double chiffre=0;
  while(!feof(stream)){
    moyenne+=chiffre;
    fscanf(stream,"%lf",&chiffre);
    l++;
  }
  moyenne/=(l-1);
  rewind(stream);
  return moyenne;
}
