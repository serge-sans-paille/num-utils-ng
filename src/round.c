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
#include <math.h>

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

int roundc(FILE* stream,int m,int n){
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

int main(int argc,char *argv[]){
  int opt,m=0,f;
  FILE* stream=stdin;
    while((opt=getopt(argc,argv,"cfn:"))!=-1){
      switch(opt) {

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
  roundc(stream, m,f);
  if (argc>optind){
    if (fclose(stream)!=0){
      perror("memory allocation"); 
      exit(EXIT_FAILURE);      
    }
  }

  return 0;
}
