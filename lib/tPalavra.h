#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uteis.h"
#define ValorArbitrario 0
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
void TEMP_ImprimeStructPalavras(tPalavra** pp_Palavras);

//auxiliares 
void ResetaString(char str[]);
int ComparaPalavras(const void *p1, const void *p2);
int PalavraRegistrada(tPalavra **pp_Palavras, int qtdPalavras, char palavra[]);
int Retorna_Idx_Palavra(tPalavra** pp_Palavras, char palavra[]);

//calculos com palavras
void Insere_Frequencias_em_Doc(int frequencia, int idx_doc, tPalavra* p_palavra);


#endif