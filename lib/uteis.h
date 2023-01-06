#ifndef _TUTEIS_H_
#define _TUTEIS_H_
#include "lib.h"
typedef int (*Vetor_Get_or_Set_fn)(char acao[], int valor);

void ExibeMenu();
void ExecutaOpcaoUsuario(tDocumento **pp_Docs, tPalavra **pp_Palavras, int opcao);

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
#endif