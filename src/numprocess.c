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
#include <string.h>
#include <math.h>
#include <ctype.h>

enum {
	TYPE_ERROR=1,
	OPTION_ERROR,
        MISSEXPR_ERROR,
	EXPR_ERROR,
     };

static int process(FILE* stream, char* expression){
  double res,d,p=0;
  int i,j;
  FILE* streamout=NULL;
  if (stream==stdin)
    streamout=stdout;
  else {
    streamout=fopen("./temp","w");
  }
  while(fscanf(stream,"%lf",&res)!=EOF ){
    for (i=0;i<strlen(expression);i++){
      switch(expression[i])
      {
      case '/':
      case ',':
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
      case 'e':
        break;
      case '*':
        if(isdigit(expression[i+1]))
          p= atoi(expression+i+1);
        if(expression[i+1]=='e'){
          p=2.718282;
          i++;
        }
        if((expression[i+1]=='p') && (expression[i+2]=='i')){
          p=3.141593;
          i=i+2;
        }
        res= res*p;
        break;
      case '%':
        p= atoi(expression+i+1);
        res= res/p;
        break;
      case '+':
        p= atoi(expression+i+1);
        res= res+p;
        break;
      case '-':
        p= atoi(expression+i+1);
        res= res-p;
        break;
      case '^':
        d=res;
        p= atoi(expression+i+1);
	for(j=1;j<p;j++){
          res=res*d;
        }
        break;
      case 's':
        if ((expression[i+1]=='i') && (expression[i+2]=='n')){
        res=sin(res);
        i=i+2;
        }
        if ((expression[i+1]=='q') && (expression[i+2]=='r') && (expression[i+3]=='t')){
        res=sqrt(abs(res));
        i=i+3;
        }
        break;
     case 'c':
        if ((expression[i+1]=='o') && (expression[i+2]=='s')){
        res=cos(res);
        i=i+2;
        }
        break;
     default:
        exit(EXIT_FAILURE);
        break;
      }
    }
    fprintf(streamout,"%lf\n",res);
  }
  if (stream!=stdin)
    fclose(streamout);
  return 1;
}

static int typeIsWrong(FILE* stream){				//this function tests if there is letters in the file.
  char c;
  while(fscanf(stream, "%c",&c)!=EOF){
    if (!isdigit(c) && !isspace(c) && !(c==46)) { 
    fprintf(stderr,"The type of the file is wrong.\n");
    fprintf(stderr,"the programm has detected an unexpected char : %c\n",c);
    return 1;
    }
  }
  rewind(stream);
  return 0;
}


int main(int argc,char *argv[]){
FILE* stream=NULL;
int opt;

while((opt=getopt(argc,argv,"iIMmlh"))!=-1){
    switch(opt) {
      case 'h':
        system("/usr/bin/man numprocess");
        return 0;
      break;

      default :				//option fail.
        fprintf(stderr, "Invalid option\n");
        return OPTION_ERROR;
      break;
    }
}
  if(argc==1){
    fprintf(stderr,"The expression is missing.\n");
  return MISSEXPR_ERROR;
  }
  if(argv[1][0]!='/'){
    fprintf(stderr,"The expression is wrong.\n");
    return EXPR_ERROR;
  }
  if(argc==(optind+1))    
    process(stdin,argv[optind]);
  else{
    if (!(stream=fopen(argv[optind+1],"r"))){
      perror("num-utils-ng"); 
      exit(EXIT_FAILURE);
    }
    if(typeIsWrong(stream)){
    fprintf(stderr, "The type of the file is wrong.");
    return TYPE_ERROR;
    }
    process(stream,argv[optind]);
    fclose(stream);
    remove(argv[optind+1]);
    rename("./temp",argv[optind+1]);
  }
  return 0;
}
