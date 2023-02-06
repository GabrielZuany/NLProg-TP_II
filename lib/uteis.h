#ifndef _TUTEIS_H_
#define _TUTEIS_H_
#include "lib.h"

typedef int (*Vetor_Get_or_Set_fn)(char acao[], int valor);

//------------prog1--------------
void ConfereProg1FoiRodado(char entrada[], char modo[]);

//-----------interface----------------
void ExibeMenu();
void ExecutaOpcaoUsuario(tDocumento **pp_Docs, tPalavra **pp_Palavras, int opcao, int k);
void ConfereEntradaValida(char entrada[], char modo[]);


//===================funcoes do menu=====================
//---buscador
/**
 * @brief  le uma linha e mostra as 10 noticias com as maiores somas dos tf-idf's de cada palavra escrita
 * 
 * @param pp_Docs todos os docs
 * @param pp_Palavras todas as palavras
 */
void Buscador(tDocumento** pp_Docs, tPalavra** pp_Palavras);

void LiberaBuscador(double* TF_IDF_docs, double* aux_TF_IDF_docs, int* acessados, int* idx_palavra);


//---classificador
/**
 * @brief O usuario digitara um texto e o programa provera uma estimativa de qual classe de noticias o texto pertence. 
 * 
 * @param pp_Docs documentos registrados.
 * @param pp_Palavras dicionario de palavras registradas.
 * @param k K vizinhos mais proximos (K-Nearest Neighbors - KNN).
 */
void Classificador(tDocumento** pp_Docs, tPalavra** pp_Palavras, int k);
void LiberaAuxiliaresClassificador(tDocumento *pDoc_Digitadas, int *idx_palavra, double *p_frequencia, double *pResultadosCos, double *p_aux_ResultadosCos, int *pAcessados);

//---relatorio palavra
/**
 * @brief Exibe o numero total de documentos em que a palavra aparece, os 10 em que ela aparece com mais frequencia e a frequencia da palavra por classe.
Ambas as listas ordenadas com os itens de maior contagem aparecendo primeiro.
 * 
 * @param pp_Palavras dicionario de palavras registradas.
 * @param pp_Docs documentos registrados.
 */
void RelatorioPalavra(tPalavra **pp_Palavras, tDocumento **pp_Docs);

/**
 * @brief imprime a frequencia da palavra por genero existente
 * 
 * @param p_Palavra palavra escrita pelo usuario
 * @param pp_Docs todos os documentos
 * @param qtd_generos quantidade de generos existentes
 */
void RelatorioPalavra_genero(tPalavra *p_Palavra, tDocumento **pp_Docs, int qtd_generos);

void LiberacaoAuxiliaresRelatorioPalavra(char **pp_TodosGeneros, char **pp_UnicoGeneros, int *freq, int *freq_aux, int *acessado);




//-------------------Calculo cosseno classificador-------------
double CalculaSomatorioNumerador(tDocumento *pDoc_Digitadas, tDocumento *p_Doc,  int qtd_palavras_total_classificador, double *a, double *b);
double CalculaSomatorioDenominador(tDocumento *pDoc_Digitadas, tDocumento *p_Doc, double* p_TFIDF_palavra_em_doc, int qtd_palavras_total_classificador);
double CalculaDistanciaPorCos(tDocumento* pDoc_Digitadas, tDocumento* p_Doc, int idx_doc, tPalavra** pp_Palavras, double* p_frequencia, int qtd_palavras_classificador);

/*
                        Numerador
             ---------------^---------------
             E(tf-idf(w,dx) * tfidf-(w, di))
        ________________________________________

    sqrt[E(tf-idf(w,d1))] * sqrt[E(tf-idf(w, d2))]
    ----------v------------   -----------v------------
         Denominador 1               Denominador 2

*/


//----------Funcoes Get Set -----------------------
/*
*tabela de dispercao usada para armazenamento e acesso de valores muito acessados
durante todo o codigo
*/

void Dispatch_table_Get_Set_inicializa();
int Dispatch_table_executa(char dado, char acao[], int valor);
int Get_Set_QuantidadePalavras(char acao[], int valor);
int Get_Set_QuantidadeDocumento(char acao[], int valor);
int Get_Or_Set_Valor(char dado, char acao[], int valor_registrar);
char* Get_Set_NomeArquivos(char acao[], char diretorio[], int idx);
char* Get_Set_TipoNoticia(char acao[], char tipo[], int idx);


//---------------binario/arquivo----------------
void ArmazenaAuxiliaresEmBinario(FILE * bin, int qtd_Generos);
void LeAuxiliaresBinario(FILE * bin);
int LeQuantidadeDeArquivos(FILE* fArquivo_caminho_noticias);

//---------auxiliares-----------------------
int ConfereTxt(char str[]);

/**
 * @brief Garante que o usuario digite uma opcao dentre as que estao disponiveis no menu.
 * 
 * @return int opcao do usuario.
 */
int GaranteOpcaoValida();

int OpcaoValida(int opcao);
void ResetaString(char str[]);
void ResetaStrComTam(char str[], int tam);

double calculaSomatorio_TF_IDF(tDocumento* p_Doc, tPalavra** pp_Palavras , int *idx_palavra, int qtd_palavras_buscador, int idx_documento);

/**
 * @brief Calcula a frequencia de determinada palavra em cada tipo de noticia.
 * 
 * @param pp_Docs documentos registrados.
 * @param p_Palavra palavra a ser contabilizada por documento.
 * @param genero genero da noticia.
 * @param qtd_docs quantidade de documentos registrados.
 * @return int frequencia da palavra no genero.
 */
int Calcula_Frequencia_Palavra_no_TipoNoticia(tDocumento** pp_Docs, tPalavra* p_Palavra, char genero[], int qtd_docs);

/**
 * @brief verifica se o genero passado existe, caso nao exista, registra-o
 * 
 * @param pp_TodosGeneros todos os generos (com repeticao)
 * @param pp_UnicoGeneros todos os generos (sem repeticao)
 * @param p_genero genero passado para analise
 * @param idx_Docs indice do documento usado
 * @param iNovoGenero indice auxiliar usado no array pp_UnicoGeneros
 * @return iNovoGenero
 */
int Armazena_Genero_Array(char **pp_TodosGeneros, char **pp_UnicoGeneros, char *p_genero, int idx_Docs, int iNovoGenero);



#endif