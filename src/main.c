#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/uteis.h"
#include "../lib/tPalavra.h"


int main(int argc, char *argv[]){
    //prepara e confere os diretorios
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        printf("ex:  ./indice data/train.txt  indice.bin\n");
        exit(0);
    }
    ConfereEntradaValida(argv[1]);
    char entrada[100] = "";
    char saida[100] = "";
    strcpy(entrada, argv[1]);    
    strcpy(saida, argv[2]);

    //trantando a dispatch table
    Dispatch_table_Get_Set_inicializa();
    Get_Or_Set_Valor('d', "set", 0);
    Get_Or_Set_Valor('p', "set", 0);
    
    //le quantidade de documentos
    FILE *fArquivo_caminho_noticias = fopen(entrada, "r");
    int qtd_Arquivos = 1;
    //Get_Or_Set_Valor('d', "set", 1);
    qtd_Arquivos = LeQuantidadeDeArquivos(fArquivo_caminho_noticias);
    Get_Or_Set_Valor('d', "set", qtd_Arquivos);
    fclose(fArquivo_caminho_noticias);
    
    
    //inicializa dicionario
    fArquivo_caminho_noticias = fopen(entrada, "r");
    tPalavra **pp_Palavras = NULL;
    pp_Palavras = Inicializa_Array_Palavra();
    pp_Palavras = LeTodosOsArquivosPalavra(fArquivo_caminho_noticias, pp_Palavras, qtd_Arquivos);
    fclose(fArquivo_caminho_noticias);

    printf("\n");
    //TEMP_ImprimeStructPalavras(pp_Palavras);
    

    Idx_Docs(pp_Palavras);

    //ArmazenaDadosEmBinario(saida, documentos, palavras);

    LiberaPalavras(pp_Palavras);
    printf("programa encerrado com sucesso!\n");
    return 0;
}


// 1. liberar o dicionario     ok
// 2. TF-IDF                   ok
// 3. struct documentos
// 4. Arquivo binario


// Alterações Gabriel.
// -> tPalavra.c linha 236 à 261
// -> uteis.c linha 70 à 88