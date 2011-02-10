#include <stdio.h>
#include <stdlib.h>

int main(int arg,char *argv[])
{
    FILE *fp;
    printf("Calculer une moyenne\n");
    float nombre=0,moyenne=0;
    int count=0;
    if(argv[1]==NULL)                       //cas où il n'y a pas d'argument
    {

        printf("Entrez le nombre de chiffre\n");
        scanf("%d",&count);
        int i;
        printf("Entrez ces %d chiffre\n",count);
        for(i=0;i<count;i++)
        {
            scanf("%f",&nombre);
            moyenne+=nombre;
        }
        moyenne=moyenne/((float)count);
        printf("La moyenne est egale a %f\n",moyenne);
    }

    else                                //cac où il y a un argument
    {

        if((fp=fopen(argv[1],"r")) != NULL)
        {
            while(getc(fp)!=EOF)
            {

                fscanf(fp,"%f",&nombre);
                moyenne+=nombre;
                count++;
            }
            if(moyenne==0)
                printf("Les donnees du fichier sont incorrectes ou le fichier est vide\n");
            else
            {
                moyenne=moyenne/((float)count);
                printf("La moyenne est egale a %f\n",moyenne);
                fclose(fp);
            }
        }
        else
        {
            printf("impossible d'ouvrir le fichier\n");
        }
    }
    return 0;
}
