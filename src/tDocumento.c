#include "../lib/lib.h"

struct tDocumento{
    char nome_documento[100];
    char tipo[10];
    int idx;
    int* idx_palavras;
    int qtd_palavras_contidas;
};


//------- PROGRAMA 1 -----------
void Idx_Documentos(tDocumento** pp_Docs, tPalavra** pp_Palavras){
    int qtd_palavra = Get_Or_Set_Valor('p', "get", null);
    int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    int idx_doc, idx_palavra, frequencia = 0;

    for(idx_doc = 0; idx_doc< qtd_docs; idx_doc++){
        printf("\n\n---------------------------------------------------------------\n\n");
        printf("Palavras no doc idx [%d] '%s'\n", idx_doc, pp_Docs[idx_doc]->nome_documento);
        printf("Tipo de noticia: %s\n\n=================\n\n", pp_Docs[idx_doc]->tipo);

        for(idx_palavra = 0; idx_palavra < pp_Docs[idx_doc]->qtd_palavras_contidas; idx_palavra++){
            
            frequencia = RetornaFrequenciaPalavra(pp_Palavras[(pp_Docs[idx_doc]->idx_palavras[idx_palavra])] , idx_doc);
            printf("Palavra: ");
            ImprimePalavra(pp_Palavras[(pp_Docs[idx_doc]->idx_palavras[idx_palavra])]);
            printf("\nFrequencia: %d\n\n", frequencia);

        }
    }
}



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



//------registrar palavras e montar Struct-------
tDocumento** RegistraPalavrasNosDocumentos(tPalavra** pp_Palavras, tDocumento** pp_Docs){
    int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    int idx_doc;
    char* nome = NULL;
    char* tipo = NULL;
    for(idx_doc=0; idx_doc<qtd_docs; idx_doc++){
        nome = Get_Set_NomeArquivos("get", "", idx_doc);
        tipo = Get_Set_TipoNoticia("get", "", idx_doc);
        pp_Docs[idx_doc] = Inicializa_Doc(pp_Palavras, nome, tipo, idx_doc);
        pp_Docs[idx_doc] = RegistraPalavrasNoDocumentoAtual(pp_Palavras, idx_doc, pp_Docs[idx_doc]);
    }
    return pp_Docs;
}

tDocumento* RegistraPalavrasNoDocumentoAtual(tPalavra** pp_Palavras, int idx_doc, tDocumento* p_Doc){
    int idx_palavra = 0;
    int idx_palavra_doc = 0;
    int qtd_palavras = Get_Or_Set_Valor('p', "get", null);
    
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
    int i = 0, j = 0, k = 0;
    
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
        free(pp_Docs[i]->idx_palavras);
        free(pp_Docs[i]);
    }
    free(pp_Docs);
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
    int i = 0;
    int qtd_docs = Get_Or_Set_Valor('d', "get", null);
    int inicio_max = qtd_docs - 10;
    
    qsort(pp_Docs, qtd_docs, sizeof(tDocumento*), Cmp_Qtd_Palavras);
    
    //imprimir os 10 maiores
    printf("Impressao 10 maiores documentos:\n\n");
    for(i = qtd_docs-1; i >= (qtd_docs-10); i--){
        printf("Doc[%d]: qtd_Palavras: %d\n---\n", i, pp_Docs[i]->qtd_palavras_contidas);
    }
    //imprimir os 10 menores
    printf("Impressao 10 menores documentos:\n\n");
    for(i=0; i<10; i++){
        printf("Doc[%d]: qtd_Palavras: %d\n---\n", i, pp_Docs[i]->qtd_palavras_contidas);
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