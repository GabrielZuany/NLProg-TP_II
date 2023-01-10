#include "../lib/lib.h"

static Vetor_Get_or_Set_fn dispatch_table_Get_Or_Set[256];



//--------opcao usuario
void ExibeMenu(){
    printf("\n\n|====================== NL PROG ======================|\n\n");
    printf("[0] Sair\n[1] Buscar\n[2] Classificar\n[3] Relatorio dicionario\n[4] Relatorio documentos\n");
    printf("[5] Imprime dicionario\n[6] Imprime documentos\n------\n>>> ");
}

void ExecutaOpcaoUsuario(tDocumento **pp_Docs, tPalavra **pp_Palavras, int opcao){
    
    switch (opcao){
    case 0:
        //sair
        break;
    case 1:
        //Buscador
        break;
    case 2:
        //Classificador
        break;
    case 3:
        RelatorioPalavra(pp_Palavras, pp_Docs);
        break;
    case 4:
        RelatorioDocumento(pp_Docs);
        break;
    case 5:
        Teste_ImprimePalavras(pp_Palavras);
        break;
    case 6:
        Teste_ImprimeDocumentos(pp_Docs);
        break;
    default:
        printf("opcao invalida!\n");
        break;
    }    
}

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

void ConfereEntradaValida(char entrada[], char modo[]){
    FILE *fteste = fopen(entrada, modo);
    if(!(fteste)){
        printf("\nERRO: nao foi possivel abrir o arquivo\n");
        printf("programa 1) ex:  ./exe1 data/train.txt  indice.bin\n");
        printf("programa 2) ex: ./exe2 ArquivosBinarios/indice.bin K\n\n\n");
        exit(EXIT_FAILURE);
    }
    fclose(fteste);
}

void ConfereProg1FoiRodado(char entrada[], char modo[]){
    FILE *fteste = fopen(entrada, modo);
    if(!(fteste)){
        printf("\nERRO: arquivo binario nao encontrado! rode o programa um antes\n\n");
        exit(EXIT_FAILURE);
    }
}


void ResetaString(char str[]){
    int i = 0;
    for(i=0; i< (strlen(str)); i++){
        str[i] = '\0';
    }
}

