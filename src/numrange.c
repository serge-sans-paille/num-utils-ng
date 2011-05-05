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

static int range(char* expression,char separator){
  double numberL=0,numberH=0, numberStep=0,numberL2=0;
  int i,count=0;
  char *token=NULL;
  char *savestr=NULL;
  char *str=NULL;
  char **tab=NULL;
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
        numberL2=numberL;
        while(numberL2>=numberH){
          fprintf(stdout,"%lf%c",numberL2,separator);
          numberL2+=numberStep;
        }
      }
      if (numberL<numberH){
          if (numberStep==0) 
	    numberStep=1;   
        numberL2=numberL;
        while(numberL2<=numberH){
          fprintf(stdout,"%lf%c",numberL2,separator);
          numberL2+=numberStep;
        }
      }
  } 
  free(tab);
  return 0;
}


int main(int argc,char *argv[]){
  int opt;
  char separator=' ';
  while((opt=getopt(argc,argv,"heNn:"))!=-1){
    switch(opt) {
      case 'h':
        printf("Sorry, the help page is not available yet.\n");
        return 0;
      break;

      case 'N':
        separator='\n';
      break;

      case 'n':       
        separator=*optarg;
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
    if(range(argv[optind],separator)==1){
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
