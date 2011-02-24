#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void normalize(FILE*);
void afficher(double *, int);
int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);
int fileTest(FILE*);


int main(int argc,char *argv[]){
	FILE* fp = NULL;
	double *tab=NULL;
	int count=0;
	int opt;
	int i=0;
	
	while((opt=getopt(argc,argv,"R"))!=-1){
		switch(opt){
		
		case 'R':
			if (argv[optind]!=NULL){		// This allows you to specify a different normalized range instead of from 0 to 1
				if((fp=fopen(argv[optind], "r"))==NULL){
					printf("The file is protected or doesn't exist \n");
					return 1;
				}
				else{
					if (fileTest(fp))
						return 0;
					normalize(fp);
					fclose(fp);
				}
			}
			else
				normalize(fp);

			return 0;

		case '?':				//option fail
			printf("option fail\n");
      			return 1;
		}
	}

	if (argv[optind]!=NULL){				 //normalized set of numbers between 0 and 1
		if((fp=fopen(argv[optind], "r"))==NULL){
			printf("The file is protected or doesn't exist \n");
			return 1;
		}
		else{
			if (fileTest(fp))
				return 0;
			normalize(fp);
			fclose(fp);
		}
	}
	else
		normalize(stdin);
	return 0;
			
}


void normalize(FILE* stream){		//this function normalize
	double *tab=NULL;
	double *numbersBis=NULL;
	double number=0.;
	double sum=0.;
	int count=0;
	int i;
	while(!feof(stream)){
		fscanf(stream,"%lf",&number);
		sum+=number;
		tab =(double*)calloc(count+1,sizeof(double));
		tab[count]=number;
		for(i=0;i<count;i++)
			tab[i]=numbersBis[i];
		count++;
		numbersBis =(double*)calloc(count,sizeof(double));
		for(i=0;i<count;i++)
			numbersBis[i]=tab[i];
	}
	sum-=number;
	for(i=0; i<count;i++){
		*(tab+i)=*(tab+i)/(double)sum;
	}
	afficher(tab,count);
	free(tab);
	
}


void afficher(double *tab, int count){
	int i=0;
	for(i=0;i<count-1;i++){
		printf("%lf \n",tab[i]);
	}
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
