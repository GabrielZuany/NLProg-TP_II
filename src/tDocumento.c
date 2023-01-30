#include "../lib/lib.h"

struct tDocumento{
    char nome_documento[100];
    char tipo[10];
    int idx;
    int* idx_palavras;
    int qtd_palavras_contidas;
};

//------inicializacao---------
tDocumento** Inicializa_Array_Docs(int qtd_docs){
    tDocumento** pp_Docs = NULL;
    pp_Docs = (tDocumento**)malloc(sizeof(tDocumento*)*qtd_docs);
    return pp_Docs;
}

tDocumento* Inicializa_Doc(tPalavra** pp_Palavras, char nome[], char tipo[], int idx){
    tDocumento* p_Doc = malloc(sizeof(tDocumento));
    int qtd_palavras_no_doc = Get_Qtd_Palavras_No_Doc(pp_Palavras, idx);

    p_Doc->idx_palavras = malloc(sizeof(int)*qtd_palavras_no_doc);
    p_Doc->qtd_palavras_contidas = qtd_palavras_no_doc;
    p_Doc->idx = idx;
    strcpy(p_Doc->nome_documento, nome);
    strcpy(p_Doc->tipo, tipo);

    return p_Doc;
}

tDocumento* InicializaDocumentoClassificador(int* idx_palavra, int qtd_palavras_classificador){
    int i = 0;
    tDocumento *doc = malloc(sizeof(tDocumento));
    doc->idx_palavras = malloc(sizeof(int)*qtd_palavras_classificador);
    doc->qtd_palavras_contidas = qtd_palavras_classificador;
    doc->idx = 0;
    
    for(i = 0; i < qtd_palavras_classificador; i++){
        doc->idx_palavras[i] = idx_palavra[i];  
    }

    return doc;
}

//------registrar palavras e montar Struct-------
tDocumento** RegistraPalavrasNosDocumentos(tPalavra** pp_Palavras, tDocumento** pp_Docs){
    int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    int idx_doc, i = 0;
    char* nome = NULL;
    char* tipo = NULL;
    char **pp_auxGenero;
    pp_auxGenero = malloc(sizeof(char*) * qtd_docs);
    for(i = 0; i < qtd_docs; i++){
        pp_auxGenero[i] = malloc(sizeof(char)*5);
        ResetaStrComTam(pp_auxGenero[i], 5);
    }


    for(idx_doc=0; idx_doc<qtd_docs; idx_doc++){
        nome = Get_Set_NomeArquivos("get", "", idx_doc);
        tipo = Get_Set_TipoNoticia("get", "", idx_doc);
        strcpy(pp_auxGenero[idx_doc], tipo);
        VerificaGeneroExiste(tipo, pp_auxGenero, idx_doc);
        pp_Docs[idx_doc] = Inicializa_Doc(pp_Palavras, nome, tipo, idx_doc);
        pp_Docs[idx_doc] = RegistraPalavrasNoDocumentoAtual(pp_Palavras, idx_doc, pp_Docs[idx_doc]);
    }

    LiberaAuxGenero(pp_auxGenero, qtd_docs);

    return pp_Docs;
}

tDocumento* RegistraPalavrasNoDocumentoAtual(tPalavra** pp_Palavras, int idx_doc, tDocumento* p_Doc){
    int idx_palavra = 0;
    int idx_palavra_doc = 0;
    char tipo[5] = "---";
    int qtd_palavras = Get_Or_Set_Valor('p', "get", null);
    strcpy(tipo, p_Doc->tipo);
    for(idx_palavra = 0; idx_palavra < qtd_palavras; idx_palavra++){
        
        if(RetornaFrequenciaPalavra(pp_Palavras[idx_palavra], idx_doc) > 0){
            p_Doc->idx_palavras[idx_palavra_doc] = idx_palavra;
            idx_palavra_doc++;
        }
    }

    p_Doc->qtd_palavras_contidas = idx_palavra_doc;
    return p_Doc;
}



//---------auxiliares-------------
char* Get_NomeArquivos(tDocumento** pp_Docs, int idx){
    char *str = NULL; 
    str = pp_Docs[idx]->nome_documento;
    return str;
}

