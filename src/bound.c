#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


double bound(FILE*,int);
int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);
int fileTest(FILE*);


int main(int argc,char *argv[]){
  FILE *stream=stdin;
  int optch;
  int m=0;
  double res;

  while((optch=getopt(argc,argv,"l"))!=-1){
    switch(optch){
      case 'l':			//option "-l" (the lower bound number)
        m=1;
      break;

      default :		  	//option fail.
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

  res=bound(stream,m);

  if (argc>1){
    if (fclose(stream)!=0){
      fprintf(stderr,"the file can't be closed, see \"errno\" for more infromation");
      return 5;
    }
  }

  printf("result : %lf\n",res);
  return 0;			
}


double bound(FILE* stream, int mode){		//this function calculates the upper or lower bound from a file or stdin depending on the argument
	double lowerBound=0.;
	double upperBound=0.;
	double number=0.;
	if(!feof(stream)){
		fscanf(stream,"%lf",&number);
		lowerBound=number;
		upperBound=number;
	}		
	while(!feof(stream)){
		if (number>upperBound)
			upperBound=number;
		if (number<lowerBound)
			lowerBound=number;
		fscanf(stream,"%lf",&number);
	}
	if (mode==1)
		return lowerBound;
	else
		return upperBound;
				
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
