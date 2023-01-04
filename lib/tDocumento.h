#ifndef _TDOCUMENTO_H_
#define _TDOCUMENTO_H_
#define null 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/tPalavra.h"
#include "../lib/uteis.h"

typedef struct tDocumento tDocumento;

//------PROGRAMA 1--------
void Idx_Documentos(tDocumento** pp_Docs, tPalavra** pp_Palavras);

//------inicializacao e alocacao de memoria------
tDocumento** Inicializa_Array_Docs(int qtd_docs);
tDocumento* Inicializa_Doc(tPalavra** pp_Palavras, char nome[], char tipo[], int idx);

//------auxiliares-------
char* Get_NomeArquivos(tDocumento** pp_Docs, int idx);

//-----------arquivo binario----------
void ArmazenaDocumentosEmBinario(FILE* bin, tDocumento** pp_Docs, int qtd_Arquivos);
void Armazena_UM_DocumentoEmBinario(tDocumento* p_Doc, FILE* bin);
void LeDocsBinario(FILE *bin);

//------registrar e montar struct-------------
tDocumento** RegistraPalavrasNosDocumentos(tPalavra** pp_Palavras, tDocumento** pp_Docs);
tDocumento* RegistraPalavrasNoDocumentoAtual(tPalavra** pp_Palavras, int idx_doc, tDocumento* p_Doc);

//-----liberar memoria-------
void LiberaDocs(tDocumento** pp_Docs);

#endif