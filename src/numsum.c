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
#include <string.h>
#include <ctype.h>


enum {TYPE_ERROR=1, OPTION_ERROR };


static int skipWord(FILE* stream){    //this function tests if there is letters in the file.
char c='a';
if (stream==stdin)
  fprintf(stderr,"This is not a number!\n");
while(!isdigit(c) && !isspace(c) && !(c==46) && !(c==45)){
  if(fscanf(stream, "%c",&c)!=1){
    perror("num-utils-ng"); 
    exit(EXIT_FAILURE);
  }
}
return 0;
}


static double sum ( FILE* stream){		//this function calculates the sum of numbers from a file or stdin.
  double sum=0.;
  double number=0.;
  while (!feof(stream)){
    sum = sum + number ;					
    if(fscanf (stream,"%lf",&number)!=EOF);
  }
 return sum;
}


static double column(FILE* stream,int *tab,int count2){     // this function print out the sum of each column.
  double *tabNumber=NULL;
  double number;
  int lengthTab=1, countMax=0, count=0;
  int test,i;
  if(!(tabNumber=(double*) calloc(1,sizeof(double)))){
    perror("num-utils-ng"); 
    exit(EXIT_FAILURE);
  }
  while((test=fscanf(stream,"%lf",&number))!=EOF){
    if(!test)
      skipWord(stream);
    if(!tab){
      if(count == lengthTab){
        lengthTab*=2;
        if(!(tabNumber =(double*)realloc(tabNumber,lengthTab*sizeof(double)))){
          perror("num-utils-ng"); 
          exit(EXIT_FAILURE);
        }
      }
      if(fgetc(stream)!='\n'){
        tabNumber[count] += number;
        count++;
		
      }
      else {
	if(count>=countMax)
	  countMax=count;
        tabNumber[count] += number;
	count=0;
      }
    }
  }
  for(i=0;i<countMax+1;i++){
    printf("3 %lf\n",tabNumber[i]);
  }
  free(tabNumber);
  return 0;
}

static double row(FILE* stream,int *tab,int count){              // this function print ou the sum of each row or specified row.
  double somme=0.,number;
  int test,line=1,i=0;
  while((test=fscanf(stream,"%lf",&number))!=EOF){
    if(!test)
        skipWord(stream);
    if(!tab){
      if(fgetc(stream)=='\n'){
        somme+=number;
        printf("%lf \n",somme);
        somme=0.;
        number=0.;
      }
      somme+=number;
    }
    else{
      if(line==tab[i]){
        somme+=number;
      }
      if(fgetc(stream)=='\n'){
        if(line==tab[i]){
          i++;
          printf("%lf \n",somme);
        }
        line++;
        somme=0.;
        number=0.;
      }   
    } 
  }
  return 0;
}


static double decimalPortion(double d){     //this function calculates the decimal portion of the final sum 
	int i = (int)d;
	double res = d - (double)i;
	return res;
}

int main(int argc,char *argv[]){
	FILE*stream = stdin;
	int opt;
	double res=0;
	int m=0;				// for options (column, row).
	int s=0;

	int *tab = NULL;                        // tab for expression after -x
	char *numColumn=NULL;
	char *token;
  	char *savestr=NULL;
  	char *str; 
	int count=0;
	int i;

						// for options (normal, integer portion and decimal portion).;
	while((opt = getopt(argc,argv,"iIcx:ry:h"))!=-1){
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

		case 'x':
		m=1;
		numColumn = optarg;
		printf("%s\n",numColumn);                    
		break;

		case 'r':			//option "-r" (Print out the sum of each row.)
		m=2;
		break;

                case 'y':
		m=2;
		numColumn = optarg;
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
	
	if(numColumn){
	for (i=0;i<strlen(numColumn);i++){
   	  switch(numColumn[i])
    	  {
	    case '0':
      	    case '1':
      	    case '2':
     	    case '3':
      	    case '4':
     	    case '5':
     	    case '6':
      	    case '7':
      	    case '8':
      	    case '9':
            break;
	    case ',':
	      count++;      
	    break;
	    default:
	      perror("this argument isn't correct");
              return 1;
	  }
	}
		
	if(!(tab =(int *)calloc(count+1,sizeof(int)))){
    	  perror("num-utils-ng");
    	  exit(EXIT_FAILURE);
  	}
	for (i=0,str=numColumn;;i++,str=NULL) {
    	  token=strtok_r(str,",", &savestr);
    	  if (!token)
     	    break;
    	  *(tab+i)=atoi(token);
 	}
	}
	
	if (argc>optind){
		if (!(stream = fopen(argv[optind], "r"))){
			perror("num-utils-ng"); 
			exit(EXIT_FAILURE);
		}
	}

	
	if (m==0)
		res = sum(stream);
	if (m==1){
		s=3;
		res = column(stream,tab,count+1); // argument 2 : number of column , argument 3 : 
	}	
	if (m==2){
		s=3;
		res = row(stream,tab,count+1);
	}
	
  if (argc>1){
    if (fclose(stream)!=0){
      perror("num-utils-ng"); 
      exit(EXIT_FAILURE);
    }
  }

		
  if (s==0)
  	printf("result : %lf\n",res);
  if (s==1)
  	printf("result : %d\n",(int)res);
  if (s==2)
  	printf("result : %lf\n",decimalPortion(res));
  return EXIT_SUCCESS;

}
