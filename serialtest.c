#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    char* str[] = {"http://api.openweathermap.org/data/2.5/weather?id=3397277&appid=7d103cfe921d9a5bfcf551a90513f265"};  //Random data we want to send
    FILE *file;
    file = fopen("/dev/ttyUSB0","w");  //Opening device file
    int i = 0;

    for(i = 0 ; i < 1 ; i++)
    {
        fprintf(file,"%s",str[i]); //Writing to the file
        sleep(1);
    }
    fclose(file);
}