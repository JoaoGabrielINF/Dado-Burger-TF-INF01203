#pragma once
#include <stdbool.h>

typedef struct str_NodoPilha NodoPilha;

/**
 * @brief Representação de um NodoPilha da pilha, que contem um ingrediente e um ponteiro para o proximo NodoPilha
 */
struct str_NodoPilha {
    NodoPilha *prox; /**< Ponteiro para o próximo nodo */
    char ingrediente; /**< Ingrediente deste nodo */
    bool ingrediente_correto; /**< Verificação se este nodo está na ordem correta */
};

/**
 * @brief Representação da pilha, que contem um ponteiro para o NodoPilha do topo
 */

typedef struct {
    NodoPilha *topo; /**< Ponteiro para o topo da pilha */
} PilhaHamburger;

/**
 * @brief Inicializa uma pilha
 * @param[in, out] p ponteiro para o topo da pilha (ainda não inicializado) 
 */

void inicializaPilha(PilhaHamburger *p);

/**
 * @brief Verifica se a pilha não contém ingredientes.
 * @param[in] p ponteiro para o topo da pilha 
 * @return true a pilha está vazia
 * @return false a pilha não está vazia
 */

bool estaVaziaPilha(const PilhaHamburger *p);

/**
 * @brief Coloca um ingrediente no topo da pilha
 * @param [in, out] p ponteiro para o topo da pilha
 * @param [in] ingrediente ingrediente à ser adicionado ao topo da pilha
 * @return true a operação foi realizada com sucesso
 * @return false não foi possivel realizar a operação
 */

bool pushPilha(PilhaHamburger *p, char ingrediente);

/**
 * @brief  Retira um ingrediente do topo da pilha
 * @param [in, out] p ponteiro para o topo da pilha
 * @param [in, out] ingrediente_removido ponteiro que receberá o ingrediente removido
 * @return true a operação foi realizada com sucesso 
 * @return false não foi possivel realizar a operação
 */

bool popPilha(PilhaHamburger *p, char *ingrediente_removido);

/**
 * @brief Descobre qual é o elemento do topo da pilha
 * @param [in] p ponteiro para o topo da pilha 
 * @param [in, out] ingrediente ponteiro para um char, ao final da execução ele terá o ingrediente do char removido na função 
 * @return true a operação foi realizada com sucesso, topo atribuído ao ingrediente
 * @return false a ação não pôde ser realizada
 */

bool topoPilha(const PilhaHamburger *p, char *ingrediente);

/**
 * @brief Devolve o tamanho da pilha
 * @param [in] p ponteiro para o topo da pilha 
 * @return int tamanho da pilha
 */

int tamanhoPilha(const PilhaHamburger *p);

/**
 * @brief Função que reinicia a pilha até o ponteiro do topo ficar null
 * @param p  Estado atual da pilha
 */
void reiniciaPilha(PilhaHamburger *p);