char *Get_GeneroArquivo(tDocumento* p_Doc){
    char *tipo;
    tipo = p_Doc->tipo;
    //tipo = malloc(sizeof(char) * 5);
    //strcpy(tipo, p_Doc->tipo);
    return tipo;
}

//--------arquivo binario---------
//====armazenamento
void ArmazenaDocumentosEmBinario(FILE* bin, tDocumento** pp_Docs, int qtd_Arquivos){
    int i = 0;
    //qtd arquivos
    fwrite(&qtd_Arquivos, sizeof(int), 1, bin);
    
    for(i = 0; i < qtd_Arquivos; i++){//nao esta armazenando todas
        Armazena_UM_DocumentoEmBinario(pp_Docs[i], bin);
    }
}

void Armazena_UM_DocumentoEmBinario(tDocumento* p_Doc, FILE* bin){
    int tamNome = 0, tamTipo = 0;
    tamNome = strlen(p_Doc->nome_documento);
    tamTipo = strlen(p_Doc->tipo);

    //qtd de palavras contidas
    fwrite(&(p_Doc->qtd_palavras_contidas), sizeof(int), 1, bin);
    //nome doc
    fwrite(&tamNome, sizeof(int), 1, bin);
    //printf("%d %s\n", tamNome, p_Doc->nome_documento);
    fputs(p_Doc->nome_documento, bin);
    //tipo
    fwrite(&tamTipo, sizeof(int), 1, bin);
    fputs(p_Doc->tipo, bin);
    //idx doc
    fwrite(&(p_Doc->idx), sizeof(int), 1, bin);
    //idx palavras
    int i;
    for(i=0; i < p_Doc->qtd_palavras_contidas; i++){
        fwrite(&(p_Doc->idx_palavras[i]), sizeof(int), 1, bin);
    }
}

//====leitura
tDocumento** LeDocsBinario(FILE *bin){
    tDocumento** pp_Docs = NULL;
    int qtdDocs = 0;
    char nome[100];
    char tipo[10];
    int* idx_palavras;
    int qtd_palavras;
    int idx_doc;
    int tamNome = 0, tamTipo = 0;
    int i = 0, j = 0;
    
    fread(&qtdDocs, sizeof(int), 1, bin);
    pp_Docs = malloc(sizeof(tDocumento*) * qtdDocs);
    Get_Or_Set_Valor('d', "set", qtdDocs);
    
    for(i = 0; i < qtdDocs; i++){
        ResetaStrComTam(nome, 100);
        ResetaStrComTam(tipo, 10);
        //qtd palavras
        fread(&qtd_palavras, sizeof(int), 1, bin);
        //nome
        fread(&tamNome, sizeof(int), 1, bin);
        fread(nome, sizeof(char), tamNome, bin);
        //tipo
        fread(&tamTipo, sizeof(int), 1, bin);
        fread(tipo, sizeof(char), tamTipo, bin);
        //idx doc
        fread(&idx_doc, sizeof(int), 1, bin);
        //tdx palavras
        idx_palavras = malloc(sizeof(int)*qtd_palavras);
        fread(idx_palavras, sizeof(int), qtd_palavras, bin);

        // montando struct
        pp_Docs[i] = malloc(sizeof(tDocumento));
        pp_Docs[i]->idx = i;
        strcpy(pp_Docs[i]->nome_documento, nome);
        strcpy(pp_Docs[i]->tipo, tipo);
        pp_Docs[i]->qtd_palavras_contidas = qtd_palavras;
        pp_Docs[i]->idx_palavras = malloc(sizeof(int)*qtd_palavras);

        for(j = 0; j < qtd_palavras; j++){
            pp_Docs[i]->idx_palavras[j] = idx_palavras[j];
        }
        free(idx_palavras);
    }

    return pp_Docs;
}

//-----liberar memoria--------
void LiberaDocs(tDocumento** pp_Docs){
    int qtd_Docs = Get_Or_Set_Valor('d', "get", null);
    int i;
    for(i=0; i<qtd_Docs; i++){
        LiberaDocumento(pp_Docs[i]);
    }
    free(pp_Docs);
}

void LiberaDocumento(tDocumento* Doc){
    free(Doc->idx_palavras);
    free(Doc);
}

