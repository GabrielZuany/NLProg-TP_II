#include "../lib/uteis.h"

int LeQuantidadeDeArquivos(FILE* fArquivo_caminho_noticias){
    if(fArquivo_caminho_noticias == NULL){
        printf("Arquivo vazio! Encerrando execucao.\n");
        exit(0);
    }
    
    char* linha = NULL;
    int qtd_linhas = 0;
    size_t len = 0;
    ssize_t read;
    
    while((read = getline(&linha, &len, fArquivo_caminho_noticias)) != -1){
        qtd_linhas+=1;
    }
    if(linha){
        free(linha);
    }
    return qtd_linhas;
}

//
void ConfereEntradaValida(char entrada[]){
    FILE *fteste = fopen(entrada, "r");
    if(!(fteste)){
        printf("ERRO: diretorio inexistente\n");
        printf("ex:  ./indice data/train.txt  indice.bin\n");
    }
    fclose(fteste);
}
