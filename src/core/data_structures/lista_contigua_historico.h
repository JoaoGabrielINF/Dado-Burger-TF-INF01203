#ifndef LISTAENC_H
#define LISTAENC_H
#include <cliente.h>

typedef struct str_Nodo Nodo;

struct str_Nodo {
    Nodo *prox;
    Pedido dado;
};

typedef struct {
    Nodo *ini;
} ListaEnc;

/**
 * @brief Inicializa a lista.
 * @param [out] lista ponteiro para o início da lista a ser inicializada.
 */
void inicializar(ListaEnc *lista);

/**
 * @brief Calcula o tamanho da lista passada.
 * @param lista ponteiro para o início da lista que se quer obter o tamanho.
 * @return Tamanho da lista fornecida.
 */
int tamanho(const ListaEnc *lista);

/**
 * @brief Busca o pedido na lista com base no código fornecido.
 * @param [in] lista ponteiro para o início da lista em que se quer buscar o pedido.
 * @param [in] cod código do pedido que se quer buscar na lista.
 * @return Pedido correspondente ao código fornecido na lista passada.
 */
Pedido buscar(const ListaEnc *lista, int cod);

/**
 * @brief Insere o pedido no início da lista.
 * @param [in, out] lista ponteiro para o início da lista em que se quer inserir o pedido.
 * @param [in] pedido pedido que se quer inserir na lista.
 * @return 1 caso o pedido seja inserido com sucesso.
 * @return 0 caso ocorra erro na alocação do espaço para o novo pedido.
 */
int inserirInicio(ListaEnc *lista, const Pedido pedido);

/**
 * @brief Insere o pedido no fim da lista.
 * @param [in, out] lista ponteiro para o início da lista em que se quer inserir o pedido.
 * @param [in] pedido pedido que se quer inserir na lista.
 * @return 1 caso o pedido seja inserido com sucesso.
 * @return 0 caso ocorra erro na alocação do espaço para o novo pedido.
 */
int inserirFim(ListaEnc *lista, const Pedido pedido);

/**
 * @brief Remove o pedido informado da lista.
 * @param [in, out] lista ponteiro para o início da lista da qual se quer remover o pedido.
 * @param [in] cod código do pedido que se quer remover da lista.
 * @return 1 caso seja removido com sucesso.
 * @return 0 caso haja erro na remoção do pedido.
 */
int removerPorCod(ListaEnc *lista, int cod);

/**
 * @brief Destrói a lista informada.
 * @param [in, out] lista ponteiro para o início da lista a ser destruída.
 */
void destruir(ListaEnc *lista);

#endif