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
#include <unistd.h>

enum {ERROR_2};

double sum ( FILE* fichier){		//this function calculates the sum of numbers from a file or stdin.
  double sum=0.;
  double number=0.;
  while (!feof(fichier)){
    sum = sum + number ;					
    fscanf (fichier,"%lf",&number);
  }
 return sum;
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
  double d,r;
	
  while((opt = getopt(argc,argv,"iIcrh"))!=-1){
    switch(opt) {

      case 'i':			// option "-i" (integer portion of the final sum)
        if (argv[optind]!=NULL){
          file = fopen(argv[optind], "r");
          if (typeIsWrong(file))
            return 1;
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
            if (typeIsWrong(file))
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

      case 'c':			//option "-c" (Print out the sum of each column.)
	if (argv[optind]!=NULL){
          file = fopen(argv[optind], "r");
          if (typeIsWrong(file))
            return 1;
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
	      fscanf(file,"%d",&tableau[i/(C+1)][i % (C+1)]);
	    }
	    for (J=0;J<C+1;J++){
	      for (I=0;I<l;I++){
	        tab[J]=tab[J]+tableau[I][J];
	      }
	      printf("The sum of column %d is %d \n",J+1,tab[J]);
	    }
	    fclose(file);
	  }
	  return 0;
        }
	break;
	
      case 'r':			//option "-r" (Print out the sum of each row.)
	if (argv[optind]!=NULL){
          file = fopen(argv[optind], "r");
          if (typeIsWrong(file))
            return 1;
	}
      break;

			
      case 'h':
	printf ( " sorry, the help page is not yet available.\n");
	return 0;
      break;
					
      default :				//option fail.
        fprintf(stderr, "Invalid option\n");
        return ERROR_2;
      break;
	
    }
  }
	
  if (argv[optind]!=NULL){		
    file=fopen(argv[optind], "r");		
    if (typeIsWrong(file))			
      return 1;
    fprintf(stderr,"The sum is %lf  \n",sum(file));
    fclose(file);
  }
  else
    printf("The sum is %lf \n",sum(stdin));
  return 0;
}
	



				
	
