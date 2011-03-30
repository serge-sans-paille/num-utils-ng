
# include <stdlib.h>
# include <stdio.h>
#include <unistd.h>

double sum (FILE*);
int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);
	

double sum ( FILE* fichier){		//this function calculates the sum of numbers from a file or stdin.
	double sum=0.;
	double number=0.;
	while (!feof(fichier)){
		sum = sum + number ;					
		fscanf (fichier,"%lf",&number);
	}
return sum;
}

int fileTest(FILE* fichier){		//this function triggers every tests on the file.
    if (fileIsEmpty(fichier)){
      fprintf(stderr,"The file is empty \n");
      return 1;	
    }
    if (typeIsWrong(fichier)){
      fprintf(stderr,"the type of the file is wrong \n");
      return 1;
    }
    return 0;
}


int fileIsEmpty(FILE*fichier){			//this function tests if the file is empty.
  long position;
  fseek(fichier, 0L, SEEK_END);
  position=ftell(fichier);
  rewind(fichier);
  if (position==0)
    return 1;
  else 
    return 0;
}

int typeIsWrong(FILE*fichier){			//this function tests if there is letters in the file.	
	char c ;
	while (!feof(fichier)){
		fscanf ( fichier, "%c", &c );
		if ( (c>57) || ((c<48) && (c>32) && (c!=46)))
			return 1 ;
	}
	rewind (fichier);
	return 0;
}

int main(int argc,char *argv[]){
FILE* file = NULL;
int opt;
double d;
double r;
	
while((opt = getopt(argc,argv,"iI"))!=-1){
	switch(opt) {

	case 'i':			// option "-i" (integer portion of the final sum)
	if (argv[optind]!=NULL){
        	file = fopen(argv[optind], "r");
        	if (fileTest(file))
          	return 0;
        	fprintf(stderr,"The integer portion of the sum is %d \n",(int)sum(file));
        	fclose(file);
        	}
	else 
        printf("The integer portion of the sum is %d \n",(int)sum(stdin));
	return 0;
	break;

	case 'I':			//option "-I" (decimal portion of the final sum)
	if (argv[optind]!=NULL){
        	file = fopen(argv[optind], "r");
        	if (fileTest(file))
          		return 0;
			r = (int)sum(file);		 
			d = sum(file)-r; 
		fprintf(stderr,"The decimal portion of the sum is %lf \n",d);
        fclose(file);
        }
	else {
        	printf("The decimal portion of the average number is %lf \n",sum(stdin) - (int)sum(stdin));
	}
	return 0;
	break;

	case 'c':
	if (argv[optind]!=NULL){
        	file = fopen(argv[optind], "r");
        	if (fileTest(file))
          	return 0;
			int l=0,i,j,I,J;
			int C=0;
			int car; 
			if ( file != NULL){
				while ( (car= getc(file)) != EOF){
					if (car == '\n')
					++l;	
					if (car == ' ' && l==0)
					++C;
				}
			int tableau[l][C+1];
			int* tab=NULL;
			tab=malloc(C*sizeof(int));
			rewind(file);
			for(i=0; i<l*(C+1); i++){
			fscanf(file,"%d",&tableau[i/(C+1)][i % (C+1)]);
			}
			for (J=0;J<C+1;J++){
				for (I=0;I<l;I++){
					tab[J]=tab[J]+tableau[I][J];
				}
			printf("The sum of column %d is %d \n",J+1,tab[J]);
			fclose(file);
	}
	return 0;
	break;
	
			
			
	case '?':				//option fail.
	printf("optionfail\n");
	return 0;
	break;
	
	}
	}
	
	if (argv[optind]!=NULL){		
		file=fopen(argv[optind], "r");		
		if (fileTest(file))			
			return 0;
		fprintf(stderr,"The sum is %lf  \n",sum(file));
		fclose(file);
	}
	else
		printf("The sum is %lf \n",sum(stdin));
	return 0;




}
	

$

				
	
