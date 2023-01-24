#include "../lib/lib.h"

static Vetor_Get_or_Set_fn dispatch_table_Get_Or_Set[256];



//--------opcao usuario
void ExibeMenu(){
    printf("\n\n|====================== NL PROG ======================|\n\n");
    printf("[0] Sair\n[1] Buscar\n[2] Classificar\n[3] Relatorio dicionario\n[4] Relatorio documentos\n");
    printf("[5] Imprime dicionario\n[6] Imprime documentos\n------\n>>> ");
}

void ExecutaOpcaoUsuario(tDocumento **pp_Docs, tPalavra **pp_Palavras, int opcao, int k){
    
    switch (opcao){
    case 0:
        //sair
        break;
    case 1:
        Buscador(pp_Docs, pp_Palavras);
        break;
    case 2:
        Classificador(pp_Docs, pp_Palavras, k);
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
    fclose(fteste);
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

int Dispatch_table_executa(char dado, char acao[], int valor){
    int idx = (int)dado;

    if (dispatch_table_Get_Or_Set[idx] != NULL)
        return dispatch_table_Get_Or_Set[idx](acao, valor);
    else{
        printf(">> ERRO: A funcao '%c' nao foi definida ainda.\n", dado);
        exit(1);
    }
}

int Get_Or_Set_Valor(char dado, char acao[], int valor_registrar){   
    int x = 0;
    //Dispatch_table_executa('p', 'set', 10); => registra o numero de palavras
    //Dispatch_table_executa('d', 'get', qlq num mas opte por passar NULL); => pega o nunumero de documentos    
    x = Dispatch_table_executa(dado, acao, valor_registrar);
    return x;
}

char* Get_Set_NomeArquivos(char acao[], char diretorio[], int idx){
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
    }return 0;
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
    int i = 0, qtd_Docs = Get_Or_Set_Valor('d', "get", null), iNovoGenero = 0;
    char **pp_TodosGeneros = malloc(sizeof(char*) * qtd_Docs), **pp_UnicoGeneros = malloc(sizeof(char*) * qtd_generos), genero[5] = "";

    for(i = 0; i < qtd_Docs; i++){
        ResetaStrComTam(genero, 5);
        pp_TodosGeneros[i] = Get_GeneroArquivo(pp_Docs[i]);
        strcpy(genero, pp_TodosGeneros[i]);
        iNovoGenero = Armazena_Genero_Array(pp_TodosGeneros, pp_UnicoGeneros, genero, i, iNovoGenero);
    }

    int *freq = malloc(sizeof(int) * qtd_generos), *freq_aux = malloc(sizeof(int) * qtd_generos), *acessado = malloc(sizeof(int) * qtd_generos);
    int idx_aux = 0, contador = 1;

    for(i = 0; i < qtd_generos; i++){
        freq[i] = Calcula_Frequencia_Palavra_no_TipoNoticia(pp_Docs, p_Palavra, pp_UnicoGeneros[i], qtd_Docs);
        freq_aux[i] = freq[i];
        acessado[i] = 0;
    }
    qsort(freq, qtd_generos, sizeof(int), Cmp_Freq);
    //impressao 
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
    LiberacaoAuxiliaresRelatorioPalavra(pp_TodosGeneros, pp_UnicoGeneros, freq, freq_aux, acessado);
}

void LiberacaoAuxiliaresRelatorioPalavra(char **pp_TodosGeneros,char **pp_UnicoGeneros, int *freq, int *freq_aux, int *acessado){
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


// ------------ BUSCADOR ---------------    
void Buscador(tDocumento** pp_Docs, tPalavra** pp_Palavras){
    double *TF_IDF_docs = NULL, *aux_TF_IDF_docs = NULL;
    int encontrou = 0, qtd_palavras_buscador = 0, idx_aux = 0, i = 0, j = 0, qtd_Docs = 0;
    int* idx_palavra = malloc(sizeof(int)), *acessados =  NULL;
    char palavra[100], lixo = '\0';
    
    qtd_Docs = Get_Or_Set_Valor('d', "get", null);
    printf("Digite as palavras que deseja buscar, ex: palavra1 palavra2 palavra3(ENTER)  \n");
    
    //pega os indices das palavras
    while(TRUE){
        scanf("%s", palavra);
        idx_aux = Retorna_Idx_Palavra(pp_Palavras, palavra);

        if (idx_aux != -1){
            encontrou = 1;
            idx_palavra[qtd_palavras_buscador] = idx_aux;
            qtd_palavras_buscador++;
            idx_palavra = (int*)realloc(idx_palavra, (sizeof(int) * (qtd_palavras_buscador + 1)));
            
        }
        scanf("%c", &lixo);
        if(lixo == '\n'){
            break;
        }
    }
    if(!encontrou){
        printf(">>> Nao foi encontrada nenhuma palavra inserida.\n");
        return;
    }

    TF_IDF_docs = malloc(sizeof(double) * qtd_Docs);
    aux_TF_IDF_docs = malloc(sizeof(double) * qtd_Docs);
    acessados = malloc(sizeof(int) * qtd_Docs);

    for(i = 0; i < qtd_Docs; i++){
        acessados[i] = 0;
        TF_IDF_docs[i] = calculaSomatorio_TF_IDF(pp_Docs[i], pp_Palavras ,idx_palavra, qtd_palavras_buscador, i);
        aux_TF_IDF_docs[i] = TF_IDF_docs[i];
    }
    qsort(TF_IDF_docs, qtd_Docs, sizeof(double), Cmp_TF_IDF);
        
    printf("\ntop 10 documentos com maior TF-IDF das palavras selecionadas\n");
    for(i = 0; i < qtd_Docs; i++){
        for(j = 0; j < qtd_Docs; j++){
            if(TF_IDF_docs[i] == aux_TF_IDF_docs[j] && !(acessados[j])){
                acessados[j] = 1;
                printf("doc[%d]: %lf\n", j, TF_IDF_docs[i]);
                break;
            }
        }    
    }
    
    free(TF_IDF_docs);
    free(aux_TF_IDF_docs);
    free(acessados);
    free(idx_palavra);
}

int Cmp_TF_IDF(const void* f1, const void* f2){
    double x = *(double*)f1;
    double y = *(double*)f2;
    if(x > y){
        return -1;
    }
    if(x < y){
        return 1;
    }return 0;
}

double calculaSomatorio_TF_IDF(tDocumento* p_Doc, tPalavra** pp_Palavras , int *idx_palavra, int qtd_palavras_buscador, int idx_documento){
    double somador_tf_idf = 0;
    int i;
    for(i = 0; i < qtd_palavras_buscador; i++){
        somador_tf_idf += Acesso_TF_IDF_NoDocX(pp_Palavras[idx_palavra[i]], idx_documento); 
    }
    return somador_tf_idf;
}

// -------------- CLASSIFICADOR ------------------
void Classificador(tDocumento** pp_Docs, tPalavra** pp_Palavras, int k){
    char palavra[100] = "";
    int qtd_palavras_classificador = 0, encontrou = 0, *idx_palavra = malloc(sizeof(int)), i = 0, idx_aux = 0, pos_palavra_no_idx_palavra = 0;
    char lixo = '\0';
    double *p_frequencia = NULL;
    p_frequencia = malloc(sizeof(double) * 1);
    tDocumento *pDoc_Digitadas = NULL;
    printf("Digite o texto que deseja classificar, ex: palavra1 palavra2 palavra3(ENTER)\n");
    while(TRUE){
        scanf("%s", palavra);
        idx_aux = Retorna_Idx_Palavra(pp_Palavras, palavra);
        if (idx_aux != -1){
            pos_palavra_no_idx_palavra = VerificaPalavraJaDigitada(idx_palavra, idx_aux, qtd_palavras_classificador);
            if(pos_palavra_no_idx_palavra == -1){
                encontrou = 1;
                idx_palavra[qtd_palavras_classificador] = idx_aux;
                p_frequencia[qtd_palavras_classificador] = 0;
                p_frequencia[qtd_palavras_classificador]++;
                qtd_palavras_classificador++;
                idx_palavra = realloc(idx_palavra, (sizeof(int) * (qtd_palavras_classificador + 1)));  
                p_frequencia = realloc(p_frequencia, (sizeof(double) * (qtd_palavras_classificador + 1)));
            }
            else{
                p_frequencia[pos_palavra_no_idx_palavra]++;
            }
        }
        scanf("%c", &lixo);
        if(lixo == '\n') break;
    }
    if(!encontrou){
        printf(" << PALAVRA(S) NAO EXISTE(M) NO CORPUS >>\n");
        return;
    }
    pDoc_Digitadas = InicializaDocumentoClassificador(idx_palavra, qtd_palavras_classificador);
    
    //calculo da distancia
    int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    int *pAcessados = NULL;
    double *pResultadosCos = NULL;
    double *p_aux_ResultadosCos = NULL;
    pAcessados =  calloc(sizeof(int), qtd_docs);
    pResultadosCos = calloc(sizeof(double), qtd_docs);
    p_aux_ResultadosCos = calloc(sizeof(double), qtd_docs);

    for(i = 0; i < qtd_docs; i++){
        pResultadosCos[i] = CalculaDistanciaPorCos(pDoc_Digitadas, pp_Docs[i], i, pp_Palavras, p_frequencia, qtd_palavras_classificador);
        p_aux_ResultadosCos[i] = pResultadosCos[i];
        pAcessados[i] = 0;

    }
    qsort(pResultadosCos, qtd_docs, sizeof(double), Cmp_Distancia_Docs);

    ImprimeResultadoClassificador(pp_Docs, pResultadosCos, p_aux_ResultadosCos, pAcessados, qtd_docs, k);
    ImprimeUmDocumento(pDoc_Digitadas);
    LiberaAuxiliaresClassificador(pDoc_Digitadas, idx_palavra, p_frequencia, pResultadosCos, p_aux_ResultadosCos, pAcessados);
}


void LiberaAuxiliaresClassificador(tDocumento *pDoc_Digitadas, int *idx_palavra, double *p_frequencia, double *pResultadosCos, double *p_aux_ResultadosCos, int *pAcessados){
    LiberaDocumento(pDoc_Digitadas);
    free(idx_palavra);
    free(pResultadosCos);
    free(p_aux_ResultadosCos);
    free(pAcessados);
    free(p_frequencia);
}

int Cmp_Distancia_Docs(const void *d1, const void *d2){
    double x1 = *(double*)d1;
    double x2 = *(double*)d2;
    if (x2 > x1){
        return 1;
    }
    if (x2 < x1){
        return -1;
    }
    return 0;
}

int VerificaPalavraJaDigitada(int* idx_palavra, int idx_aux, int qtd_palavras_classificador){
    int i = 0, pos = 0, existe = 0;
    for(i=0; i<qtd_palavras_classificador; i++){
        if(idx_aux == idx_palavra[i]){
            existe = 1;
            pos = i;
            break;
        }
    }
    if(!existe) pos = -1;
    return pos;
}

double CalculaDistanciaPorCos(tDocumento* pDoc_Digitadas, tDocumento* p_Doc, int idx_doc, tPalavra** pp_Palavras, double* p_frequencia, int qtd_palavras_classificador){
    double dist_entre_docs = 0.00, x = 0.00, y1 = 0.00, y2 = 0.00;
    int i = 0, idx_palavra = 0, qtdDocs = Get_Or_Set_Valor('d', "get", null);
    tPalavra* p_temp_palavra = NULL;
    double *p_TFIDF_palavra_em_doc1 = calloc(sizeof(double), qtd_palavras_classificador);
    double *p_TFIDF_palavra_em_doc2 = calloc(sizeof(double), qtd_palavras_classificador);

    for(i = 0; i < qtd_palavras_classificador; i++){
        idx_palavra = Retorna_Idx_Palavra_ViaDoc(pDoc_Digitadas, i);
        p_temp_palavra = pp_Palavras[idx_palavra];
      
        p_TFIDF_palavra_em_doc1[i] = Calcula_TF_IDF(p_frequencia[i], qtdDocs, Calcula_EmQuantosDocumentosEstaPresente(p_temp_palavra, qtdDocs));
        p_TFIDF_palavra_em_doc2[i] = Acesso_TF_IDF_NoDocX(p_temp_palavra, idx_doc);

    }

    x = CalculaSomatorioNumerador(pDoc_Digitadas, p_Doc, qtd_palavras_classificador, p_TFIDF_palavra_em_doc1, p_TFIDF_palavra_em_doc2);
    y1 = CalculaSomatorioDenominador(pDoc_Digitadas, p_Doc, p_TFIDF_palavra_em_doc1, qtd_palavras_classificador);
    y2 = CalculaSomatorioDenominador(pDoc_Digitadas, p_Doc, p_TFIDF_palavra_em_doc2, qtd_palavras_classificador);
    
    free(p_TFIDF_palavra_em_doc1);
    free(p_TFIDF_palavra_em_doc2);
    
    if((y1 * y2) == 0){
        return 0.00;
    }
    dist_entre_docs = (x /(y1*y2));
    return dist_entre_docs;
}

double CalculaSomatorioNumerador(tDocumento *pDoc_Digitadas, tDocumento *p_Doc,  int qtd_palavras_classificador, double *a, double *b){
    //         E[tf-idf(w,dx) * tfidf-(w, di)]
    //           -----v-----    -------v------
    //                a[w]             b[w]
    
    double somatorio = 0.00;
    int i = 0;

    for(i = 0; i < qtd_palavras_classificador; i++){
        somatorio += (a[i] * b[i]);
    }
    return somatorio;
}

double CalculaSomatorioDenominador(tDocumento *pDoc_Digitadas, tDocumento *p_Doc, double* p_TFIDF_palavra_em_doc, int qtd_palavras_classificador){
    // sqrt[E(tf-idf(w,d1)^2)] 
    //  ----------v------------   
    //            y 
    
    int i = 0;
    double somatorio = 0.00;
    for(i=0; i<qtd_palavras_classificador; i++){
        somatorio = somatorio + (p_TFIDF_palavra_em_doc[i] * p_TFIDF_palavra_em_doc[i]);
    }
    return (somatorio);
}

//--------
int GaranteOpcaoValida(){
    int opcao = -1, voltas = 0;
    char linha[100];

    while (!OpcaoValida(opcao)){
        if(voltas > 0){
            printf("opcao invalida! digite novamente\n");
        }
        ResetaStrComTam(linha, 100);
        scanf("%[^\n]", linha);
        scanf("%*c");
        sscanf(linha, "%1d", &opcao);
        voltas++;
    }
    return opcao;
}

int OpcaoValida(int opcao){
    if (0 <= opcao && opcao <= 6){
        return 1;
    }
    return 0;
}
