#ifndef _TUTEIS_H_
#define _TUTEIS_H_
#include "lib.h"
typedef int (*Vetor_Get_or_Set_fn)(char acao[], int valor);

void ExibeMenu();
void ExecutaOpcaoUsuario(tDocumento **pp_Docs, tPalavra **pp_Palavras, int opcao, int k);
int LeQuantidadeDeArquivos(FILE* fArquivo_caminho_noticias);
void ConfereEntradaValida(char entrada[], char modo[]);
void ResetaString(char str[]);
void ResetaStrComTam(char str[], int tam);
void Dispatch_table_Get_Set_inicializa();
int Get_Set_QuantidadePalavras(char acao[], int valor);
int Get_Set_QuantidadeDocumento(char acao[], int valor);
int Get_Or_Set_Valor(char dado, char acao[], int valor_registrar);
char* Get_Set_NomeArquivos(char acao[], char diretorio[], int idx);
char* Get_Set_TipoNoticia(char acao[], char tipo[], int idx);
int ConfereTxt(char str[]);
void ArmazenaAuxiliaresEmBinario(FILE * bin, int qtd_Generos);
void LeAuxiliaresBinario(FILE * bin);
void RelatorioPalavra(tPalavra **pp_Palavras, tDocumento **pp_Docs);
void RelatorioPalavra_genero(tPalavra *p_Palavra, tDocumento **pp_Docs, int qtd_generos);
int VerificaGeneroExiste(char tipo[], char **pp_auxGenero, int idx_doc);
int Armazena_Genero_Array(char **pp_TodosGeneros, char **pp_UnicoGeneros, char *p_genero, int idx_Docs, int iNovoGenero);
void ConfereProg1FoiRodado(char entrada[], char modo[]);
void Buscador(tDocumento** pp_Docs, tPalavra** pp_Palavras);
int Cmp_TF_IDF(const void* f1, const void* f2);
int Calcula_Frequencia_Palavra_no_TipoNoticia(tDocumento** pp_Docs, tPalavra* p_Palavra, char genero[], int qtd_docs);
int Cmp_Freq(const void* f1, const void* f2);

double calculaSomatorio_TF_IDF(tDocumento* p_Doc, tPalavra** pp_Palavras , int *idx_palavra, int qtd_palavras_buscador, int idx_documento);



void Classificador(tDocumento** pp_Docs, tPalavra** pp_Palavras, int k);
double CalculaDistanciaPorCos(tDocumento* pDoc_Digitadas, tDocumento* p_Doc, int idx_doc, tPalavra** pp_Palavras, double* p_frequencia, int qtd_palavras_classificador);
int VerificaPalavraJaDigitada(int* idx_palavra, int idx_aux, int qtd_palavras_classificador);
double CalculaSomatorioNumerador(tDocumento *pDoc_Digitadas, tDocumento *p_Doc,  int qtd_palavras_classificador, double *a, double *b);
double CalculaSomatorioDenominador(tDocumento *pDoc_Digitadas, tDocumento *p_Doc, double* p_TFIDF_palavra_em_doc, int qtd_palavras_classificador);
int Cmp_Distancia_Docs(const void *d1, const void *d2);
/*
                            X
             ---------------^---------------
             E(tf-idf(w,dx) * tfidf-(w, di))
        ________________________________________

    sqrt[E(tf-idf(w,d1))] * sqrt[E(tf-idf(w, d2))]
    ----------v------------   -----------v------------
              y1                        y2

*/

#endif