#include "../lib/lib.h"

struct tPalavra{
    char palavra[50];
    int *pFrenquencia;
    double *pTF_IDF;
};

//----PROGRAMA 1-----
void Idx_Palavras(tPalavra** pp_Palavras){
    int i = 0, j = 0;
    int qtd_palavras = Get_Or_Set_Valor('p', "get", null);
    int qtd_docs = Get_Or_Set_Valor('d', "get", null);

    for(i=0; i<qtd_palavras; i++){
        printf("palavra[%d]: %s\n", i,pp_Palavras[i]->palavra);
        for(j=0; j<qtd_docs; j++){
            printf("doc[%d]:   f = %d  idf =  %.2lf\n", j, pp_Palavras[i]->pFrenquencia[j], pp_Palavras[i]->pTF_IDF[j]);
        }
        printf("\n");
    }
}
//---------------


//leitura
tPalavra** LeTodosOsArquivosPalavra(FILE* fArquivo_caminho_noticias, tPalavra** pp_Palavras, int qtd_Arquivos, char argv[]){
    int i = 0;
    char linha[100000];

    //leitura unitaria de arquivos.txt
    for(i = 0; i < qtd_Arquivos; i++){
        fscanf(fArquivo_caminho_noticias, "%[^\n]", linha);
        fscanf(fArquivo_caminho_noticias, "%*c");
        
        FILE *fArquivo = Get_ArquivoNoticia(linha, argv);
        pp_Palavras = LeArquivo(fArquivo, pp_Palavras, i);

        //tratar docs

        fclose(fArquivo);
    }

    //tratamento do TF-IDF
    for(i = 0; i < (Get_Or_Set_Valor('p', "get", null)); i++){
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
    
    qtdDocumentos = Get_Or_Set_Valor('d', "get", null);
    
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
        ResetaString(str);
    }
    return pp_Palavras;
}