void ResetaStrComTam(char str[], int tam){
    int i = 0;
    for(i=0; i< tam; i++){
        str[i] = '\0';
    }
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

int Get_Set_QuantidadeGeneros(char acao[], int valor){
    static int total_Generos = 0;

    if(strcmp(acao, "set") == 0){
        total_Generos = valor;
    }else if(strcmp(acao, "get") == 0){
        total_Generos = total_Generos;
    }else{
        printf("ERRO: '%s' eh um comando nao existente.\n=> Comandos validos: 'get', 'set'\n", acao);
        exit(EXIT_FAILURE);
    }
    return total_Generos;

}

void Dispatch_table_Get_Set_inicializa(){
    for (int i = 0; i < 256; i++){
        dispatch_table_Get_Or_Set[i] = NULL;

    }   
    dispatch_table_Get_Or_Set['d'] = Get_Set_QuantidadeDocumento; //d = documento
    dispatch_table_Get_Or_Set['p'] = Get_Set_QuantidadePalavras; // p = palavra
    dispatch_table_Get_Or_Set['g'] = Get_Set_QuantidadeGeneros; // p = palavra

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

char* Get_Set_NomeArquivos(char acao[], char diretorio[], int idx){
    const int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    static int idx_doc = 0;
    static char arquivos[10000000][100]; //[qtd docs][tamanho do texto]
    char *str = NULL; 
    
    if(strcmp(acao, "set") == 0){
        strcpy(arquivos[idx_doc], diretorio);
        idx_doc++;
    }else if(strcmp(acao, "get") == 0){
    }else{
        printf("ERRO: '%s' eh um comando nao existente.\n=> Comandos validos: 'get', 'set'\n", acao);
        exit(EXIT_FAILURE);   
    }
    str = arquivos[idx];
    return str;
}

char* Get_Set_TipoNoticia(char acao[], char tipo[], int idx){
    const int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    static int idx_doc = 0;
    static char lista_tipos[10000000][10]; //[qtd docs][tamanho do texto]
    char *str = NULL; 
    
    if(strcmp(acao, "set") == 0){
        strcpy(lista_tipos[idx_doc], tipo);
        idx_doc++;
    }else if(strcmp(acao, "get") == 0){
    }else{
        printf("ERRO: '%s' eh um comando nao existente.\n=> Comandos validos: 'get', 'set'\n", acao);
        exit(EXIT_FAILURE);   
    }
    str = lista_tipos[idx];
    return str;
}

//novas

int VerificaGeneroExiste(char tipo[], char **pp_auxGenero, int idx_doc){
    int i = 0, existe = 0, qtd_generos = 0;
    qtd_generos = Get_Or_Set_Valor('g', "get", null);

    for(i = 0; i < idx_doc; i++){
        if (strcmp(pp_auxGenero[i], tipo) == 0){
            existe = 1;
            return 1;
        }
    }
    if (!existe){
        Get_Or_Set_Valor('g', "set", qtd_generos+1);
    }
    return 0;
    printf("\n");
}

void ArmazenaAuxiliaresEmBinario(FILE * bin, int qtd_Generos){
    fwrite(&qtd_Generos, sizeof(int), 1, bin);
}

void LeAuxiliaresBinario(FILE * bin){
    int qtd_generos = 0;
    fread(&qtd_generos, sizeof(int), 1, bin);
    Get_Or_Set_Valor('g', "set", qtd_generos);
}

int ConfereTxt(char str[]){

    int i = 0, tam = 0;
    tam = strlen(str);

    for(i = 0; i < tam; i++){
        if(str[i] == '.'){
            return 1;
        }
    }
    return 0;
}

void RelatorioPalavra(tPalavra **pp_Palavras, tDocumento **pp_Docs){
    char nome[100];
    int idx_palavra = -1, qtd_docs = 0, qtd_docs_presente = 0;
    qtd_docs = Get_Or_Set_Valor('d', "get", null);
    printf("digite uma palavra: ");
    scanf("%s", nome);
    scanf("%*c");

    //garante que a palavra sera valida e ja sai com o indice dela no array
    while (TRUE){
        idx_palavra = VerificaPalavraExiste(pp_Palavras, nome);
        if(idx_palavra != -1){
            break;
        }
        ResetaStrComTam(nome, 100);
        printf("nome invalido!, digite outro: ");
        scanf("%s", nome);
        scanf("%*c");
    }

    qtd_docs_presente = Calcula_EmQuantosDocumentosEstaPresente(pp_Palavras[idx_palavra], qtd_docs);
    
    printf("\nnumero de documentos com a palavra: %d\n", qtd_docs_presente);
    printf("----------------------------------------------\n");

    RelatorioPalavra_frequencia(pp_Palavras, qtd_docs, idx_palavra);
    printf("----------------------------------------------\n");
    RelatorioPalavra_genero(pp_Palavras[idx_palavra], pp_Docs, Get_Or_Set_Valor('g', "get", null));

}

void  RelatorioPalavra_genero(tPalavra *p_Palavra, tDocumento **pp_Docs, int qtd_generos){
    int i = 0, qtd_Docs = 0, iNovoGenero = 0;
    char **pp_TodosGeneros;
    char **pp_UnicoGeneros;
    char genero[5] = "";
    qtd_Docs = Get_Or_Set_Valor('d', "get", null);

    //iniclizaza generos auxiliares
    pp_UnicoGeneros = malloc(sizeof(char*) * qtd_generos);
    pp_TodosGeneros = malloc(sizeof(char*) * qtd_Docs);

    
    //armazeno no pp_UnicoGenero os generos sem repeticao
    for(i = 0; i < qtd_Docs; i++){
        ResetaStrComTam(genero, 5);
        pp_TodosGeneros[i] = Get_GeneroArquivo(pp_Docs[i]);
        strcpy(genero, pp_TodosGeneros[i]);
        iNovoGenero = Armazena_Genero_Array(pp_TodosGeneros, pp_UnicoGeneros, genero, i, iNovoGenero);
    }

    int *freq;
    int *freq_aux;
    int *acessado;
    freq = malloc(sizeof(int) * qtd_generos);
    freq_aux = malloc(sizeof(int) * qtd_generos);
    acessado = malloc(sizeof(int) * qtd_generos);

    
    for(i = 0; i < qtd_generos; i++){
        freq[i] = Calcula_Frequencia_Palavra_no_TipoNoticia(pp_Docs, p_Palavra, pp_UnicoGeneros[i], qtd_Docs);
        freq_aux[i] = freq[i];
        acessado[i] = 0;
    }

    qsort(freq, qtd_generos, sizeof(int), Cmp_Freq);
    
    //impressao 
    int idx_aux = 0, contador = 1;
    
    printf("Impressao frequencia ordenada em generos:\n");
    for(i = 0; i < qtd_generos; i++){
        for(idx_aux = 0; idx_aux < qtd_generos; idx_aux++){
            if((freq[i] == freq_aux[idx_aux]) && acessado[idx_aux] == 0){
                printf("    top %d: frequencia %d no genero %s\n", contador, freq_aux[idx_aux], pp_UnicoGeneros[idx_aux]);
                acessado[idx_aux] = 1;
                contador++;
            }
        }
    }
    
    free(pp_TodosGeneros);
    free(pp_UnicoGeneros);
    free(freq);
    free(freq_aux);
    free(acessado);
}


int Cmp_Freq(const void* f1, const void* f2){
    int freq1 = *(int*)f1;
    int freq2 = *(int*)f2;
    return freq2 - freq1;
}

int Armazena_Genero_Array(char **pp_TodosGeneros, char **pp_UnicoGeneros, char genero[], int idx_Docs, int iNovoGenero){
    int i = 0, existe = 0;
    for(i = 0; i < idx_Docs; i++){
        if (strcmp(pp_TodosGeneros[i], genero) == 0){
            existe = 1;
            break;
        }
    }
    if(!existe){
        pp_UnicoGeneros[iNovoGenero] = pp_TodosGeneros[i];
        iNovoGenero++;
    }
    return iNovoGenero;
}


int Calcula_Frequencia_Palavra_no_TipoNoticia(tDocumento** pp_Docs, tPalavra* p_Palavra, char genero[], int qtd_docs){
    int idx_doc = 0, frequencia = 0;
    char* tipo = NULL;
    
    for(idx_doc = 0; idx_doc < qtd_docs; idx_doc++){
        tipo = Get_GeneroArquivo(pp_Docs[idx_doc]);

        if(strcmp(genero, tipo) == 0){
            frequencia += Get_FrequenciaPalavraNoDoc(p_Palavra, idx_doc);
        }
    }
    return frequencia;
}
