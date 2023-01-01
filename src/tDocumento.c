#include "../lib/tDocumento.h"

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