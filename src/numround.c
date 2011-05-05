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
* ***** END GPL LICENSE BLOCK *****
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
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

static int roundc(FILE* stream,int m,int n){
  double d;
  if (m==0){
    while(fscanf(stream, "%lf",&d)!=EOF){     
      if (fabs(decimalPortion(d))<0.5)
        printf("result : %d\n", (int) d);
      else{
        if (d>=0)
          printf("result : %d\n", (int) d+1);
        else
          printf("result : %d\n", (int) d-1);
      }    
    }
  }
  if (m==1){
    while(fscanf(stream, "%lf",&d)!=EOF){
      if (d==(int)d)
        printf("result : %d\n", (int)d);
      else{
        if (d>=0)
          printf("result : %d\n", (int) d+1);
        else
          printf("result : %d\n", (int) d);
      }    
    }
  }
  if (m==2){
    while(fscanf(stream, "%lf",&d)!=EOF){
      if (d>=0)
        printf("result : %d\n", (int) d); 
      else
        printf("result : %d\n", (int) d-1);        
    }
  }
  if (m==3){
    while(fscanf(stream, "%lf",&d)!=EOF){     
      d=d/(double)n;
      if (fabs(decimalPortion(d))<0.5)
        printf("result : %d\n", (int)d*n);
      else
        if (d>=0)
          printf("result : %d\n", (int) (d+1)*n);
        else
          printf("result : %d\n", (int) (d-1)*n);            
    }
  }
  return 0;
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


int main(int argc,char *argv[]){
  int opt=0,m=0,f=0;
  FILE* stream=stdin;
    while((opt=getopt(argc,argv,"hcfn:"))!=-1){
      switch(opt) {

      case 'h':
        if (system("/usr/bin/man numround")!=0){
          perror("num-utils-ng"); 
          exit(EXIT_FAILURE);
        }
        return 0;
      break;

      case 'c': 				
        m=1;
      break;

      case 'f': 				
        m=2;
      break;

      case 'n': 				
        f=atoi(optarg);
        m=3;
      break;

      default :				//option fail.
        fprintf(stderr,"invalid option \n");
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
  roundc(stream, m,f);
  if (argc>optind){
    if (fclose(stream)!=0){
      perror("num-utils-ng"); 
      exit(EXIT_FAILURE);      
    }
  }

  return 0;
}
