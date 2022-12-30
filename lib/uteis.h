#ifndef _TUTEIS_H_
#define _TUTEIS_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*Vetor_Get_or_Set_fn)(char acao[], int valor);


int LeQuantidadeDeArquivos(FILE* fArquivo_caminho_noticias);
void ConfereEntradaValida(char entrada[]);



int Get_Set_QuantidadePalavras(char acao[], int valor);

int Get_Set_QuantidadeDocumento(char acao[], int valor);

void Dispatch_table_Get_Set_inicializa();

int Get_Or_Set_Valor(char dado, char acao[], int valor_registrar);




#endif