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
#include <ctype.h>

static int skipWord(FILE* stream){
char c='a';
if (stream==stdin)
  fprintf(stderr,"This is not a number!\n");
while(!isdigit(c) && !isspace(c) && !(c==46) && !(c==45)){
  if(fscanf(stream, "%c",&c)!=1){
    perror("num-utils-ng"); 
    return EXIT_FAILURE;
  }
}
return 0;
}

static int interval(FILE* stream){ 	
  double oldnumber,newnumber,interval;
  int test;
  if (fscanf(stream,"%lf",&oldnumber)!=1){
    perror("num-utils-ng");
    exit(EXIT_FAILURE);  
  }
  while((test=fscanf(stream,"%lf",&newnumber))!=EOF){
    if(test==0)
      skipWord(stream);
    else{
      interval=newnumber-oldnumber;
      fprintf(stdout, "%lf\n", interval);
      oldnumber=newnumber;
    }
  }
  return 0;
}

int main(int argc,char *argv[]){
  int opt;
  FILE* stream = stdin;
  while((opt=getopt(argc,argv,"iIMmlh"))!=-1){
    switch(opt) {
      case 'h':
        if (execlp("man","man","numinterval",NULL)==-1){
          perror("num-utils-ng"); 
          exit(EXIT_FAILURE);
        }
        return 0;
      break;

      default :				//option fail.
        fprintf(stderr, "Invalid option\n");
        return 1;
      break;
    }
  }
  if(argc>optind){
    if (!(stream = fopen(argv[optind], "r"))){
      perror("num-utils-ng"); 
      return EXIT_FAILURE;
    }
  }
  interval(stream);
  if(argc>optind){
    if (fclose(stream)!=0){
      perror("num-utils-ng"); 
      return EXIT_FAILURE;
    }
  }
  return 0;
}
