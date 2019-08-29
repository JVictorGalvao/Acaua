#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bemvindo(){
    puts("BEM VINDO AO CONTROLADOR DE PLACAS FOTOVOLTAICAS");
}
char concatenarlink (char* id){
    
    char link [96] = "http://api.openweathermap.org/data/2.5/weather?id=";
    char apikey [] = "&appid=7d103cfe921d9a5bfcf551a90513f265";

    strcat(link,id);
    strcat(link, apikey);

    return printf("%s\n", link);
}


int main (void)
{
    //Variáveis
    char id [8];
    
    bemvindo();

    scanf("%s", id);

    concatenarlink(id);


    return 0;
}
