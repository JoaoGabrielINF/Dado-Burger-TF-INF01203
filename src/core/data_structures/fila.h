#pragma once
#include "../models.h"

typedef struct str_Nodo Nodo;

/**
 * @brief Representação de um nodo da fila, contem um ponteiro para o proximo nodo da fila e um cliente.
 */
struct str_Nodo {
    Nodo *prox; /**<Ponteiro para o próximo nodo da fila */
    Cliente cliente; /**<Cliente do nodo atual */
};

/**
 * @brief Representação da fila de clientes, contem um ponteiro para o inicio da fila e um ponteiro para o final da fila
 */
typedef struct {
    Nodo *frente; /**<Ponteiro para o primeiro elemento da fila */
    Nodo *final; /**<Ponteiro para o ultimo elemento da fila */
} FilaClientes;

/**
 * @brief Inicializa os ponteiros da fila
 * @param [in, out] f ponteiros de inicio e fim da fila
 */

void inicializa(FilaClientes *f);

/**
 * @brief Descobre se a fila está vazia
 * @param f ponteiros de inicio e fim da fila
 * @return true a fila está vazia
 * @return false a fila não está vazia 
 */

bool estaVazia(const FilaClientes *f);

/**
 * @brief Coloca um cliente na fila
 * @param f ponteiros de inicio e fim da fila
 * @param cliente cliente à ser inserido na fila
 * @return true cliente alocado no fim da fila com sucesso
 * @return false a ação não pôde ser realizada
 */

bool enqueue(FilaClientes *f, const Cliente *cliente);

/**
 * @brief Retira um cliente do inicio da fila
 * @param f ponteiros de inicio e fim da fila
 * @param cliente cliente à ser retirado da fila
 * @return true cliente retirado da fila com sucesso
 * @return false a ação não pôde ser realizada
 */

bool dequeue(FilaClientes *f, Cliente *cliente);

/**
 * @brief Descobre qual é o primeiro cliente da fila
 * @param f ponteiros de inicio e fim da fila
 * @param cliente ponteiro que recebe cliente da frente na fila
 * @return true a fila possui clientes
 * @return false a ação não pôde ser realizada
 */

bool frente(const FilaClientes *f, Cliente *cliente);

/**
 * @brief Descobre o tamanho da fila
 * @param f ponteiros de inicio e fim da fila
 * @return int tamanho da fila
 */

int tamanho(const FilaClientes *f);
