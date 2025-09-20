#include <stdio.h>
#include <string.h>

int mais (void) {
    int n = 0; // linha corrente
    int achou = 0; // se achou a subcadeia | variavel flag 
    char entrada[121]; // nome do arquivo de entrada
    char subcadeia[121]; 
    char linha[121]; // armazena cada linha do arquivo
    FILE* fp; // ponteiro do arquivo de entrada

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%120s", entrada);
    printf("Digite a subcadeia: ");
    scanf("%120s", subcadeia);

    // abrindo arquivos para a leitura
    fp = fopen(entrada, "rt");
    if (fp == NULL) {
        printf("Não foi possivel abrir.\n");
        return 1;
    }
     
    // lendo linha a linha 
    while (fgets(linha, 121, fp) != NULL) { // fgets le a linha do ficheiro ou input padrao
        n++;
        if(strstr(linha, subcadeia) != NULL) { // strstr localiza a primeira ocorrencia de uma substring
            achou = 1; // flag 1
            break;
        }
    }

    fclose(fp); // fechando arquivo 

    if(achou) { // exibindo saída
        printf("Achou na linha %d.\n", n);
    } else {
        printf("Não achou.");
    }
    return 0;
}