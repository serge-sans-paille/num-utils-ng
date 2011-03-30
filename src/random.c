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
#include <string.h>
#include <time.h>

enum {ERROR_1=1,ERROR_2,ERROR_3,ERROR_4};

int numberRandom(FILE* stream, char* expression){
  int number1,number2;
  double numberL=0.,numberH=0, numberStep=0.;
  int integerPortion;
  double decimalPortion;
  int i,count=0,mode;
  char *token;
  char *savestr;
  char *str;
  char **tab=NULL;
  double *randomNumber=NULL;

  for (i=0;i<strlen(expression);i++){
    switch(expression[i])
    {
      case '/':
        expression[i]=',';
	break;
      case '.':
        mode=2;
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
        return EXIT_FAILURE;
    }
  }
  if(!(tab =(char **)calloc(count+1,sizeof(char*)))){
    perror("memory allocation");
    exit(EXIT_FAILURE);
  }
  
  for (i=0,str=expression;;i++,str=NULL) {
    token=strtok_r(str,",", &savestr);
    if (token == NULL)
      break;
    *(tab+i)=token;
  }
  
  if(!(randomNumber=(double *)calloc(count+1,sizeof(double)))){
    perror("memory allocation");
    exit(EXIT_FAILURE);
  }  

  srand(time(NULL));

  for(i=0;i<=count;i++){
    
    if(strstr(*(tab+i),"i")!=NULL){
      
      /* a decimal number between numberL and number with a step of numberStep */
      sscanf(*(tab+i),"%lf:%lfi%lf",&numberL,&numberH,&numberStep);
      integerPortion=(int)numberStep;
      decimalPortion=numberStep-(double)integerPortion;
      int count2=0;
      double numberL2 =numberL;
      while(numberL2<numberH){
        numberL2+=numberStep;
        count2++;
      }
      *(randomNumber+i)=numberL+numberStep*(rand()%(count2));
    }

    /* an integer between number1 and number2 */
    else{
      sscanf(*(tab+i),"%d:%d",&number1,&number2);
      *(randomNumber+i)=rand()%(number2+1-number1)+number1;
    }
  }
  printf( "%lf\n",randomNumber[rand()%(count+1)]);
  
  free(tab);
  free(randomNumber);
  return EXIT_SUCCESS;
}


int main(int argc,char *argv[]){
  char *arg;
  if((argc>1) && (argv[optind][0]=='/')){
    arg=argv[optind];
  }
  else{
    char arg2[]="/1:100/";
    arg=arg2;
  }
  numberRandom(stdin,arg);
  fclose(stdin);
  return EXIT_SUCCESS;
}
