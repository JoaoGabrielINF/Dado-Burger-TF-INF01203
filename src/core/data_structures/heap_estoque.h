#pragma once
#include "../alimento.h"
#include <stdbool.h>
/** Capacidade máxima do estoque de alimentos perecíveis */
#define MAX_ALIM 100
typedef struct {
    int tamanho_heap; /**< Quantidade de alimentos armazenados na heap */
    char alimento; /**< Alimento específico desse estoque */
    int validade_alimentos[MAX_ALIM] /**< Vetor da heap de validades */
} HeapEstoque;

/**
 * @brief Inicializa a heap
 * @param heap estado atual da heap
 */
void inicializaHeap(HeapEstoque* heap);
/**
 * @brief Restaura a propriedade de um nó que pode estar maior que um de seus filhos
 * @param[in,out] validade vetor de validades
 * @param[in] n número de elementos ativos no heap
 * @param[in] i índice do nó a descer
 */
void heapify(int validade[], int n, int i); 

/**
 * @brief Restaura a propriedade de um nó que pode estar menor que um de seus pais
 * @param[in,out] validade vetor de validades
 * @param[in] i índice do nó a subir
 */
void siftUp(int validade[], int i);


 /**
  * @brief Insere um alimento/turno de validade no heap
  * @param[in,out] heap heap de estoque que receberá o alimento
  * @param[in] validade validade a ser inserida
  * @param[in] alimento a ser inserido na heap
  * @return true inserção realizada com sucesso
  * @return false erro ao inserir - alimento não sucetível à inserção
  */
bool inserirHeap(HeapEstoque *heap, int validade, const char alimento);

/**
 * @brief Remove o elemento que está no topo do heap
 * @param[in,out] heap heap de estoque de onde o alimento será removido
 * @return true se um alimento foi removido
 * @return false se a heap estiver vazia
 */

bool removerHeap(HeapEstoque *heap, char* alimento);

/**
 * @brief Verifica qual é o turno de vencimento do elemento do topo. Se for igual ao turno atual, remove o elemento  do estoque. Realiza essa operação até o elemento do topo da min_heap ser maior que o turno atual
 * @param[in,out] heap heap de estoque consultada e atualizada
 * @param[in] turno_atual turno atual usado para verificar o vencimento
 * @return true se havia alimento vencido no topo
 * @return false se o alimento do topo não venceu
 */
bool consultarTopoHeap(HeapEstoque *heap, int turno_atual);

