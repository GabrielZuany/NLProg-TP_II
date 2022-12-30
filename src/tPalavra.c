#include "../lib/tPalavra.h"

struct tPalavra{
    char palavra [50];
    int *pFrenquencia;
    double *pTF_IDF;
};


//leitura
tPalavra** LeTodosOsArquivosPalavra(FILE* fArquivo_caminho_noticias, tPalavra** pp_Palavras, int qtd_Arquivos){
    int i = 0;
    char linha[100000];

    //leitura unitaria de arquivos.txt
    for(i = 0; i < qtd_Arquivos; i++){
        fscanf(fArquivo_caminho_noticias, "%[^\n]", linha);
        fscanf(fArquivo_caminho_noticias, "%*c");
        
        FILE *fArquivo = Get_ArquivoNoticia(linha);
        pp_Palavras = LeArquivo(fArquivo, pp_Palavras, i);

        //tratar docs

        fclose(fArquivo);
    }

    //tratamento do TF-IDF
    for(i = 0; i < (Get_Or_Set_Valor('p', "get", ValorArbitrario)); i++){
        Atualiza_Palavra_TF_IDF(pp_Palavras[i], qtd_Arquivos);
    }
    return pp_Palavras;
}

tPalavra** LeArquivo(FILE* fArquivo, tPalavra **pp_Palavras, int idxDocumento){
    char str[50];
    static int idxPalavra = 0;
    tPalavra* p_palavra = NULL;
    int qtdDocumentos = 0, frequenciaNoDocumento = 0;
    int idx_aux = 0, freq = 0;
    
    qtdDocumentos = Get_Or_Set_Valor('d', "get", ValorArbitrario);
    
    while(fscanf(fArquivo,"%s", str) == 1){
        
        if(!(PalavraRegistrada(pp_Palavras, (idxPalavra), str))){

            pp_Palavras = (tPalavra**)realloc(pp_Palavras, sizeof(tPalavra*) * (idxPalavra + 2));
            p_palavra = Inicializa_Palavra(str, qtdDocumentos);
            pp_Palavras[idxPalavra] = p_palavra;
            Insere_Frequencias_em_Doc(1, idxDocumento, pp_Palavras[idxPalavra]);
            idxPalavra++;
            Get_Or_Set_Valor('p', "set", idxPalavra);
        }else{

            idx_aux = Retorna_Idx_Palavra(pp_Palavras, str);
            freq = pp_Palavras[idx_aux]->pFrenquencia[idxDocumento];    
            Insere_Frequencias_em_Doc((freq+1), idxDocumento, pp_Palavras[idx_aux]);
        }

        //printf("%d: %s\n", i, palavra); //verifica cada palavra
        ResetaString(str);
    }
    return pp_Palavras;
}


void TEMP_ImprimeStructPalavras(tPalavra** pp_Palavras){
    int i = 0, j = 0;
    int qtd_palavras = Get_Or_Set_Valor('p', "get", ValorArbitrario);
    int qtd_docs = Get_Or_Set_Valor('d', "get", ValorArbitrario);

    for(i=0; i<qtd_palavras; i++){
        printf("palavra[%d]: %s\n", i,pp_Palavras[i]->palavra);
        for(j=0; j<qtd_docs; j++){
            printf("doc[%d]:   f = %d  idf =  %.2lf\n", j, pp_Palavras[i]->pFrenquencia[j], pp_Palavras[i]->pTF_IDF[j]);
        }
        printf("\n");
    }
}



// --------relacionadas com arquivo diretorio--------
FILE* Get_ArquivoNoticia(char caminho[]){
    char aux[1000];
    char diretorio[10000];
    
    sscanf(caminho, "%s", aux);
    sprintf(diretorio, "datasets/tiny/%s", aux);
    
    ConfereEntradaValida(diretorio);
    FILE *fArquivo = fopen(diretorio, "r");
    return fArquivo;
}

// --------------inicializacao de ponteiro ----------
tPalavra** Inicializa_Array_Palavra(){
    tPalavra** pp_Palavras = NULL;
    pp_Palavras = (tPalavra**)malloc(sizeof(tPalavra*));
    return pp_Palavras;
}

