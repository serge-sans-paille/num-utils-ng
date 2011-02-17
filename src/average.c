#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double mean(FILE*);
int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);
int fileTest(FILE*);

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

int main(int argc,char *argv[]){
  FILE* tab = NULL; 
  int opt;
  double d;                              //d is used to store any double which needs storage.
  while((opt=getopt(argc,argv,"iI"))!=-1){
    switch(opt) {

    case 'i': 				// option "-i" (integer portion of the average)
      if (argv[optind]!=NULL){
        tab = fopen(argv[optind], "r");
        if (fileTest(tab))
          return 0;
        fprintf(stderr,"The integer portion of the average number is %d \n",(int) mean(tab));
        fclose(tab);
        }
      else 
        printf("The integer portion of the average number is %d \n",(int) mean(stdin));
      return 0;
      break;

    case 'I': 				//option "-I" (decimal portion of the average)
      if (argv[optind]!=NULL){
        tab = fopen(argv[optind], "r");
        if (fileTest(tab))
          return 0;
        fprintf(stderr,"The decimal portion of the average number is %lf \n",mean(tab) - (int) mean(tab));
        fclose(tab);
        }
      else {
        d=mean(stdin);
        printf("The decimal portion of the average number is %lf \n",d - (int) d);
      }
      return 0;
      break;

    case '?':				//option fail.
      printf("optionfail\n");
      return 0;
      break;
    }
  }
    if (argv[optind]!=NULL){		//normal use of "average".
      tab = fopen(argv[optind], "r");
      if (fileTest(tab))
        return 0;
      fprintf(stderr,"The average number is %lf \n",mean(tab));
      fclose(tab);
      }
    else 
      printf("The average number is %lf \n",mean(stdin));
  return 0;
}
