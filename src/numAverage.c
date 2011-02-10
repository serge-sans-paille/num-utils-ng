#include <stdio.h>
#include <stdlib.h>

int main(int arg,char *argv[])
{
    FILE *fp;
    float number=0,average=0;
    int count=0;
    if(argv[1]==NULL)                       //not argument
    {

        printf("How many numbers ?\n");
        scanf("%d",&count);
        int i;
        printf("Enter these %d numbers\n",count);
        for(i=0;i<count;i++)
        {
            scanf("%f",&number);
            average+=number;
        }
        average=average/((float)count);
        printf("The average is %f\n",average);
    }

    else                                //an only argument
    {

        if((fp=fopen(argv[1],"r")) != NULL)
        {
            while(getc(fp)!=EOF)
            {

                fscanf(fp,"%f",&number);
                average+=number;
                count++;
            }
            if(average==0)
                printf("The file is empty or corrrupted\n");
            else
            {
                average=average/((float)count);
                printf("The average is %f\n",average);
                fclose(fp);
            }
        }
        else
        {
            printf("The file doesn't exist in this directory\n");
        }
    }
    return 0;
}