// --------relacionadas com arquivo diretorio--------
FILE* Get_ArquivoNoticia(char linha[], char argv[]){
    char diretorio[1000], temp[50], caminho[100], str[1000], argv_copy[100];

    ResetaStrComTam(argv_copy, 100);
    strcpy(argv_copy, argv);
    ResetaStrComTam(str, 1000);
    ResetaStrComTam(diretorio, 1000);
    ResetaStrComTam(caminho, 100);
    // ---- nome e tipo de noticia -----
    char tipo[100], nome_arq[100];
    ResetaStrComTam(nome_arq, 100);
    sscanf(linha, "%[^ ]", caminho);
    sscanf(linha, "%*[^/]%*c%[^ ]", nome_arq);
    sscanf(linha, "%*[^ ]%*c%s", tipo);    

    
    Get_Set_NomeArquivos("set", nome_arq, null);
    Get_Set_TipoNoticia("set", tipo, null);


    int fim = 0;
    while(1){
        ResetaStrComTam(str, 1000);
        sscanf(argv_copy, "%[^/]", str);
        sscanf(argv_copy,"%*[^/]%*c%s", argv_copy);
        fim = ConfereTxt(str);
        if(fim){
            strcat(diretorio, caminho);
            break;
        }
        strcat(diretorio, str);
        strcat(diretorio, "/");
    }

    ConfereEntradaValida(diretorio, "r");
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
int ComparaPalavras(const void *p1, const void *p2){
    const struct tPalavra *palavra1 = p1;
    const struct tPalavra *palavra2 = p2;
    if(strcmp(palavra1->palavra, palavra2->palavra) == 0){
        return 1;
    }
    return 0;
}

int Retorna_Idx_Palavra(tPalavra** pp_Palavras, char palavra[]){
    int qtd_palavras = Get_Or_Set_Valor('p', "get", null);
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

int Get_Qtd_Palavras_No_Doc(tPalavra** pp_Palavras, int idx_doc){
    int i = 0, j = 0, count = 0;
    int qtd_palavras = Get_Or_Set_Valor('p', "get", null);
    int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    for(i=0; i<qtd_palavras; i++){
        for(j=0; j<qtd_docs; j++){
            if(pp_Palavras[i]->pFrenquencia[j] != 0){
                count++;
            }
        }
    }
    return count;
}

void ImprimePalavra(tPalavra* p_palavra){
    printf("%s", p_palavra->palavra);
}

int RetornaFrequenciaPalavra(tPalavra* p_palavra, int idx_doc){
    return p_palavra->pFrenquencia[idx_doc];
}

//-----------------calculo com palavras--------------------
void Insere_Frequencias_em_Doc(int frequencia, int idx_doc, tPalavra* p_palavra){
    p_palavra->pFrenquencia[idx_doc] = frequencia;
}

void Insere_TF_IDF_em_Doc(double TF_IDF, int idx_doc, tPalavra *p_palavra){
    p_palavra->pTF_IDF[idx_doc] = TF_IDF;
}

void Atualiza_Palavra_TF_IDF(tPalavra *p_palavra, int qtdDocumentos){
    //calculo:
    //TF-IDF eh dada pelo produto de TF(d, p) * IDF(p)
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


//------------arquivos binarios------------
//====armazenamento
void ArmazenaPalavrasEmBinario(FILE* bin, tPalavra** pp_Palavras, int qtd_palavras){
    int i = 0;
    //qtd palavras
    fwrite(&qtd_palavras, sizeof(int), 1, bin);
    
    for(i = 0; i < qtd_palavras; i++){//nao esta armazenando todas
        Armazena_UMA_PalavraEmBinario(pp_Palavras[i], bin);
    }
}

void Armazena_UMA_PalavraEmBinario(tPalavra* p_Palavra, FILE* bin){
    int tam_Palavra = strlen(p_Palavra->palavra);
    int tam_pFrequencia = Get_Or_Set_Valor('d', "get", null);
    
    
    fwrite(&tam_Palavra, sizeof(int), 1, bin);
    fwrite(p_Palavra->palavra, sizeof(char), tam_Palavra, bin);
    fwrite(&tam_pFrequencia, sizeof(int), 1, bin);
    fwrite(p_Palavra->pFrenquencia, sizeof(int), tam_pFrequencia, bin);
    fwrite(p_Palavra->pTF_IDF, sizeof(double), tam_pFrequencia, bin);

}

//====leitura
tPalavra** LeDicionarioBinario(FILE *bin){    
    tPalavra** pp_Palavras = NULL;
    char palavra [50];
    int *pFrenquencia;
    double *pTF_IDF;
    int qtd_palavras = 0;    
    int tam_palavra = 0;
    int tam_pFrequencia = 0;

    //td palavras
    fread(&qtd_palavras, sizeof(int), 1, bin);
    Get_Or_Set_Valor('p', "set", qtd_palavras);
    //printf("QTD PALAVRAS %d\n\n", qtd_palavras);

    pp_Palavras = malloc(sizeof(tPalavra*) * qtd_palavras);


    int i = 0, j = 0;
    
    for(i = 0; i < qtd_palavras; i++){
        ResetaStrComTam(palavra, 50);
        //palavra
        fread(&tam_palavra, sizeof(int), 1, bin);
        fread(palavra, sizeof(char), tam_palavra, bin);
        //frequencia
        fread(&tam_pFrequencia, sizeof(int), 1, bin);
        pFrenquencia = malloc(sizeof(int) * tam_pFrequencia);
        fread(pFrenquencia, sizeof(int), tam_pFrequencia, bin);
        //tf-idf
        pTF_IDF = malloc(sizeof(double) * tam_pFrequencia);
        fread(pTF_IDF, sizeof(double), tam_pFrequencia, bin);


        pp_Palavras[i] = malloc(sizeof(tPalavra));
        strcpy(pp_Palavras[i]->palavra, palavra);
        pp_Palavras[i]->pFrenquencia = malloc(sizeof(int)*tam_pFrequencia);
        pp_Palavras[i]->pTF_IDF = malloc(sizeof(double)*tam_pFrequencia);

        //printf("palavra[%d]:  tamStr: %d str: %s tamFrequencia: %d\n", i, tam_palavra, palavra, tam_pFrequencia);
        //printf("frequencia: ");
        for(j=0; j<tam_pFrequencia; j++){
            //printf("%d ", pFrenquencia[j]);
            pp_Palavras[i]->pFrenquencia[j] = pFrenquencia[j];
        }
        //printf("\n");
        //printf("TF-IDF ");
        for(j=0; j<tam_pFrequencia; j++){
            //printf("%lf ", pTF_IDF[j]);
            pp_Palavras[i]->pTF_IDF[j] = pTF_IDF[j];
        }
        //printf("\n\n");

        free(pFrenquencia);
        free(pTF_IDF);
   }
   return pp_Palavras;
}   



//--------------liberacao de memoria--------------
void LiberaPalavras(tPalavra **pp_Palavras){
    int qtdPalavras = 0, i = 0;
    qtdPalavras = Get_Or_Set_Valor('p', "get", null);
    
    for(i = 0; i < qtdPalavras; i++){
        free(pp_Palavras[i]->pTF_IDF);
        free(pp_Palavras[i]->pFrenquencia);
        free(pp_Palavras[i]);
    }
    free(pp_Palavras);
}

//impressao
void Teste_ImprimePalavras(tPalavra **pp_Palavras){
    int iPalavra = 0, qtdPalavras = 0, iFrequencia = 0, qtdDocs = 0;
    qtdDocs = Get_Or_Set_Valor('d', "get", null);
    qtdPalavras = Get_Or_Set_Valor('p', "get", null);
   
    for(iPalavra = 0; iPalavra < qtdPalavras; iPalavra++){
        
        printf("        Palavra: %s\n", pp_Palavras[iPalavra]->palavra);
        
        for(iFrequencia = 0; iFrequencia < qtdDocs; iFrequencia++){
            printf("\ndoc[%d] f: %d tf-idf: %lf", iFrequencia, pp_Palavras[iPalavra]->pFrenquencia[iFrequencia], pp_Palavras[iPalavra]->pTF_IDF[iFrequencia]);
        }
        printf("\n\n");
        
    }   
}
