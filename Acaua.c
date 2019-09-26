#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *id;
char linkdacidade [100];
float dados [100];
FILE *tensao;
int num = 0;

int TiraBarraN(char *v){
    int i;
    for(i=0;v[i]!='\0';i++)
    {
        if(v[i]=='\n')
            v[i]='\0';
    }
}

void BuscaCidade(){
    FILE *fp;
    char cidade[101], linha[2001];
    char *tok;
    int c,t=0;
    char str1[100]="http://api.openweathermap.org/data/2.5/weather?id=";
    char str2[100]="&appid=7d103cfe921d9a5bfcf551a90513f265";
    char *id;

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
        strcat(str1,id);
        strcat(str1,str2);
        //printf("%s\n",id);
        strcpy(linkdacidade,str1);
        puts("Cidade encontrada.");
    }
    else
        puts("Cidade nao encontrada.");
    fclose(fp);
}

void ExibeMenu(){
    printf("----------------------Menu----------------------\n"
        "\t1 - Buscar cidade\n"
        "\t2 - Exibir link\n"
        "\t3 - Abrir arquivo com tensoes\n"
        "\t4 - Opcoes com a tensao\n"
        "\t5 - Sair\n");
}
void ExibeMenu1(){
    printf("\t\t1 - Media total\n"
        "\t\t2 - Media por hora\n"
        "\t\t3 - Soma total\n"
        "\t\t4 - Voltar\n");
}

void bemvindo(){
    puts("Bem-vindo ao programa");
}

void obtertensao(){
    char ch;
    char linha [100];
    int c, i;
    char *tok;
    tensao = fopen("tensao.txt", "r");
    if (tensao == NULL){
        puts("Houve um erro ao abrir o arquivo");
    }else{
        puts("Arquivo aberto com sucesso");
    }
    num = 0;
    while( (ch=fgetc(tensao))!= EOF ){
        if(ch == '\n')
            num++;
    }
    rewind(tensao);
    i=0;
    while(1){
        fgets(linha, 2001, tensao);
        if (feof(tensao)){
            break;
        }
        c = 0;
        tok = strtok(linha, ">"); 
        while (c != 1){
            tok = strtok(NULL, ">");
            c++;
            dados[i] = strtod(tok, NULL);
            i++;
        }
    }
    fclose (tensao);
}

void opcaotensao(){
    int opcao1;
    int i, intervalo;
    float media, soma=0;
    while(1){
        printf("Digite uma opcao: ");
        scanf("%d%*c", &opcao1);

        if (opcao1 == 4){
            break;
        }   
        switch (opcao1){
        case 1:
            soma =0;
            for (i=0; i<num; i++){
                soma += dados[i];
            }
            media = soma/num;
            printf("%.2f V\n", media);
            break;
        case 2:
            printf("Dados de qual intervalo de hora? ");
            scanf("%d", &intervalo);
            if (intervalo == 1){
                soma = 0;
                for(i=0;i<6;i++){
                    soma += dados[i];
                }
                media = soma/6;
                printf("%.2f V\n", media);
            }
            if (intervalo == 2){
                soma = 0;
                for(i=6;i<12;i++){
                    soma += dados[i];
                }
                media = soma/6;
                printf("%.2f V\n", media);
            }
            if (intervalo != 1 && intervalo !=2){
                puts("Intervalo invalido");
            }
            break;
        case 3:
            soma = 0;
            for (i=0; i<num; i++){
                soma += dados[i];
            }
            printf("%.2f V\n", soma);
            break;
        default:
            puts("Opcao Invalida");
        break;
        }
    }       
}

int main (void){
    
    int opcao, opcao1;

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
            puts(linkdacidade);
            break;
        case 3:
            obtertensao(tensao);
            break;
        case 4:
            ExibeMenu1();
            opcaotensao();
            break;
        default:
            puts("Opcao invalida");
            break;
        }
    }   
    return 0;
}