void LiberaAuxGenero(char **pp_auxGenero, int qtd){
    int i = 0;
    for(i = 0; i < qtd; i++){
        free(pp_auxGenero[i]);
    }
    free(pp_auxGenero);
}

//=============relatorio documento
int Cmp_Qtd_Palavras(const void *p1, const void *p2){
    tDocumento *d1 = *(tDocumento**)p1;
    tDocumento *d2 = *(tDocumento**)p2;
    return (d1->qtd_palavras_contidas - d2->qtd_palavras_contidas);
}

int Cmp_Idx_Docs(const void *p1, const void *p2){
    tDocumento* d1 = *(tDocumento**)p1;
    tDocumento* d2 = *(tDocumento**)p2;
    return (d1->idx) - (d2->idx);
}

void RelatorioDocumento(tDocumento** pp_Docs){
    int i = 0, j = 0;
    int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    
    qsort(pp_Docs, qtd_docs, sizeof(tDocumento*), Cmp_Qtd_Palavras);
    
    //imprimir os 10 maiores
    printf("    Impressao 10 maiores documentos:\n");
    for(i = qtd_docs-1, j = 1; i >= (qtd_docs-10); i--, j++){
        printf("top %d: documento %d com %d palavras\n", j, pp_Docs[i]->idx, pp_Docs[i]->qtd_palavras_contidas);
    }
    //imprimir os 10 menores
    printf("\n");
    printf("    Impressao 10 menores documentos:\n");
    for(i=0, j = 1; i<10; i++, j++){
        printf("top %d: documento %d com %d palavras\n", j, pp_Docs[i]->idx, pp_Docs[i]->qtd_palavras_contidas);
    }
    
    qsort(pp_Docs, qtd_docs, sizeof(tDocumento*), Cmp_Idx_Docs);
}


//============novas
void Teste_ImprimeDocumentos(tDocumento **pp_Docs){
    int qtd_Docs = 0, iDoc = 0;
    qtd_Docs = Get_Or_Set_Valor('d', "get", null);
    int iPalavra = 0;
    
    for(iDoc = 0; iDoc < qtd_Docs; iDoc++){
        printf("doc[%d] qtd_palavras: %d nome: %s tipo: %s \n", pp_Docs[iDoc]->idx, pp_Docs[iDoc]->qtd_palavras_contidas, pp_Docs[iDoc]->nome_documento, pp_Docs[iDoc]->tipo);
        printf("palavras contidas: ");
        for(iPalavra = 0; iPalavra < (pp_Docs[iDoc]->qtd_palavras_contidas); iPalavra++){
            printf("%d ", pp_Docs[iDoc]->idx_palavras[iPalavra]);
        }
        printf("\n\n");
    }
}


void ImprimeUmDocumento(tDocumento *p_doc){
    int i = 0;
    printf("qtd_palavras: %d    ", p_doc->qtd_palavras_contidas);
    printf("indice das palavars contidas: ");
    for(i = 0; i < p_doc->qtd_palavras_contidas; i++){
        printf("%d ", p_doc->idx_palavras[i]);
    }
}

void ImprimeResultadoClassificador(tDocumento** pp_Docs, double* pResultadosCos, double* p_aux_ResultadosCos, int* pAcessados, int qtd_docs, int k){
    int i = 0, idx_doc = 0, qtd_generos = Get_Or_Set_Valor('g', "get", null), iNovoGenero = 0;
    int *pPresencasEmCadaGenero = calloc(sizeof(int), qtd_generos);
    char genero[5] = "";
    char **pp_UnicoGeneros = malloc(sizeof(char*) * qtd_generos);
    char **pp_TodosGeneros = malloc(sizeof(char*) * qtd_docs);

    //armazeno no pp_UnicoGenero os generos sem repeticao
    for(i = 0; i < qtd_docs; i++){
        ResetaStrComTam(genero, 5);
        pp_TodosGeneros[i] = Get_GeneroArquivo(pp_Docs[i]);
        strcpy(genero, pp_TodosGeneros[i]);
        iNovoGenero = Armazena_Genero_Array(pp_TodosGeneros, pp_UnicoGeneros, genero, i, iNovoGenero);
    }

    for(i = 0; i < k; i++){
        for(idx_doc = 0; idx_doc < qtd_docs; idx_doc++){
            if ((pResultadosCos[i] == p_aux_ResultadosCos[idx_doc]) && (pAcessados[idx_doc] == 0)){
                printf("doc[%d] %s   %.4lf\n", idx_doc, pp_Docs[idx_doc]->nome_documento, pResultadosCos[i]);
                pAcessados[idx_doc] = 1;
                AdicionaPresencaEmGenero(pp_Docs[idx_doc]->tipo, pp_UnicoGeneros, pPresencasEmCadaGenero, qtd_generos);
                break;
            }
        }   
    }
    ImprimeGeneroComMaisPresencas(pp_UnicoGeneros, pPresencasEmCadaGenero, qtd_generos, k);
    free(pPresencasEmCadaGenero);
    free(pp_TodosGeneros);
    free(pp_UnicoGeneros);
}

