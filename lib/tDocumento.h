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

//------auxiliares---------
char* Get_NomeArquivos(tDocumento** pp_Docs, int idx);
char *Get_GeneroArquivo(tDocumento* p_Doc);
int ExistePalavraEmDoc(int idx_palavra, tDocumento* p_Doc);
int Retorna_Idx_Palavra_ViaDoc(tDocumento* pDoc_Digitadas, int i);
int ExistePalavraNoDoc(int idx_palavra, tDocumento *pDoc);
int VerificaGeneroExiste(char tipo[], char **pp_auxGenero, int idx_doc);

/**
 * @brief Compara a distancia entre docs para utilizar a funcao de busca binaria (bsearch) ou de ordenacao (qsort) no resultado dos cossenos.
 * 
 * @param d1 ponteiro do tipo double (elemento 1).
 * @param d2 ponteiro do tipo double (elemento 2).
 * @return = 0 caso sejam iguais; < 0 caso o primeiro seja maior que o segundo; > 0 caso o primeiro seja menor que o segundo.
 */
int Cmp_Distancia_Docs(const void *d1, const void *d2);

//------classificador------
/**
 * @brief adiciona uma presenca no genero passado
 * 
 * @param genero str genero
 * @param pp_UnicoGeneros array contendo todos os generos
 * @param pPresencasEmCadaGenero array contendo a presenca em cada genero
 * @param qtd_generos quantidade total de generos
 */
void AdicionaPresencaEmGenero(char* genero, char** pp_UnicoGeneros, int* pPresencasEmCadaGenero, int qtd_generos);

/**
 * @brief recebe dois documentos e calcula uniao da quantidade de palavras de ambos os documentos(sem repeticao)
 * 
 * @param pDoc_Digitadas documento criado a partir do texto escrito pelo usuario
 * @param p_Doc documento ja registrado no prog1
 * @param qtd_palavras_classificador quantidade de palavras contidas no pDoc_Digitadas
 * @param qtd_palavras_total_classificador quantidade de palavras contida na uniao dos documentos passados
 * @return qtd_palavras_total_classificador
 */
int *CalculaTodasAsPalavrasNosDocsXY(tDocumento *pDoc_Digitadas, tDocumento *p_Doc, int qtd_palavras_classificador, int *qtd_palavras_total_classificador);


//-----------arquivo binario----------
void ArmazenaDocumentosEmBinario(FILE* bin, tDocumento** pp_Docs, int qtd_Arquivos);
void Armazena_UM_DocumentoEmBinario(tDocumento* p_Doc, FILE* bin);
tDocumento** LeDocsBinario(FILE *bin);


//------registrar e montar struct-------------

tDocumento* RegistraPalavrasNoDocumentoAtual(tPalavra** pp_Palavras, int idx_doc, tDocumento* p_Doc);

/**
 * @brief Monta o array do tipo tDocumento** inserindo o nome, tipo, palavras e indice dos docs.
 * 
 * @param pp_Palavras dicionário de palavras.
 * @param pp_Docs array de structs do tipo tDocumento, na qual estarão todas as informações dos docs (cada doc em uma posição do array).
 * @return tDocumento** array de structs do tipo tDocumento* inicializadas e registradas.
 */
tDocumento** RegistraPalavrasNosDocumentos(tPalavra** pp_Palavras, tDocumento** pp_Docs);



//------impressao-------

/**
 * @brief Imprime o resultado do cálculo do cosseno para cada documento.
 * 
 * @param pp_Docs Todos os documentos a serem calculados.
 * @param pResultadosCos ponteiro que armazena os resultados de cada cálculo de cosseno.
 * @param p_aux_ResultadosCos ponteiro auxiliar (necessário para manter uma referência de pResultadosCos).
 * @param pAcessados ponteiro que armazena o status (acessados ou não acessados) de cada elemento do ponteiro de resultado de cossenos.
 * @param qtd_docs quantidade de documentos que serão calculados.
 * @param k valor passado pelo argumento da linha de comando.
 */
void ImprimeResultadoClassificador(tDocumento** pp_Docs, double* pResultadosCos, double* p_aux_ResultadosCos, int* pAcessados, int qtd_docs, int k);

/**
 * @brief encontra o(s) genero(s) com maior presencas nos k primeiros documentos e imprime-os
 * 
 * @param pp_UnicoGeneros array com todos os generos(sem repeticao)
 * @param pPresencasEmCadaGenero array que armazena a quantidade de presencas em cada genero(sua posicao no array esta ligada com a posicao
 no array do pp_UnicoGeneros)
 * @param qtd_generos quantidade de generos existentes
 * @param k valor passado como argumento
 */
void ImprimeGeneroComMaisPresencas(char **pp_UnicoGeneros, int *pPresencasEmCadaGenero, int qtd_generos, int k);

void ImprimeDocumentos(tDocumento **pp_Docs);
void ImprimeUmDocumento(tDocumento *p_doc);

//-----liberar memoria-------
void LiberaDocs(tDocumento** pp_Docs);
void LiberaAuxGenero(char **pp_auxGenero, int qtd);
void LiberaDocumento(tDocumento* Doc);



//------relatorio documentos------

/**
 * @brief recebe todos os documentos e ordena-os de forma crescente(quantidade de palavra como criterio) 
 *imprime os 10 primeiros e os 10 ultimos(top 10 menores e maiores)
 * @param pp_Docs todos os documentos
 */
void RelatorioDocumento(tDocumento** pp_Docs);

/**
 * @brief funcao de ordenacao passada no qsort para ordenar por idx como criterio.
 * 
 * @param p1 ponteiro do tipo tDocumento (elemento 1).
 * @param p2 ponteiro do tipo tDocumento (elemento 2).
 * @return  > 0 caso doc1 maior q doc2; < 0 caso doc1 menor q doc2; = 0 caso doc1 igual a doc2.
 */
int Cmp_Idx_Docs(const void *p1, const void *p2);

/**
 * @brief Compara a quantdade de palavras para utilizar a função de busca binária (bsearch) ou de ordenação (qsort).
 * 
 * @param p1 ponteiro do tipo tDocumento (elemento 1).
 * @param p2 ponteiro do tipo tDocumento (elemento 2).
 * @return = 0 caso sejam iguais; > 0 caso o primeiro seja maior que o segundo; < 0 caso o primeiro seja menor que o segundo.
 */
int Cmp_Qtd_Palavras(const void *p1, const void *p2);


#endif