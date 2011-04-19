/**
*
*
* ***** BEGIN GPL LICENSE BLOCK *****
*
* This file is part of num-utils-nv project
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program If not, see <http://www.gnu.org/licenses/>.
*
* The Original Code is Copyright (C) 2011 by num-utils-nv project.
* All rights reserved.
*
* The Original Code is: all of this file.
*
* Contributor(s): none yet.
*
* ***** END GPL LICENSE BLOCK *****
*/


# include <stdlib.h>
# include <stdio.h>
#include  <unistd.h>
#include <ctype.h>


enum {TYPE_ERROR=1, OPTION_ERROR };

double sum ( FILE* fichier){		//this function calculates the sum of numbers from a file or stdin.
  double sum=0.;
  double number=0.;
  while (!feof(fichier)){
    sum = sum + number ;					
    if(fscanf (fichier,"%lf",&number)!=EOF);
  }
 return sum;
}


int typeIsWrong(FILE* stream){				//this function tests if there is letters in the file.
  char c;
  while(fscanf(stream, "%c",&c)!=EOF){
    if (!isdigit(c) && !isspace(c) && !(c==46)) { 
    fprintf(stderr,"The type of the file is wrong.\n");
    fprintf(stderr,"the programm has detected an unexpected char : %c\n",c);
    return 1;
    }
  }
  rewind(stream);
  return 0;
}


void column ( FILE* file ){     // this function print out the sum of each column.
	int l=0,i,I,J;  
	int C=0;
	int car; 
	if (file != NULL){
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
		if(fscanf(file,"%d",&tableau[i/(C+1)][i % (C+1)])!=EOF);
	    }
	for (J=0;J<C+1;J++){
		for (I=0;I<l;I++){
			tab[J]=tab[J]+tableau[I][J];
		}
	      printf("The sum of column %d is %d \n",J+1,tab[J]);
	}
	fclose(file);
	}
	return;
}

double decimalPortion(FILE* file){     //this function calculates the decimal portion of the final sum 
	double d = sum(file);
	int i = (int)d;
	double res = d - (double)i;
	return res;
}

int main(int argc,char *argv[]){
	FILE* file = stdin;
	int opt;
	int m=0;				// for options (column, row).
	int s=0;				// for options (normal, integer portion and decimal portion).;
	while((opt = getopt(argc,argv,"iIcrh"))!=-1){
		switch(opt) {

		case 'i':			// option "-i" (integer portion of the final sum)
		s=1;     
		break;
		
		case 'I':			//option "-I" (decimal portion of the final sum)
        	s=2;
		break;

		case 'c':			//option "-c" (Print out the sum of each column.)
		m=1;
		break;
	
		case 'r':			//option "-r" (Print out the sum of each row.)
		m=2;
		break;

			
		case 'h':
		printf ( " sorry, the help page is not yet available.\n");
		return 0;
		break;
					
		default :				//option fail.
        	fprintf(stderr, "Invalid option\n");
        	return OPTION_ERROR;
		break;
	
    		}
  	}
	
	if (argc>optind){
		if (!(file = fopen(argv[optind], "r"))){
			perror("num-utils-ng"); 
			exit(EXIT_FAILURE);
		}
    		if (typeIsWrong(file))
			return TYPE_ERROR;
	}  
	
  if (s==0)
  	printf("result : %lf\n",sum(file));
  if (s==1)
  	printf("result : %d\n",(int)sum(file));
  if (s==2)
  	printf("result : %lf\n",decimalPortion(file));
  return EXIT_SUCCESS;

}
