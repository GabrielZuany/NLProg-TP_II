#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uteis.h"
#define TRUE 1
#define FALSE 0

typedef struct tPalavra tPalavra;

//inicializacao
tPalavra** Inicializa_Array_Palavra();
tPalavra* Inicializa_Palavra(int qtd_docs);

//leitura
tPalavra** LeTodosOsArquivosPalavra(FILE* fArquivo_caminho_noticias, tPalavra** pp_Palavras, int qtd_Arquivos);
FILE* Get_ArquivoNoticia(char caminho[]);
tPalavra** LeArquivo(FILE* fArquivo, tPalavra **pp_Palavras);

void ResetaString(char str[]);

#endif