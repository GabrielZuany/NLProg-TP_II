#include "lib/lib.h"


int main(int argc, char *argv[]){
    //prepara e confere os diretorios
    printf("entramos prog1\n");
    if(argc <= 2){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        printf("ex:  ./indice data/train.txt  indice.bin\n");
        exit(0);
    }

    ConfereEntradaValida(argv[1], "r");
    char entrada[100] = "";
    char saida[100] = "";
    strcpy(entrada, argv[1]);    
    strcpy(saida, argv[2]);

    //trantando a dispatch table
    Dispatch_table_Get_Set_inicializa();
    Get_Or_Set_Valor('d', "set", 0);
    Get_Or_Set_Valor('p', "set", 0);
    Get_Or_Set_Valor('g', "set", 0);
    
    //le quantidade de documentos
    FILE *fArquivo_caminho_noticias = fopen(entrada, "r");
    int qtd_Arquivos = LeQuantidadeDeArquivos(fArquivo_caminho_noticias);
    Get_Or_Set_Valor('d', "set", qtd_Arquivos);
    fclose(fArquivo_caminho_noticias);
    
    
    //inicializa dicionario
    fArquivo_caminho_noticias = fopen(entrada, "r");
    tPalavra **pp_Palavras = NULL;
    pp_Palavras = Inicializa_Array_Palavra();
    pp_Palavras = LeTodosOsArquivosPalavra(fArquivo_caminho_noticias, pp_Palavras, qtd_Arquivos, entrada);
    fclose(fArquivo_caminho_noticias);
    OrganizaPalavrasPorIndice(pp_Palavras, Get_Or_Set_Valor('p', "get", null));

    //inicializa documentos
    tDocumento** pp_Docs = NULL;
    pp_Docs = Inicializa_Array_Docs(Get_Or_Set_Valor('d', "get", null));
    pp_Docs = RegistraPalavrasNosDocumentos(pp_Palavras, pp_Docs);

    //armazena em binario
    FILE *fBin = fopen(saida, "wb");
    if (fBin == NULL || fBin == NULL){
        printf("Erro! o documento binario nao foi inicializado com sucesso!\n");
        exit(EXIT_FAILURE);
    }

    ArmazenaDocumentosEmBinario(fBin, pp_Docs, qtd_Arquivos);
    fclose(fBin);

    fBin = fopen(saida, "ab");
    ArmazenaPalavrasEmBinario(fBin, pp_Palavras, Get_Or_Set_Valor('p', "get", null));
    fclose(fBin);

    fBin = fopen(saida, "ab");
    ArmazenaAuxiliaresEmBinario(fBin, Get_Or_Set_Valor('g', "get", null));
    fclose(fBin);
    
    //ImprimePalavras(pp_Palavras);
    //ImprimeDocumentos(pp_Docs);

    printf("------\n-> Qtd documentos: %d\n-> Qtd palavras diferentes: %d\n-------\n", Get_Or_Set_Valor('d', "get", null), Get_Or_Set_Valor('p', "get", null));

    //frees
    LiberaPalavras(pp_Palavras);
    LiberaDocs(pp_Docs);
    printf("programa encerrado com sucesso!\n");
    return 0;
}

