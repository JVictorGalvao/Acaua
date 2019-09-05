#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *listadecidades;
FILE *Listadecidades;

void bemvindo(){
    puts("BEM VINDO AO CONTROLADOR DE PLACAS FOTOVOLTAICAS");
}
char concatenarlink (char* id){
    
    char link [97] = "http://api.openweathermap.org/data/2.5/weather?id=";
    char apikey [] = "&appid=7d103cfe921d9a5bfcf551a90513f265";

    strcat(link,id);
    strcat(link, apikey);

    return printf("%s\n", link);
}

void abriraquivo(){
    listadecidades = fopen("city.list.json", "r");
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

char organizaBusca(char *buscaCidade){
    int i;
    // a-z 97-122 A-Z 65 - 90
    if(buscaCidade[0] >= 'a' && buscaCidade[0] <= 'z'){
        buscaCidade[0] -= 32;
        }
    return     printf("%s\n", buscaCidade);
}

/*char buscaNoArquivo(FILE *arquivo){
    char cidade[2000000];
    int i;
    for(i=0; i<10; i++){
        fscanf(listadecidades,"%s", &cidade[i]);
        printf("%s\n", cidade[i]);  
    }
}*/


int main (void)
{
    //Variáveis
    char id [8] = {"12354"};
    char buscaCidade [50], c;


    bemvindo();

    abriraquivo();

   // buscaNoArquivo(listadecidades);
    Listadecidades = fopen("Listadecidades.txt", "w");
   while(!feof(listadecidades)){
        fscanf(listadecidades, "%c", &c);
        fprintf(Listadecidades, "%c", c);
    }


    contalinhas(listadecidades);

   // scanf("%[^\n]s", buscaCidade);
    //organizaBusca(buscaCidade);
    

    //scanf("%s", id);

    fechararquivo();

    concatenarlink(id);


    return 0;
}
