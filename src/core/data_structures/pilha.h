#pragma once
#include "../models.h"
#include <stdbool.h>

typedef struct str_Nodo Nodo;

/**
 * @brief Representação de um nodo da pilha, que contem um ingrediente e um ponteiro para o proximo nodo
 */
struct str_Nodo {
    Nodo *prox;
    char ingrediente;
};

/**
 * @brief Representação da pilha, que contem um ponteiro para o nodo do topo
 */

typedef struct {
    Nodo *topo;
} PilhaHamburger;

/**
 * @brief Inicializa uma pilha
 * @param[in, out] p ponteiro para o topo da pilha (ainda não inicializado) 
 */
void inicializa(PilhaHamburger *p);

/**
 * @brief 
 * @param[in] p ponteiro para o topo da pilha 
 * @return true a pilha está vazia
 * @return false a pilha não está vazia
 */
bool estaVazia(const PilhaHamburger *p);

/**
 * @brief Coloca um ingrediente no topo da pilha
 * @param [in, out] p ponteiro para o topo da pilha
 * @param [in] ingrediente ingrediente à ser adicionado ao topo da pilha
 * @return true a operação foi realizada com sucesso
 * @return false não foi possivel realizar a operação
 */
bool push(PilhaHamburger *p, char ingrediente);

/**
 * @brief  Retira um ingrediente do topo da pilha
 * @param [in, out] p ponteiro para o topo da pilha
 * @param [in, out] ingrediente ponteiro para um char, ao final da execução ele terá o valor do char removido na função 
 * @return true a operação foi realizada com sucesso 
 * @return false não foi possivel realizar a operação
 */

bool pop(PilhaHamburger *p, char *ingrediente);

/**
 * @brief Descobre qual é o elemento do topo da pilha
 * @param [in] p ponteiro para o topo da pilha 
 * @param [in, out] ingrediente ponteiro para um char, ao final da execução ele terá o valor do char removido na função 
 * @return true a operação foi realizada com sucesso, topo atribuído ao ingrediente
 * @return false a ação não pôde ser realizada
 */

bool topo(const PilhaHamburger *p, char *ingrediente);

/**
 * @brief Devolve o tamanho da pilha
 * @param [in] p ponteiro para o topo da pilha 
 * @return int tamanho da pilha
 */

int tamanho(const PilhaHamburger *p);