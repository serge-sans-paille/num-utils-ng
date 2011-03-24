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


void normalize(FILE*, int, int);
void afficher(double *, int);
int fileIsEmpty(FILE*);
int typeIsWrong(FILE*);


int main(int argc,char *argv[]){
  FILE *stream=stdin;
  int optch;
  int numberL=0;
  int numberH=1;
	
  while((optch=getopt(argc,argv,"R:"))!=-1){
    switch(optch){
      case 'R':
        if(optarg){
	  sscanf(optarg,"%d..%d",&numberL,&numberH); 
	}
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
      fprintf(stderr,"the file can't be opened, see \"errno\" for more information");
      return 4;
    }
    if (typeIsWrong(stream))
      return 2;
    if (fileIsEmpty(stream))
      return 1;
  }
normalize(stream,numberL,numberH);
return 0;			
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
    *(tab+i)=*(tab+i)*(h-l)/(double)sum + l;
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
