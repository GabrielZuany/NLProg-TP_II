#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uteis.h"
#define null 0
#define TRUE 1
#define FALSE 0

typedef struct tPalavra tPalavra;

//inicializacao
tPalavra** Inicializa_Array_Palavra();
tPalavra* Inicializa_Palavra(char str[], int qtd_docs);

//leitura
tPalavra** LeTodosOsArquivosPalavra(FILE* fArquivo_caminho_noticias, tPalavra** pp_Palavras, int qtd_Arquivos);
tPalavra** LeArquivo(FILE* fArquivo, tPalavra **pp_Palavras, int idxDocumento);

//arquivos
FILE* Get_ArquivoNoticia(char caminho[]);

//impressao
void Idx_Palavras(tPalavra** pp_Palavras);
void ImprimePalavra(tPalavra* p_palavra);

//auxiliares 
void ResetaString(char str[]);
int ComparaPalavras(const void *p1, const void *p2);
int PalavraRegistrada(tPalavra **pp_Palavras, int qtdPalavras, char palavra[]);
int Retorna_Idx_Palavra(tPalavra** pp_Palavras, char palavra[]);
int Get_Qtd_Palavras_No_Doc(tPalavra** pp_Palavras, int idx_doc);
int RetornaFrequenciaPalavra(tPalavra* p_palavra, int idx_doc);

//calculos com palavras
void Insere_Frequencias_em_Doc(int frequencia, int idx_doc, tPalavra* p_palavra);
void Insere_TF_IDF_em_Doc(double TF_IDF, int idx_doc, tPalavra *p_palavra);
void Atualiza_Palavra_TF_IDF(tPalavra *p_palavra, int qtdDocumentos);
int Calcula_EmQuantosDocumentosEstaPresente(tPalavra *p_palavra, int qtdDocumentos);
double Calcula_IDF(double n, double DF);

//liberacao de palavras
void LiberaPalavras(tPalavra **pp_Palavras);






#endif