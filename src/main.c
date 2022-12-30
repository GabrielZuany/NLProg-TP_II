#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/uteis.h"
#include "../lib/tPalavra.h"


int main(int argc, char *argv[]){
    printf("a\n");
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

    TEMP_ImprimeStructPalavras(pp_Palavras);
    //cria dicionarioclear
    
    /*
    inicializa pp_palavras, quantidadeDocumentos;
    pp_palavras = LeDIcionarioPalavras(fArquivo_caminho_noticias, pp_palavras);
    fclose(fArquivo_caminho_noticias);
    */


    //ArmazenaDadosEmBinario(saida, documentos, palavras); *******
    //free(pp_Palavras);
    printf("\n\nprograma encerrado com sucesso!\n");
    return 0;
}


// 1. liberar o dicionario
// 2. TF-IDF
// 3. struct documentos
// 4. Arquivo binario
// 5. Funcao get set: Definir parametros e retorno void.