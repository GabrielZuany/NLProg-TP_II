#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_
#include "lib.h"


typedef struct tPalavra tPalavra;

//-----------inicializacao------------
tPalavra** Inicializa_Array_Palavra();
tPalavra* Inicializa_Palavra(char str[], int qtd_docs, int idxPalavra);



//---------------leitura------------------
/**
 * @brief A partir do arquivo .txt contendo o caminho das notícias, abre cada uma e monta o Idx Palavras (dicionário contendo todas as palavras diferentes dos documentos dados).
 * 
 * @param fArquivo_caminho_noticias arquivo .txt contendo o caminho das notícias.
 * @param pp_Palavras Array de struct tipo tPalavra.
 * @param qtd_Arquivos quantidade de arquivos a serem lidos.
 * @param argv comando passado pelo terminal.
 * @return tPalavra** dicionário com as palavras contidas em todos os documentos.
 */
tPalavra** LeTodosOsArquivosPalavra(FILE* fArquivo_caminho_noticias, tPalavra** pp_Palavras, int qtd_Arquivos, char argv[]);

/**
 * @brief A partir do arquivo de notícia, armazena todas as palavras contidas nele (sem repetir).
 * 
 * @param fArquivo arquivo notícia.
 * @param pp_Palavras Array de palavras (dicionário).
 * @param idxDocumento índice do documento que está sendo lido.
 * @return tPalavra** Array de palavras (dicionário), atualizado.
 */
tPalavra** LeArquivo(FILE* fArquivo, tPalavra **pp_Palavras, int idxDocumento);

/**
 * @brief A partir de uma determinada linha do arquivo que contém o caminho para todas as notícias e o argumento passado pelo terminal, retorna esse arquivo.
 * 
 * @param caminho caminho do arquivo (relativo --> "train/noticia.txt")
 * @param argv pasta cujos arquivos serão lidos (--> "datasets/tiny/train.txt")
 * @return FILE* arquivo que será lido.
 */
FILE* Get_ArquivoNoticia(char caminho[], char argv[]);



//------------impressao---------------
void Idx_Palavras(tPalavra** pp_Palavras);
void ImprimePalavra(tPalavra* p_palavra);
void ImprimePalavras(tPalavra **pp_Palavras);



//-----------auxiliares--------------------- 
void ResetaString(char str[]);
//int ComparaPalavras(const void *p1, const void *p2);
int Acesso_Idx_Palavra(tPalavra* palavra);
int PalavraRegistrada(tPalavra **pp_Palavras, int qtdPalavras, char palavra[]);
int Retorna_Idx_Palavra(tPalavra** pp_Palavras, char palavra[]);
tPalavra* Retorna_Palavra(tPalavra** pp_Palavras, char palavra[], int alterado);
void OrganizaPalavrasPorIndice(tPalavra **pp_Palavras, int tam);
int Get_Qtd_Palavras_No_Doc(tPalavra** pp_Palavras, int idx_doc);
int RetornaFrequenciaPalavra(tPalavra* p_palavra, int idx_doc);
int Get_FrequenciaPalavraNoDoc(tPalavra* p_Palavra, int pos);
double Acesso_TF_IDF_NoDocX(tPalavra* p_palavra, int idx_documento);
void ZeraPonteiroDeInteiro(int *p, int tam);
int VerificaPalavraJaDigitada(int* idx_palavra, int idx_aux, int qtd_palavras_classificador);

/**
 * @brief Verifica se a palavra dada consta no dicionário. Necessário para adicionar palavras sem repetir no dicionário.
 * 
 * @param pp_Palavras Dicionário.
 * @param nome palavra dada.
 * @return int TRUE se ela existe, FALSE se não existe.
 */
int VerificaPalavraExiste(tPalavra **pp_Palavras, char nome[]);



//-------------calculos com palavras---------------
void Insere_Frequencias_em_Doc(int frequencia, int idx_doc, tPalavra* p_palavra);
void Insere_TF_IDF_em_Doc(double TF_IDF, int idx_doc, tPalavra *p_palavra);

/**
 * @brief Função responsável por atualizar o TD-IDF daquela palavra, acessando os parâmetros necessários e fazendo o cálculo própriamente dito do TF-IDF.
 * 
 * @param p_palavra palavra a qual receberá o valor do cálculo para cada documento.
 * @param qtdDocumentos quantidade de documentos.
 */
void Atualiza_Palavra_TF_IDF(tPalavra *p_palavra, int qtdDocumentos);

/**
 * @brief Compara a tf-idf para utilizar a funcao de busca binaria (bsearch) ou de ordenacao (qsort).
 * 
 * @param f1 ponteiro do tipo double (elemento 1).
 * @param f2 ponteiro do tipo double (elemento 2).
 * @return = 0 caso sejam iguais; < 0 caso o primeiro seja maior que o segundo; > 0 caso o primeiro seja menor que o segundo.
 */
int Cmp_TF_IDF(const void* f1, const void* f2);

int Calcula_EmQuantosDocumentosEstaPresente(tPalavra *p_palavra, int qtdDocumentos);
double Calcula_TF_IDF(double TF,double n, double DF);



//------------arquivos binarios--------------
void ArmazenaPalavrasEmBinario(FILE* bin, tPalavra** pp_Palavras, int qtd_palavras);
void Armazena_UMA_PalavraEmBinario(tPalavra* p_Palavra, FILE* bin);
tPalavra** LeDicionarioBinario(FILE *bin);



//---------liberacao de palavras--------
void LiberaPalavras(tPalavra **pp_Palavras);



//---------relatorio palavra-------------


int Cmp_frequencia_Palavras(const void *p1, const void *p2);

/**
 * @brief Compara a frequencia para utilizar a funcao de busca binaria (bsearch) ou de ordenacao (qsort).
 * 
 * @param f1 ponteiro do tipo int (elemento 1).
 * @param f2 ponteiro do tipo int (elemento 2).
 * @return = 0 caso sejam iguais; < 0 caso o primeiro seja maior que o segundo; > 0 caso o primeiro seja menor que o segundo.
 */
int Cmp_Freq(const void* f1, const void* f2);


/**
 * @brief Imprime os 10 documentos com maior frequencia da palavra digitada (em RelatorioPalavra na uteis.c). 
 * 
 * @param pp_Palavras dicionario de palavras.
 * @param qtd_docs quantidade de documentos lidos.
 * @param idx_palavra índice da palavra digitada.
 */
void RelatorioPalavra_frequencia(tPalavra **pp_Palavras, int qtd_docs, int idx_palavra);

/**
 * @brief A partir de um vetor de frequencias ordenado, busca o documento correspondente a frquencia na posição i.
 * 
 * @param p_palavra palavra cuja frequencia em cada documento vai ser acessada.
 * @param frequencia frequencia que está procurando.
 * @param pAcessada vetor de inteiros (0, 1) para indicar que aquele documento já foi acessado ou não. Assim evita-se que seja retornado o mesmo documento mais de uma vez.
 * @param qtd_docs quantidade de documentos a serem analisados.
 * @return int indice do documento.
 */
int EncontraDocumentoComFrequenciaX(tPalavra *p_palavra, int frequencia, int *pAcessada, int qtd_docs);


int cmp_palavra_nome_bsearch(const void *a, const void*b);
int cmp_palavra_nome_qsort(const void *a, const void *b);

#endif