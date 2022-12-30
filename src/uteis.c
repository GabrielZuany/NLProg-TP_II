#include "../lib/uteis.h"

static Vetor_Get_or_Set_fn dispatch_table_Get_Or_Set[256];


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
    Get_Or_Set_Valor('d', "set", qtd_linhas);
    return qtd_linhas;

}

void ConfereEntradaValida(char entrada[]){
    FILE *fteste = fopen(entrada, "r");
    if(!(fteste)){
        printf("ERRO: diretorio inexistente\n");
        printf("ex:  ./indice data/train.txt  indice.bin\n");
    }
    fclose(fteste);
}


//----------------dispatch_table_Get_Or_Set -------------


int Get_Set_QuantidadePalavras(char acao[], int valor){
    static int total_palavras = 0;
    
    if(strcmp(acao, "set") == 0){
        total_palavras = valor;
    }else if(strcmp(acao, "get") == 0){
        total_palavras = total_palavras;
    }else{
        printf("ERRO: '%s' eh um comando nao existente.\n=> Comandos validos: 'get', 'set'\n", acao);
        exit(EXIT_FAILURE);
    }
    return total_palavras;
}

int Get_Set_QuantidadeDocumento(char acao[], int valor){
    static int total_Documentos = 0;

    if(strcmp(acao, "set") == 0){
        total_Documentos = valor;
    }else if(strcmp(acao, "get") == 0){
        total_Documentos = total_Documentos;
    }else{
        printf("ERRO: '%s' eh um comando nao existente.\n=> Comandos validos: 'get', 'set'\n", acao);
        exit(EXIT_FAILURE);
    }
    return total_Documentos;
}

void Dispatch_table_Get_Set_inicializa(){
    // apenas para sabermos quais funcoes nao foram definidas ainda
    for (int i = 0; i < 256; i++){
        dispatch_table_Get_Or_Set[i] = NULL;

    }   
    // TODO: adicionar funcoes...
    dispatch_table_Get_Or_Set['d'] = Get_Set_QuantidadeDocumento; //d = documento
    dispatch_table_Get_Or_Set['p'] = Get_Set_QuantidadePalavras; // p = palavra
}

static void Dispatch_table_executa(char dado, char acao[], int valor){
    int idx = (int)dado;

    if (dispatch_table_Get_Or_Set[idx] != NULL)
        dispatch_table_Get_Or_Set[idx](acao, valor);
    else
        printf(">> ERRO: A funcao '%c' nao foi definida ainda.\n", dado);
}

int Get_Or_Set_Valor(char dado, char acao[], int valor_registrar){   
    //Dispatch_table_executa('p', 'set', 10); => registra o numero de palavras
    //Dispatch_table_executa('d', 'get', qlq num mas opte por passar NULL); => pega o nunumero de documentos    
    Dispatch_table_executa(dado, acao, valor_registrar);
}

