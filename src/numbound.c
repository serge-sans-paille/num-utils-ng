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
#include <ctype.h>


enum {TYPE_ERROR=1,OPTION_ERROR,WRONG_FILE,CLOSE_ERROR};

static double bound(FILE* stream, int mode){		//this function calculates the upper or lower bound from a file or stdin depending on the argument
	double lowerBound=0.;
	double upperBound=0.;
	double number=0.;
	if(!feof(stream)){
		if(fscanf(stream,"%lf",&number)!=EOF);
		lowerBound=number;
		upperBound=number;
	}		
	while(!feof(stream)){
		if (number>upperBound)
			upperBound=number;
		if (number<lowerBound)
			lowerBound=number;
		if(fscanf(stream,"%lf",&number)!=EOF);
	}
	if (mode==1)
		return lowerBound;
	else
		return upperBound;			
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
  FILE *stream=stdin;
  int optch;
  int m=0;
  double res;

  while((optch=getopt(argc,argv,"lh"))!=-1){
    switch(optch){
      case 'l':			//option "-l" (the lower bound number)
        m=1;
      break;
      
      case 'h':
        if (system("/usr/bin/man numaverage")!=0){
          perror("num-utils-ng"); 
          exit(EXIT_FAILURE);
        }
        return 0;
      break;

      default :		  	//option fail.
        perror("invalid option\n");
        return OPTION_ERROR;
      break;
    }
  }
  if (argc>optind){
    if (!(stream=fopen(argv[optind], "r"))){
      perror("num-utils-ng");
      return WRONG_FILE;
    }
    if (typeIsWrong(stream))
      return TYPE_ERROR;
  }

  res=bound(stream,m);

  if (argc>1){
    if (fclose(stream)!=0){
      perror("num-utils-ng");
      return CLOSE_ERROR;
    }
  }

  printf("result : %lf\n",res);
  return 0;			
}
