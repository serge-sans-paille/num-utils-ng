#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int typeIsWrong(FILE* stream);
int fileIsEmpty(FILE* stream);
int process(FILE*, char*);

int main(int argc,char *argv[]){
FILE* stream=NULL;
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
  double res;
  int i=0,p;
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
        break;
      case '*':
        p= (int) atoi(expression+i+1);
        res= res*(double)p;
        break;
      case '%':
        p= (int) atoi(expression+i+1);
        res= res/(double)p;
        break;
      case '+':
        p= (int) atoi(expression+i+1);
        res= res+(double)p;
        break;
      case '-':
        p= (int) atoi(expression+i+1);
        res= res-(double)p;
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