tPalavra* Inicializa_Palavra(char str[], int qtd_docs){
    tPalavra* p_palavra = malloc(sizeof(tPalavra));
    p_palavra->pFrenquencia = malloc(sizeof(int) * qtd_docs);
    p_palavra->pTF_IDF = malloc(sizeof(double) * qtd_docs);
    strcpy(p_palavra->palavra, str);

    int i = 0;
    for(i=0; i<qtd_docs; i++){
        Insere_Frequencias_em_Doc(0, i, p_palavra);
        Insere_TF_IDF_em_Doc(0.00, i, p_palavra);
    }
    
    return p_palavra;
}

// -----------------auxiliares----------------------
void ResetaString(char str[]){
    int i = 0;
    for(i=0; i<strlen(str); i++){
        str[i] = '\0';
    }
}

int ComparaPalavras(const void *p1, const void *p2){
    const struct tPalavra *palavra1 = p1;
    const struct tPalavra *palavra2 = p2;
    if(strcmp(palavra1->palavra, palavra2->palavra) == 0){
        return 1;
    }
    return 0;
}

int Retorna_Idx_Palavra(tPalavra** pp_Palavras, char palavra[]){
    int qtd_palavras = Get_Or_Set_Valor('p', "get", ValorArbitrario);
    int i = 0;
    for(i=0; i<qtd_palavras; i++){
        if(strcmp(pp_Palavras[i]->palavra, palavra) == 0){
            return i;
        }
    }
    return -667;
}

int PalavraRegistrada(tPalavra **pp_Palavras, int qtdPalavras, char palavra[]){
    int i = 0;
    for (i = 0; i < qtdPalavras; i++){
        if (strcmp(pp_Palavras[i]->palavra, palavra) == 0){
            return 1;
        }
    }
    return 0;
}

//calculo com palavras
void Insere_Frequencias_em_Doc(int frequencia, int idx_doc, tPalavra* p_palavra){
    p_palavra->pFrenquencia[idx_doc] = frequencia;
}

void Insere_TF_IDF_em_Doc(double TF_IDF, int idx_doc, tPalavra *p_palavra){
    p_palavra->pTF_IDF[idx_doc] = TF_IDF;
}

void Atualiza_Palavra_TF_IDF(tPalavra *p_palavra, int qtdDocumentos){
    //calculo:
    //TF-IDF é dada pelo produto de TF(d, p) * IDF(p)
    //TF: frequencia da palavra no documento(p)
    
    //IDF: ln[(1 + n)/(1 + df(p))] + 1                   
    //        ---------v---------
    //                 x
    
    //   .:. ln(x) + 1

    //n: numero total de documentos
    //df(p): numero de documentos com a palavra

    int idxDocs = 0;
    double TF = 0, IDF = 0;
    int DF = 0, n = 0;

    DF = Calcula_EmQuantosDocumentosEstaPresente(p_palavra, qtdDocumentos);    
    n = qtdDocumentos;
    for(idxDocs = 0; idxDocs < qtdDocumentos; idxDocs++){
        TF = (double)p_palavra->pFrenquencia[idxDocs];
        IDF = Calcula_IDF((double)n, (double)DF);
        p_palavra->pTF_IDF[idxDocs] = TF * IDF;
    }
}

double Calcula_IDF(double n, double DF){
    double IDF = 0, x = 0;
    x = ((1 + n) / (1 + DF));
    IDF = log(x);
    IDF++;
    return IDF;
}


int Calcula_EmQuantosDocumentosEstaPresente(tPalavra *p_palavra, int qtdDocumentos){
    int idxDoc = 0, presencas = 0;

    for(idxDoc = 0; idxDoc < qtdDocumentos; idxDoc++){
        if((p_palavra->pFrenquencia[idxDoc]) > 0){
            presencas++;
        }
    }
    return presencas;
}

//liberacao de arquivos
void LiberaPalavras(tPalavra **pp_Palavras){
    int qtdPalavras = 0, i = 0;
    qtdPalavras = Get_Or_Set_Valor('p', "get", ValorArbitrario);
    
    for(i = 0; i < qtdPalavras; i++){
        free(pp_Palavras[i]->pTF_IDF);
        free(pp_Palavras[i]->pFrenquencia);
        free(pp_Palavras[i]);
    }
    free(pp_Palavras);
}


