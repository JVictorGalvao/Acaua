#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void){

    FILE *listadecidades;
    FILE *listaatualizada;
    char caracter;
    char linha[30];
    listaatualizada = fopen("cidades.txt", "w");
    listadecidades = fopen("city.list.json", "r");
    if (listadecidades == NULL){
        puts("Houve um erro ao abrir o arquivo");
    }else{
        puts("Arquivo aberto com sucesso");
    }
    if (listaatualizada == NULL){
        puts("Houve um erro ao abrir o arquivo");
    }else{
        puts("Arquivo aberto com sucesso");
    }
    
    while((caracter = fgetc(listadecidades)) != EOF){
        if(caracter >= 'A' && caracter <= 'Z' || caracter >= 'a' && caracter <='z'|| caracter == '\n'|| caracter >= '0' && caracter <= '9' || caracter == ' ' || caracter == ':')
        fprintf(listaatualizada, "%c", caracter);
    }

    return 0;
}