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
* Contributor(s): Edern Hotte, Flavien Moullec, Reuven Benichou.
*
* ***** END GPL LICENSE BLOCK *****
*/



#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h>

enum {OPTION_ERROR=1,
      EXPR_ERROR,
      MISSEXPR_ERROR};

static int range(char* expression,char separator, char* exceptions){
  double numberL=0,numberH=0, numberStep=0;
  int i=0,count=0,j,isException=0,l=0;
  char *token=NULL;
  char *savestr=NULL;
  char *str=NULL;
  char **tab=NULL;
  double *exceptiontab=NULL;
  if(!(exceptiontab=(double*)malloc((int) strlen(exceptions)*sizeof(double)))){
    perror("num-utils-ng");
    exit(EXIT_FAILURE);
  } 
  for (j=0,str=exceptions;;j++,str=NULL) {
    token=strtok_r(str,",", &savestr);
    if (token == NULL)
      break;
    sscanf(token,"%lf",&exceptiontab[j]);
    l++;
  }  
  for (i=0;i<strlen(expression);i++){
    switch(expression[i])
    {
      case '/':
        expression[i]=',';
	break;
      case '.':
	break;
      case ':':
	break;
      case '-':
	break;
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
      case 'i':          
	break;
      case ',':
        count++;
        break;
      default:
	perror("this expression is not correct");
        return 1;
    }
  }
  if(!(tab =(char **)calloc(count+1,sizeof(char*)))){
    perror("num-utils-ng");
    exit(EXIT_FAILURE);
  } 
  for (i=0,str=expression;;i++,str=NULL) {
    token=strtok_r(str,",", &savestr);
    if (token == NULL)
      break;
    *(tab+i)=token;
  }  
  for(i=0;i<=count;i++){
     numberStep=0;
      sscanf(*(tab+i),"%lf:%lfi%lf",&numberL,&numberH,&numberStep);       
     if (numberL>numberH){
        if (numberStep==0) 
	  numberStep=-1;    
        while(numberL>=numberH){
          for (j=0;j<=l-1;j++){
            if (numberL==exceptiontab[j]){
               isException=1;
               j=l;
            }
	  }
	  if (isException==0)
            fprintf(stdout,"%lf%c",numberL,separator);
          isException=0;
          numberL+=numberStep;
        }
      }
      else {
          if (numberStep==0) 
	    numberStep=1;   
        while(numberL<=numberH){
          for (j=0;j<=l-1;j++){
            if (numberL==exceptiontab[j]){
               isException=1;
               j=l;
            }
	  }
          if (isException==0)
            fprintf(stdout,"%lf%c",numberL,separator);
	  isException=0;
          numberL+=numberStep;
        }
      }
  } 
  free(tab);
  free(exceptiontab);
  return 0;
}


int main(int argc,char *argv[]){
  int opt;
  char separator=' ';
  char *exceptions=NULL;
  while((opt=getopt(argc,argv,"he:Nn:"))!=-1){
    switch(opt) {
      case 'h':
        system("/usr/bin/man numrange");
        return 0;
      break;

      case 'N':
        separator='\n';
      break;

      case 'n':       
        separator=*optarg;
      break;
      
      case 'e':
        exceptions=optarg;
      break;

      default :				//option fail.
        fprintf(stderr, "Invalid option\n");
        return OPTION_ERROR;
      break;
    }
  }
  if(argc>optind){
    if(argv[optind][0]!='/'){
      fprintf(stderr,"The expression is wrong.\n");
      return EXPR_ERROR;
    }
    if(range(argv[optind],separator,exceptions)==1){
      fprintf(stderr,"The expression is wrong.\n");
      return EXPR_ERROR;
    }
    fprintf(stdout,"\n");
  }
  else{
    fprintf(stderr,"The expression is missing.\n");
    return MISSEXPR_ERROR; 
  }
  return 0;
}
