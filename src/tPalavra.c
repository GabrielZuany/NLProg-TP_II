#include "../lib/tPalavra.h"

struct tPalavra{
    char palavra [50];
    int *pFrenquencia;
};

tPalavra** Inicializa_Array_Palavra(){
    tPalavra** pp_Palavras = NULL;
    pp_Palavras =  malloc(sizeof(tPalavra*));
    return pp_Palavras;
}

tPalavra* Inicializa_Palavra(int qtd_docs){
    tPalavra* palavra = malloc(sizeof(tPalavra));
    palavra->pFrenquencia = malloc(sizeof(palavra->pFrenquencia) * qtd_docs);
    return palavra;
}

tPalavra** LeTodosOsArquivosPalavra(FILE* fArquivo_caminho_noticias, tPalavra** pp_Palavras, int qtd_Arquivos){
    int i = 0;
    char linha[100000];
    for(i = 0; i < qtd_Arquivos; i++){
        fscanf(fArquivo_caminho_noticias, "%[^\n]", linha);
        fscanf(fArquivo_caminho_noticias, "%*c");
        
        FILE *fArquivo = Get_ArquivoNoticia(linha);
        pp_Palavras = LeArquivo(fArquivo, pp_Palavras);

        //falta armazenar a palavra na struct.
        //tratar docs

        fclose(fArquivo);
    }
    return pp_Palavras;
}

FILE* Get_ArquivoNoticia(char caminho[]){
    char aux[1000];
    char diretorio[10000];
    
    sscanf(caminho, "%s", aux);
    sprintf(diretorio, "datasets/tiny/%s", aux);
    
    ConfereEntradaValida(diretorio);
    FILE *fArquivo = fopen(diretorio, "r");
    return fArquivo;
}

tPalavra** LeArquivo(FILE* fArquivo, tPalavra **pp_Palavras){
    char palavra[50];
    
    while(fscanf(fArquivo,"%s", palavra) == 1){
        printf("%s ", palavra);
        


        
        ResetaString(palavra);
    }
    return pp_Palavras;
}

void ResetaString(char str[]){
    int i = 0;
    for(i=0; i<strlen(str); i++){
        str[i] = '\0';
    }
}