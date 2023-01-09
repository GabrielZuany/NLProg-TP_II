#ifndef _TDOCUMENTO_H_
#define _TDOCUMENTO_H_
#include "lib.h"

typedef struct tDocumento tDocumento;

//------PROGRAMA 1--------
void Idx_Documentos(tDocumento** pp_Docs, tPalavra** pp_Palavras);

//------inicializacao e alocacao de memoria------
tDocumento** Inicializa_Array_Docs(int qtd_docs);
tDocumento* Inicializa_Doc(tPalavra** pp_Palavras, char nome[], char tipo[], int idx);

//------auxiliares-------
char* Get_NomeArquivos(tDocumento** pp_Docs, int idx);
char *Get_GeneroArquivo(tDocumento* p_Doc);

//-----------arquivo binario----------
void ArmazenaDocumentosEmBinario(FILE* bin, tDocumento** pp_Docs, int qtd_Arquivos);
void Armazena_UM_DocumentoEmBinario(tDocumento* p_Doc, FILE* bin);
tDocumento** LeDocsBinario(FILE *bin);

//------registrar e montar struct-------------
tDocumento** RegistraPalavrasNosDocumentos(tPalavra** pp_Palavras, tDocumento** pp_Docs);
tDocumento* RegistraPalavrasNoDocumentoAtual(tPalavra** pp_Palavras, int idx_doc, tDocumento* p_Doc);

//------impressao-------
void Teste_ImprimeDocumentos(tDocumento **pp_Docs);

//-----liberar memoria-------
void LiberaDocs(tDocumento** pp_Docs);
void LiberaAuxGenero(char **pp_auxGenero, int qtd);

//------relatório documentos------
void RelatorioDocumento(tDocumento** pp_Docs);
//int Cmp_Idx_Docs(const void *p1, const void *p2);
int Cmp_Qtd_Palavras(const void *p1, const void *p2);

#endif