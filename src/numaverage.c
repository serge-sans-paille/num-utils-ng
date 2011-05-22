/**
*
*
* ***** BEGIN GPL LICENSE BLOCK *****
*
* This file is part of num-utils-ng project
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
* Contributor: Edern Hotte, Flavien Moullec, Reuven Benichou.
*
n***** END GPL LICENSE BLOCK *****
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

enum {
	TYPE_ERROR=1,
	OPTION_ERROR,
     };


static double decimalPortion(double d){
  int i= (int) d;
  double res= d- (double) i;
  return res;
}

static int isHigher(const void *a,const void *b){
if(*(double const *) a > * (double const *) b)
  return 1;
else if(*(double const *) a < * (double const *) b)
  return -1;
else
  return 0;
}

static double median(FILE* stream,int b){ 				//this function calculates the median.
  int nballoc=1,nbdouble=0;
  double med,d;
  double *tab=NULL;
  while(fscanf(stream,"%lf",&d)!=EOF){
    nbdouble++;
    if(nbdouble==nballoc){
      nballoc*=2;
      if(!(tab=(double*) realloc(tab,(nballoc)*sizeof(double)))){
        perror("num-utils-ng"); 
        exit(EXIT_FAILURE);
      }
    }
    tab[nbdouble-1]=d;
  }

  qsort(tab,nbdouble,sizeof(double),isHigher);
  if (decimalPortion(nbdouble/2.0)==0)
    med=tab[(nbdouble/2)-b];
  else
    med=tab[(nbdouble-1)/2];
  free(tab);
  return med;
}

static double mode(FILE* stream){				//this functionn calculates the mode.
  int *nb=NULL,nballoc=1;                                         // nb is an array of occurences bound to tab.
  double *tab=NULL;					//tab keeps in memory everyr different number in the stream.
  double d=0;
  int i,nbmod=0,done=0,nbdouble=0;
  while(fscanf(stream,"%lf",&d)!=EOF){
    i=0;
    done=0;
    while((i<nbdouble) && (done!=1)){
      if (d==tab[i]){
        nb[i]++;
        done=1;
      }
    i++;
    }
    if(done==0){
    nbdouble++;
      if (nbdouble==nballoc){
        nballoc*=2;
        if(!(tab=(double*) realloc(tab,(nballoc)*sizeof(double)))){
          perror("num-utils-ng"); 
          exit(EXIT_FAILURE);
        }
        if(!(nb=(int*) realloc(nb,(nballoc)*sizeof(int)))){
          perror("num-utils-ng"); 
          exit(EXIT_FAILURE);
        }
      }
      tab[nbdouble-1]=d;
      nb[nbdouble-1]=1;
    }
  }
  i=0;
  while(i<nbdouble){
    if (nb[i]>nb[nbmod])
      nbmod=i;
    i++;
  }
  d=tab[nbmod];
  free(tab);
  free(nb);
  return d;
}


static int typeIsWrong(FILE* stream){				//this function tests if there is letters in the file.
  char c;
  while(fscanf(stream, "%c",&c)!=EOF){
    if (!isdigit(c) && !isspace(c) && !(c==46) && !(c==45)) { 
    fprintf(stderr,"The type of the file is wrong.\n");
    fprintf(stderr,"the programm has detected an unexpected char : %c\n",c);
    return 1;
    }
  }
  rewind(stream);
  return 0;
}

static double mean(FILE *stream){				//this function calculates the average from a File or stdin depending on the argument.
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
  double res=0;
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
        if (system("/usr/bin/man numaverage")!=0){
          perror("num-utils-ng"); 
          exit(EXIT_FAILURE);
        }
        return 0;
      break;

      default :				//option fail.
        fprintf(stderr, "Invalid option\n");
        return OPTION_ERROR;
      break;
    }
  }
  if (argc>optind){
    if (!(stream = fopen(argv[optind], "r"))){
      perror("num-utils-ng"); 
      exit(EXIT_FAILURE);
    }
    if (typeIsWrong(stream))
      return TYPE_ERROR;
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
      perror("num-utils-ng"); 
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
