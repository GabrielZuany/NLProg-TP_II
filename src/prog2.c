#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/uteis.h"
#include "../lib/tPalavra.h"
#include "../lib/tDocumento.h"

int main(int argc, char *argv[]){
    printf("entramos prog2");
    // input: ./prog2 indice.bin K
    //prepara e confere os diretorios
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        printf("ex:  ./prog2 arq.bin K\n");
        exit(0);
    }
    ConfereEntradaValida(argv[1], "rb");
    char entrada[100] = "";
    int k = atoi(argv[2]);
    strcpy(entrada, argv[1]);   

    //trantando a dispatch table
    Dispatch_table_Get_Set_inicializa();
    Get_Or_Set_Valor('d', "set", 0);
    Get_Or_Set_Valor('p', "set", 0);

    //-------LEITURA
    //--LeDocumentos
    FILE *fBin = NULL;
    fBin = fopen(entrada, "rb");
    tDocumento **pp_Docs = NULL;
    pp_Docs = LeDocsBinario(fBin);

    //--LePalavras
    tPalavra **pp_Palavras = NULL;
    pp_Palavras = LeDicionarioBinario(fBin);
    fclose(fBin);


    //impressao
    //Teste_ImprimeDocumentos(pp_Docs);
    //Teste_ImprimePalavras(pp_Palavras);

    LiberaDocs(pp_Docs);
    LiberaPalavras(pp_Palavras);
    printf("programa 2 encerrado com sucesso!\n");
    return 0;
}


/*
1. salvar as structs .....................................ok
x. switch opcao...........................................
2. relatorio documento....................................
3. relatorio dicionario...................................
4. Buscar ................................................
5. Classificar............................................

pp_Copia_pp_docs = CriaCopiaDocumentos(pp_Docs);
ImprimeDocumentos(pp_Copia_pp_docs);
LiberaDocumentos(pp_Copia_pp_docs);


Relatório de Documentos: Exibe os 10 documentos mais longos e os 10 mais curtos com o número de palavras e as
 respectivas classes. As listas devem ser ordenadas, a primeira do maior para o menor e a segunda do menor para o
  maior. A ordenação deve ser feita ao selecionar a opção usando a função qsort.

tDocumento **pp_docs
copia_pp_docs = pp_docs

qsort(copia_pp_docs, qtd_palavras_no_doc)

*/
