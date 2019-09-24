#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
    char str[30] ;  //Random data we want to send
    FILE *file;
    file = fopen("/dev/ttyUSB0","r");  //Opening device file
    int i = 0;
    float dados [100];
    char final[30];
    for(i=0; i < 100; i++)
    {
        
        fscanf(file,"%f", *str ); //Writing to the fileR
        dados[i]=strtod(const char *str,char **final)
        //printf("%f\n", str);
     
    }
     for(i=0;i<100;i++)
     {
         printf("%f\n",dados[i]);
     }   
    fclose(file);
}