void AdicionaPresencaEmGenero(char* genero, char** pp_UnicoGeneros, int* pPresencasEmCadaGenero, int qtd_generos){
    int i = 0;
    for(i = 0; i < qtd_generos; i++){
        if (strcmp(genero, pp_UnicoGeneros[i]) == 0){
            pPresencasEmCadaGenero[i]++;
            return;
        }
    }
}

void ImprimeGeneroComMaisPresencas(char **pp_UnicoGeneros, int *pPresencasEmCadaGenero, int qtd_generos, int k){
    int i = 0, maior = 0;
    for(i = 0; i < qtd_generos; i++){
        if(i == 0){
            maior = pPresencasEmCadaGenero[i];
            continue;
        }
        if(pPresencasEmCadaGenero[i] >= maior){
            maior = pPresencasEmCadaGenero[i];
        }
    }
    printf("\n-----------------------------------------------------------------------------------\n");
    printf("Resultado: existem maiores probabilidades de o texto pertencer ao(s) genero(s): ");
    for(i = 0; i < qtd_generos; i++){
        if (pPresencasEmCadaGenero[i] == maior){
            printf("%s ", pp_UnicoGeneros[i]);
        }
    }
    printf("\nobs.: o(s) genero(s) possui(em) %d presencas dentre os k(%d) documentos mais proximos", maior, k);
    printf("\n-----------------------------------------------------------------------------------\n");
}

int ExistePalavraEmDoc(int idx_palavra, tDocumento* p_Doc){
    int i;
    for(i=0; i<p_Doc->qtd_palavras_contidas; i++){
        if(idx_palavra == p_Doc->idx_palavras[i]){
            return i;
        }
    }   
    return -1;
}

int Retorna_Idx_Palavra_ViaDoc(tDocumento* pDoc_Digitadas, int i){
    return pDoc_Digitadas->idx_palavras[i];
}

int *CalculaTodasAsPalavrasNosDocsXY(tDocumento *pDoc_Digitadas, tDocumento *p_Doc, int qtd_palavras_classificador, int *qtd_palavras_total_classificador){
    int i = 0, qtd_palavra_doc2 = 0;
    qtd_palavra_doc2 = p_Doc->qtd_palavras_contidas;
    int *pAux = malloc(sizeof(int) * (qtd_palavras_classificador + qtd_palavra_doc2));

    for(i = 0; i < qtd_palavras_classificador; i++){
        pAux[i] = pDoc_Digitadas->idx_palavras[i];
    }
    *(qtd_palavras_total_classificador) = i;
    

    for(i = 0; i < qtd_palavra_doc2; i++){
        if(!ExistePalavraNoDoc(p_Doc->idx_palavras[i], pDoc_Digitadas)){
            pAux[*(qtd_palavras_total_classificador)] = p_Doc->idx_palavras[i];
            *(qtd_palavras_total_classificador) = *(qtd_palavras_total_classificador) + 1;
        }
    } 
    return pAux;
}

int ExistePalavraNoDoc(int idx_palavra, tDocumento *pDoc){
    int i = 0;
    for(i = 0; i < pDoc->qtd_palavras_contidas; i++){
        if (idx_palavra == pDoc->idx_palavras[i]){
            return 1;
        }
    }
    return 0;
}