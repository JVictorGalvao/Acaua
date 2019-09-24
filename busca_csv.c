#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


int TiraBarraN(char *v)
{
    int i;
    for(i=0;v[i]!='\0';i++)
    {
        if(v[i]=='\n')
            v[i]='\0';
    }
}
int main(void){
    FILE *fp;
    char cidade[101], linha[2001];
    char *tok;
    int c,t=0;
    char *id;
    char str1[100]="http://api.openweathermap.org/data/2.5/weather?id=";
    char str2[100]="&appid=7d103cfe921d9a5bfcf551a90513f265";
    char *link [101];
    fp = fopen("citylist.csv", "r");
    if (!fp){
        puts("Erro ao abrir");
        return 1;
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
        printf("%s\n",id);
        puts(str1);
        *link = str1;
        printf("%s\n", *link);
    }
    else
        puts("Cidade nao encontrada");
    
    fclose(fp);

    
    FILE *file;
    file = fopen("/dev/ttyUSB0","w");  //Opening device file
    int i = 0;

    for(i = 0 ; i < 1 ; i++)
    {
        sleep(1);
        fprintf(file,"%s",link[i]); //Writing to the file
        
    }
    fclose(file);


    return 0;
}