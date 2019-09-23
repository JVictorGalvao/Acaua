#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

FILE *listadecidades;

void bemvindo(){
    puts("BEM VINDO AO CONTROLADOR DE PLACAS FOTOVOLTAICAS");
}
char concatenarlink (char *id){
    
    char link [97] = "http://api.openweathermap.org/data/2.5/weather?id=";
    char apikey [] = "&appid=7d103cfe921d9a5bfcf551a90513f265";

    strcat(link,id);
    strcat(link, apikey);

    return printf("%s\n", link);
}

void abriraquivo(){
    listadecidades = fopen("Listadecidades.txt", "r");
    if (listadecidades == NULL){
        puts("Houve um erro ao abrir o arquivo");
    }else{
        puts("Arquivo aberto com sucesso");
    }
}
int contalinhas(FILE *arquivo){
    char ch;
    int num = 0;
    while( (ch=fgetc(arquivo))!= EOF ){
        if(ch == '\n')
            num++;
    }
    return printf("%d\n", num+1);
}
void fechararquivo(){
    fclose (listadecidades);
}


int main (void)
{
    //Variáveis
    char compara[30];
    char linhas[100];
    typedef struct {
        char id [8];
        char cidade[30];
        char pais[3];
    } tCidade;

    tCidade cidade = {"3397277","Joao Pessoa", "BR"};
    

    bemvindo();

    abriraquivo();

    contalinhas(listadecidades);

    listadecidades = fopen("Listadecidades.txt", "r");

    while(fgets(linhas, 100, listadecidades) != NULL){
        printf("%s\n", linhas);
    }
    
    
   // scanf("%s", id);

    fechararquivo();

    concatenarlink(cidade.id);
    
    return 0;
}