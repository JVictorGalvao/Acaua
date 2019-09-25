#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
    char *str[30] ;  //Random data we want to send
    FILE *file;
    file = fopen("/dev/ttyUSB0","r");  //Opening device file
    int i = 0;

    while(i<10){
        char ar[5];
        int r = fread(ar, sizeof("amendoin"), 5, file);
        printf("%s", ar);
        if (r == 5){
            break;
        }
        i++;
    }
       // fscanf(file,"%s", str[i] ); //Writing to the fileR
        //rintf("%s\n", *str);
    fclose(file);
}test