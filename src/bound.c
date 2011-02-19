#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double bound(FILE*,int);
int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);
int fileTest(FILE*);


int main(int argc,char *argv[]){
	FILE* fp = NULL;
	int opt;
	
	while((opt=getopt(argc,argv,"l"))!=-1){
		switch(opt){
		
		case 'l':
			if (argv[optind]!=NULL){		//option "-l" (lower bound number)
				fp=fopen(argv[optind], "r");
				if (fileTest(fp))
					return 0;
				fprintf(stderr,"The lower bound is %lf \n",bound(fp,1));
				fclose(fp);
			}
			else 
				printf("The lower bound is %lf \n",bound(stdin,1));

			return 0;

		case '?':				//option fail
			printf("option fail\n");
      			return 1;
		}
	}

	if (argv[optind]!=NULL){
		fp=fopen(argv[optind], "r");
		if (fileTest(fp))
			return 0;
		fprintf(stderr,"The upper bound is %lf \n",bound(fp,2));
		fclose(fp);
	}
	else
		printf("The upper bound is %lf \n",bound(stdin,2));
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
  long position;
  fseek(stream, 0L, SEEK_END);
  position=ftell(stream);
  rewind(stream);
  if (position==0)
    return 1;
  else 
    return 0;
}
