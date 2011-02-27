#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);
double decimalPortion(double);
int roundc(FILE*,int,int);

int main(int argc,char *argv[]){
  int opt;
  int m=0;
  int f=0;
  FILE* stream=stdin;
    while((opt=getopt(argc,argv,"cfn:"))!=-1){
      switch(opt) {

      case 'c': 				
        m=1;
      break;

      case 'f': 				
        m=2;
      break;

      case 'n': 				
        f=atoi(optarg);
        m=3;
      break;

      default :				//option fail.
        fprintf(stderr,"invalid option \n");
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
  

  roundc(stream, m,f);


  if (argc>1){
    if (fclose(stream)!=0){
      fprintf(stderr,"the file can't be closed, see \"errno\" for more infromation");
      return 5;
    }
  }

  return 0;
}


double decimalPortion(double d){
  int i;
  double res;
  i= (int) d;
  res= d- (double) i;
  return res;
}

int roundc(FILE* stream,int m,int n){
  double d;
  fscanf(stream, "%lf",&d);
  if (m==0){
    while(!feof(stream)){     
      if (fabs(decimalPortion(d))<0.5)
        printf("result : %d\n", (int) d);
      else{
        if (d>=0)
          printf("result : %d\n", (int) d+1);
        else
          printf("result : %d\n", (int) d-1);
      }
     fscanf(stream, "%lf",&d);      
    }
  }
  if (m==1){
    while(!feof(stream)){
      if (d==(int)d)
        printf("result : %d\n", (int)d);
      else{
        if (d>=0)
          printf("result : %d\n", (int) d+1);
        else
          printf("result : %d\n", (int) d);
      }
      fscanf(stream, "%lf",&d);      
    }
  }
  if (m==2){
    while(!feof(stream)){
      if (d>=0)
        printf("result : %d\n", (int) d); 
      else
        printf("result : %d\n", (int) d-1);    
      fscanf(stream, "%lf",&d);    
    }
  }
  if (m==3){
    while(!feof(stream)){     
      d=d/(double)n;
      if (fabs(decimalPortion(d))<0.5)
        printf("result : %d\n", (int)d*n);
      else
        if (d>=0)
          printf("result : %d\n", (int) (d+1)*n);
        else
          printf("result : %d\n", (int) (d-1)*n);
     fscanf(stream, "%lf",&d);            
    }
  }
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
