#ifndef _TDOCUMENTO_H_
#define _TDOCUMENTO_H_
#include "lib.h"

typedef struct tDocumento tDocumento;

//------PROGRAMA 1--------
void Idx_Documentos(tDocumento** pp_Docs, tPalavra** pp_Palavras);

//------inicializacao e alocacao de memoria------
tDocumento** Inicializa_Array_Docs(int qtd_docs);
tDocumento* Inicializa_Doc(tPalavra** pp_Palavras, char nome[], char tipo[], int idx);
tDocumento* InicializaDocumentoClassificador(int* idx_palavra, int qtd_palavras_classificador);

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
void ImprimeResultadoClassificador(tDocumento** pp_Docs, double* pResultadosCos, double* p_aux_ResultadosCos, int* pAcessados, int qtd_docs, int k);
void Teste_ImprimeDocumentos(tDocumento **pp_Docs);
void ImprimeUmDocumento(tDocumento *p_doc);

//-----liberar memoria-------
void LiberaDocs(tDocumento** pp_Docs);
void LiberaAuxGenero(char **pp_auxGenero, int qtd);
void LiberaDocumento(tDocumento* Doc);

//------relatório documentos------
void RelatorioDocumento(tDocumento** pp_Docs);
//int Cmp_Idx_Docs(const void *p1, const void *p2);
int Cmp_Qtd_Palavras(const void *p1, const void *p2);


void AdicionaPresencaEmGenero(char* genero, char** pp_UnicoGeneros, int* pPresencasEmCadaGenero, int qtd_generos);
void ImprimeGeneroComMaisPresencas(char **pp_UnicoGeneros, int *pPresencasEmCadaGenero, int qtd_generos, int k);
int ExistePalavraEmDoc(int idx_palavra, tDocumento* p_Doc);
int Retorna_Idx_Palavra_ViaDoc(tDocumento* pDoc_Digitadas, int i);

#endif