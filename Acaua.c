#include <stdio.h>
#include <stdlib.h>
#include <string.h>

            FILE *fp;
            char cidade[101], linha[2001];
            char *tok;
            int c,t=0;
            char *id;
            char *link [101];
            char apilink [97] = "http://api.openweathermap.org/data/2.5/weather?id=";
            char apikey [] = "&appid=7d103cfe921d9a5bfcf551a90513f265";

typedef struct {
    int id;
    char cidade [50];
    char pais [3];
} tCidade;

int TiraBarraN(char *v){
    int i;
    for(i=0;v[i]!='\0';i++)
    {
        if(v[i]=='\n')
            v[i]='\0';
    }
}

void BuscaCidade(){
    
    fp = fopen("citylist.csv", "r");
    if (!fp){
        puts("Erro ao abrir");
    }

    printf("Digite a Cidade: ");
    fgets(cidade,101,stdin);
    TiraBarraN(cidade);
    fgets(linha,2001,fp);
    while(1){
        fgets(linha,2001,fp);
        if(feof(fp))
            break;
        c=0;
        tok=strtok(linha,";");
        id=tok;
        while(c!=1){
            tok=strtok(NULL,";");
            c++;
        }
        if(strcmp(tok,cidade)==0){
            t++;
            break;
        }

    }
    if(t==1){
        printf("%s\n",id);
    }
    else
        puts("Cidade nao encontrada");
    
    fclose(fp);
}

void ExibeMenu(){
    printf("----------------------Menu----------------------\n"
        "\t1 - Buscar cidade\n"
        "\t2 - Concatenar link\n"
        "\t3 - Salvar cidade \n"
        "\t4 - Ver cidades salvas\n"
        "\t5 - Sair\n");
}

void bemvindo(){
    puts("Bem vindo ao programa");
}
char concatenarlink (char *id){
    
    strcat(apilink,id);
    strcat(apilink, apikey);

    return printf("%s\n", apilink);
}

/*void abriraquivo(){
    listadecidades = fopen("Listadecidades.txt", "r");
    if (listadecidades == NULL){
        puts("Houve um erro ao abrir o arquivo");
    }else{
        puts("Arquivo aberto com sucesso");
    }
}*/
/*int contalinhas(FILE *arquivo){
    char ch;
    int num = 0;
    while( (ch=fgetc(arquivo))!= EOF ){
        if(ch == '\n')
            num++;
    }
    return printf("%d\n", num+1);
}*/
/*void fechararquivo(){
    fclose (listadecidades);
}*/


int main (void){

    int opcao;

    while(1){
        bemvindo();
        ExibeMenu();
        printf("Digite uma opcao: ");
        scanf("%d%*c", &opcao);

        if (opcao == 5){
            break;
        }

        switch (opcao){
        case 1:
            BuscaCidade();
            break;
        case 2:
            concatenarlink(id);
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            puts("Opcao invalida");
            break;
        }

    }
    
    return 0;
}