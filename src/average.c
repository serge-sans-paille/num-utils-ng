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

enum {
	ERROR_1=1,
	ERROR_2,
     };


double decimalPortion(double d){
  int i;
  double res;
  i= (int) d;
  res= d- (double) i;
  return res;
}

int isHigher(const void *a,const void *b){
if(*(double const *) a > * (double const *) b)
  return 1;
else
  return 0;
}

double median(FILE* stream,int b){ 				//this function calculates the median.
  int l=0;
  double med;
  double *tab=NULL;
  if(!(tab=(double*) malloc(sizeof(double)))){
    perror("memory allocation"); 
    exit(EXIT_FAILURE);
  }
  while(fscanf(stream,"%lf",&tab[l])!=EOF){
    if(!(tab=(double*) realloc(tab,(l+2)*sizeof(double)))){
      perror("memory allocation"); 
      exit(EXIT_FAILURE);
    }
    l++;
  }

  qsort(tab,l+1,sizeof(double),isHigher);

  if (decimalPortion((float)l/2)==0){
printf("even\n");
    if (b==0)
      med=tab[(int) (l/2 +1)];
    else
      med=tab[(int) (l/2)];
  }
  else
    med=tab[(int) (l/2) + 1];
  free(tab);
  return med;
}

double mode(FILE* stream){				//this functionn calculates the mode.
  int *nb=NULL;                                         // nb is an array of occurences bound to tab.
  double *tab=NULL;					//tab keeps in memory everyr different number in the stream.
  double d;
  int i =0;
  int l =1;
  int nbmod=0;
  double mod;
  if(!(tab=(double*) malloc(sizeof(double)))){
    perror("memory allocation"); 
    exit(EXIT_FAILURE);
  }
  if (!(nb=(int*) malloc(sizeof(int)))){
    perror("memory allocation");
    exit(EXIT_FAILURE);
  }
  while(fscanf(stream,"%lf",&d)){
    i=0;
    while(i<l){
      if (d==tab[i])
        nb[i]++;
      else {
        if(!(tab=(double*) realloc(tab,(l+2)*sizeof(double)))){
          perror("memory allocation"); 
          exit(EXIT_FAILURE);
        }
        tab[l+1]=d;
        if(!(nb=(int*) realloc(nb,(l+2)*sizeof(int)))){
          perror("memory allocation"); 
          exit(EXIT_FAILURE);
        }
        nb[l+1]=1;
        l++;
      }
    i++;
    }
  }
  i=0;
  while(i<l){
    if (nb[i]>nb[nbmod])
      nbmod=i;
    i++;
  }
  mod=tab[nbmod];
  free(tab);
  free(nb);
  return mod;
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

double mean(FILE *stream){				//this function calculates the average from a File or stdin depending on the argument.
  double l=0;
  double average=0;
  double d=0;
  while(fscanf(stream,"%lf",&d)!=EOF){
    average+=d;
    l++;
  }
  average/=l;
  rewind(stream);
  return average;
}

int main(int argc,char *argv[]){
  int opt;
  int m=0;				// for options (average, median and mode).
  int s=0;				// for options (normal, integer portion and decimal portion).
  int low=0;
  double res;
  FILE *stream=stdin;				// input stream (stdin or file).
  while((opt=getopt(argc,argv,"iIMmlh"))!=-1){
    switch(opt) {
      case 'i': 				// option "-i" (integer portion of the average)
        s=1;
      break;

      case 'I': 				//option "-I" (decimal portion of the average)
        s=2;
      break;

      case 'M':					//option "-M" (median)
        m=1;
      break;

      case 'l':					//option "-l" (median)
        low=1;
      break;

      case 'm':					//option "-m" (mode)
        m=2;
      break;

      case 'h':
        printf("sorry, the help page is not yet available.\n");
        return 0;
      break;

      default :				//option fail.
        fprintf(stderr, "Invalid option\n");
        return ERROR_2;
      break;
    }
  }
  if (argc>optind){
    if (!(stream = fopen(argv[optind], "r"))){
      perror("memory allocation"); 
      exit(EXIT_FAILURE);
    }
    if (typeIsWrong(stream))
      return ERROR_1;
  }  
  
  if (m==0)
    res=mean(stream);
  if (m==1){
    if (low==1)
      res=median(stream,1);
    else
      res=median(stream,0);
  }
  if (m==2)
  res=mode(stream);

  if (argc>1){
    if (fclose(stream)!=0){
      perror("memory allocation"); 
      exit(EXIT_FAILURE);
    }
  }

  if (s==0)
  printf("result : %lf\n",res);
  if (s==1)
  printf("result : %d\n",(int) res);
  if (s==2)
  printf("result : %lf\n",decimalPortion(res));
  return EXIT_SUCCESS;
}
