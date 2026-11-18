#pragma once
#include <stdbool.h>

typedef struct str_NodoLista NodoLista;

/**
 * @brief Representação de um nodo da lista, contem um ponteiro para o proximo nodo e um ingrediente
 */
struct str_NodoLista {
    NodoLista *prox; /**< Ponteiro para o próximo nodo da lista */
    char ingrediente; /**< Caractere do ingrediente do nodo */
};

/**
 * @brief Representação da lista, contem o ponteiro para o primeiro elemento da lista
 * 
 */
typedef struct {
    NodoLista *ini;  /**< Ponteiro para o início da lista */
} ListaReceita;

/**
 * @brief Inicializa a lista - ponteiro inicial aponta para NULL
 * @param[in, out] lista ponteiro para o inicio da lista encadeada
 */

void  inicializarLista(ListaReceita *lista);

/**
 * @brief Imprime os ingredientes da lista 
 * @param[in] lista ponteiro para o inicio da lista encadeada
 */

void imprimirLista(const ListaReceita *lista);

/**
 * @brief Busca um ingrediente na lista
 * @param[in] lista ponteiro para o inicio da lista encadeada
 * @param[in] ingrediente ingrediente a ser procutado 
 * @return true ingrediente encontrado na lista
 * @return false ingrediente não foi encontrado na lista
 */

bool buscarLista(const ListaReceita *lista, char ingrediente);

/**
 * @brief Insere um ingrediente no início da lista 
 * @param[in, out] lista ponteiro para o inicio da lista encadeada
 * @param[in] ingrediente ingrediente a ser inserido
 * @return true inserção ocorreu com sucesso
 * @return false não foi possível realizar a inserção
 */

bool inserirInicioLista(ListaReceita *lista, char ingrediente);

/**
 * @brief Insere um ingrediente no fim da lista
 * @param[in] lista ponteiro para o inicio da lista encadeada
 * @param[in] ingrediente ingrediente a ser inserido
 * @return true inserção ocorreu com sucesso
 * @return false não foi possível realizar a inserção
 */

bool inserirFimLista(ListaReceita *lista, char ingrediente);

/**
 * @brief Remove um ingrediente pelo caractere informado no parâmetro
 * @param[in, out] lista ponteiro para o inicio da lista  encadeada 
 * @param[in] ingrediente caractere do ingrediente a ser removido
 * @return true a remoção ocorreu com sucesso
 * @return false não foi possível realizar a remoção
 */

bool removerPorCharLista(ListaReceita *lista, char ingrediente);

/**
 * @brief Destrói a lista 
 * @param[in, out] lista ponteiro para o inicio da lista encadeada
 */

void destruirLista(ListaReceita *lista);

/**
 * @brief Descobre o tamanho da lista
 * @param[in] lista ponteiro para o inicio da lista encadeada
 * @return int tamanho da lista
 */
int tamanhoLista(const ListaReceita *lista);