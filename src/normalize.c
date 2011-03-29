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



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


enum {ERROR_1=1,ERROR_2,ERROR_3,ERROR_4};

void afficher(double *tab, int count){
  int i=0;
  for(i=0;i<count-1;i++){
    printf("%lf \n",tab[i]);
  }
}


void normalize(FILE* stream,int l, int h){		//this function normalize
  double *tab=NULL;
  double *numbersBis=NULL;
  double number=0.;
  double sum=0.;
  int count=0;
  int i;
  while(!feof(stream)){
    fscanf(stream,"%lf",&number);
    sum+=number;
    if(!(tab =(double*)calloc(count+1,sizeof(double)))){
      perror("memory allocation");
      exit(EXIT_FAILURE); 
    }
    tab[count]=number;
    for(i=0;i<count;i++)
      tab[i]=numbersBis[i];
      count++;
      if(!(numbersBis =(double*)calloc(count,sizeof(double)))){
        perror("memory allocation");
        exit(EXIT_FAILURE); 
      }
      for(i=0;i<count;i++)
        numbersBis[i]=tab[i];
  }
  sum-=number;
  for(i=0; i<count;i++){
    *(tab+i)=*(tab+i)*(h-l)/(double)sum + l;
  }
  afficher(tab,count);
  free(tab);	
}


int typeIsWrong(FILE* stream){				//this function tests if there is letters in the file.
  char d;
  while(!feof(stream)){
    fscanf(stream, "%c",&d);
    if ((d>57) || ((d<48) && (d>32) && (d!=46))) { 
      perror("The type of the file is wrong\n");
      return ERROR_1;
    }
  }
  rewind(stream);
  return EXIT_SUCCESS;
}


int main(int argc,char *argv[]){
  FILE *stream=stdin;
  int optch;
  int numberL=0;
  int numberH=1;
	
  while((optch=getopt(argc,argv,"R:"))!=-1){
    switch(optch){
      case 'R':
        if(optarg){
	  if(!sscanf(optarg,"%d..%d",&numberL,&numberH)){
            perror("invalid argument\n");
            exit(EXIT_FAILURE);
	  }
        }
      break;
      
      default :		  	//option fail.
        perror("invalid option\n");
        return ERROR_3;
      break;
    }
  }

  if (argc>optind){
    if(!(stream = fopen(argv[optind], "r"))){
      perror("the file can't be opened, see \"errno\" for more information");
      return ERROR_4;
    }
    if (typeIsWrong(stream))
      return ERROR_2;
  }
  normalize(stream,numberL,numberH);
  return EXIT_SUCCESS;			
}



