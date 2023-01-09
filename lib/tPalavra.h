#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_
#include "lib.h"


typedef struct tPalavra tPalavra;

//inicializacao
tPalavra** Inicializa_Array_Palavra();
tPalavra* Inicializa_Palavra(char str[], int qtd_docs, int idxPalavra);

//leitura
tPalavra** LeTodosOsArquivosPalavra(FILE* fArquivo_caminho_noticias, tPalavra** pp_Palavras, int qtd_Arquivos, char argv[]);
tPalavra** LeArquivo(FILE* fArquivo, tPalavra **pp_Palavras, int idxDocumento);

//arquivos
FILE* Get_ArquivoNoticia(char caminho[], char argv[]);

//impressao
void Idx_Palavras(tPalavra** pp_Palavras);
void ImprimePalavra(tPalavra* p_palavra);
void Teste_ImprimePalavras(tPalavra **pp_Palavras);

//auxiliares 
void ResetaString(char str[]);
int ComparaPalavras(const void *p1, const void *p2);
int PalavraRegistrada(tPalavra **pp_Palavras, int qtdPalavras, char palavra[]);
int Retorna_Idx_Palavra(tPalavra** pp_Palavras, char palavra[]);
int Get_Qtd_Palavras_No_Doc(tPalavra** pp_Palavras, int idx_doc);
int RetornaFrequenciaPalavra(tPalavra* p_palavra, int idx_doc);
int VerificaPalavraExiste(tPalavra **pp_Palavras, char nome[]);

//calculos com palavras
void Insere_Frequencias_em_Doc(int frequencia, int idx_doc, tPalavra* p_palavra);
void Insere_TF_IDF_em_Doc(double TF_IDF, int idx_doc, tPalavra *p_palavra);
void Atualiza_Palavra_TF_IDF(tPalavra *p_palavra, int qtdDocumentos);
int Calcula_EmQuantosDocumentosEstaPresente(tPalavra *p_palavra, int qtdDocumentos);
double Calcula_IDF(double n, double DF);

//arquivos binarios
void ArmazenaPalavrasEmBinario(FILE* bin, tPalavra** pp_Palavras, int qtd_palavras);
void Armazena_UMA_PalavraEmBinario(tPalavra* p_Palavra, FILE* bin);
tPalavra** LeDicionarioBinario(FILE *bin);

//liberacao de palavras
void LiberaPalavras(tPalavra **pp_Palavras);

//relatorio palavra
void RelatorioPalavra(tPalavra **pp_Palavras);
int Cmp_frequencia_Palavras(const void *p1, const void *p2);
void RelatorioPalavra_frequencia(tPalavra **pp_Palavras, int qtd_docs, int idx_palavra);
void ZeraPonteiroDeInteiro(int *p, int tam);
int EncontraDocumentoComFrequenciaX(tPalavra *p_palavra, int frequencia, int *pAcessada, int qtd_docs);


#endif