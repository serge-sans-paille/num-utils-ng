#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int typeIsWrong(FILE* stream);
int fileIsEmpty(FILE* stream);
int process(FILE*, char*);

int main(int argc,char *argv[]){
FILE* stream=NULL;
  if(argv[1][0]!='/')
    fprintf(stderr,"The expression is wrong\n");
    return 2;
  if(argc==2)    
    process(stdin,argv[1]);
  else{
    stream=fopen(argv[2],"r");
    if (stream==NULL){
    fprintf(stderr,"the file can't be opened, see \"errno\" for more informations");
    return 1;
    }
    process(stream,argv[1]);
    fclose(stream);
    remove(argv[2]);
    rename("./temp",argv[2]);
  }
  return 0;
}


int process(FILE* stream, char* expression){
  double res,d,p;
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
        return 0;
      }
    }
    fprintf(streamout,"%lf\n",res);
  }
  if (stream!=stdin)
    fclose(streamout);
  return 1;
}

int fileIsEmpty(FILE* stream){				//this function tests if the file is empty.
  long pos;
  fseek(stream, 0L, SEEK_END);
  pos=ftell(stream);
  rewind(stream);
  if (pos==0){
    fprintf(stderr,"The file is empty\n");
    return 1;
  }
  else 
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
