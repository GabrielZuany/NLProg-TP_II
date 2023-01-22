#include "../lib/lib.h"

int main(int argc, char *argv[]){
    printf("entramos prog2\n");
    // input: ./prog2 indice.bin K
    //prepara e confere os diretorios
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        printf("ex:  ./prog2 arq.bin K\n");
        exit(0);
    }
    
    ConfereProg1FoiRodado(argv[1], "rb");
    char entrada[100] = "";
    int k = atoi(argv[2]);
    strcpy(entrada, argv[1]);   

    //trantando a dispatch table
    Dispatch_table_Get_Set_inicializa();
    Get_Or_Set_Valor('d', "set", 0);
    Get_Or_Set_Valor('p', "set", 0);
    Get_Or_Set_Valor('g', "set", 0);

    //-------LEITURA
    //--LeDocumentos
    FILE *fBin = NULL;
    fBin = fopen(entrada, "rb");
    tDocumento **pp_Docs = NULL;
    pp_Docs = LeDocsBinario(fBin);

    //--LePalavras
    tPalavra **pp_Palavras = NULL;
    pp_Palavras = LeDicionarioBinario(fBin);

    //--LeAuxiliares;
    LeAuxiliaresBinario(fBin);
    fclose(fBin);

    //impressao
    //Teste_ImprimeDocumentos(pp_Docs);
    //Teste_ImprimePalavras(pp_Palavras);
    

    int opcao = 0;    
    do{
        ExibeMenu();
        scanf("%d",&opcao);
        scanf("%*c");
        ExecutaOpcaoUsuario(pp_Docs, pp_Palavras, opcao, k);
    }while(opcao != 0);

    //testes
    //printf("qtd generos: %d\n", Get_Or_Set_Valor('g', "get", null));
    
    //liberacao
    LiberaDocs(pp_Docs);
    LiberaPalavras(pp_Palavras);
    printf("k: %d\n", k);
    printf("programa 2 encerrado com sucesso!\n");
    return 0;
}


/*
1. salvar as structs .....................................ok
x. switch opcao...........................................ok
2. relatorio documento....................................ok
3. relatorio dicionario...................................ok
4. Buscar ................................................ok
5. Classificar............................................ok
    5.1 Registrar doc.....................................ok
    5.2 Calcular cos......................................ok
    5.3 Retornar tipo noticia.............................ok
6. Verificar se saida faz sentido.........................
7. free no classificador..................................

OBS: Trocar nome da Teste_ImprimeDocumentos(tDocumento** pp_Docs)
*/
