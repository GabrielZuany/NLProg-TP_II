#include "../lib/tPalavra.h"

struct tPalavra{
    char palavra [50];
    int *pFrenquencia;
};

tPalavra** LeTodosOsArquivosPalavra(FILE* fArquivo_caminho_noticias, tPalavra** pp_Palavras, int qtd_Arquivos){
    int i = 0;
    char linha[100000];
    for(i = 0; i < qtd_Arquivos; i++){
        fscanf(fArquivo_caminho_noticias, "%[^\n]", linha);
        fscanf(fArquivo_caminho_noticias, "%*c");
        
        FILE *fArquivo = Get_ArquivoNoticia(linha);
        pp_Palavras = LeArquivo(fArquivo, pp_Palavras, i);

        //falta armazenar a palavra na struct.
        //tratar docs

        fclose(fArquivo);
    }
    return pp_Palavras;
}

int ComparaPalavras(const void *p1, const void *p2){
    const struct tPalavra *palavra1 = p1;
    const struct tPalavra *palavra2 = p2;
    if(strcmp(palavra1->palavra, palavra2->palavra) == 0){
        return 1;
    }
    return 0;
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

void TEMP_ImprimeStructPalavras(tPalavra** pp_Palavras){
    int i = 0, j = 0;
    int qtd_palavras = Get_Or_Set_Valor('p', "get", ValorArbitrario);
    int qtd_docs = Get_Or_Set_Valor('d', "get", ValorArbitrario);

    for(i=0; i<qtd_palavras; i++){
        printf("palavra[%d]: %s\n", i,pp_Palavras[i]->palavra);
        for(j=0; j<qtd_docs; j++){
            printf("f[%d]: %d\n", j, pp_Palavras[i]->pFrenquencia[j]);
        }
        printf("\n");
    }
}


void Insere_Frequencias_em_Doc(int frequencia, int idx_doc, tPalavra* p_palavra){
    p_palavra->pFrenquencia[idx_doc] = frequencia;
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
    strcpy(p_palavra->palavra, str);

    int i;
    for(i=0; i<qtd_docs; i++){
        Insere_Frequencias_em_Doc(0, i, p_palavra);
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
