#pragma once
#include "../alimento.h"
#include <stdbool.h>
/** Capacidade máxima do estoque de alimentos perecíveis */
#define MAX_ALIM 100
typedef struct {
    int tamanho_heap; /**< Quantidade de alimentos armazenados na heap */
    char alimento; /**< Alimento específico desse estoque */
    Alimento estoque_perecivel[MAX_ALIM]; /**< Vetor de alimentos perecíveis do estoque */
} HeapEstoque;

/**
 * @brief Inicializa a heap
 * @param heap estado atual da heap
 */
void inicializaHeap(HeapEstoque* heap);
/**
 * @brief Restaura a propriedade de um nó que pode estar maior que um de seus filhos
 * @param[in,out] a vetor de alimentos que representa o heap
 * @param[in] n número de elementos ativos no heap
 * @param[in] i índice do nó a descer
 */
void heapify(Alimento a[], int n, int i); 

/**
 * @brief Restaura a propriedade de um nó que pode estar menor que um de seus pais
 * @param[in,out] a vetor de alimentos que representa o heap
 * @param[in] i índice do nó a subir
 */
void siftUp(Alimento a[], int i);


 /**
  * @brief Insere um alimento no heap
  * @param[in,out] heap heap de estoque que receberá o alimento
  * @param[in] alimento alimento a inserir
  * @return true inserção realizada com sucesso
  * @return false erro ao inserir - alimento não sucetivel à inserção
  */
bool inserirHeap(HeapEstoque *heap, const Alimento alimento);

/**
 * @brief Remove o elemento que está no topo do heap
 * @param[in,out] heap heap de estoque de onde o alimento será removido
 * @param[out] alimento recebe o alimento removido
 * @return true se um alimento foi removido
 * @return false se a heap estiver vazia
 */

bool removerHeap(HeapEstoque *heap, Alimento *alimento);

/**
 * @brief Verifica qual é o turno de vencimento do elemento do topo. Se for igual ao turno atual, remove o elemento  do estoque. Realiza essa operação até o elemento do topo da min_heap ser maior que o turno atual
 * @param[in,out] heap heap de estoque consultada e atualizada
 * @param[in] turno_atual turno atual usado para verificar o vencimento
 * @param[out] alimento recebe o último alimento removido por vencimento
 * @return true se havia alimento vencido no topo
 * @return false se o alimento do topo não venceu
 */
bool consultarTopoHeap(HeapEstoque *heap, int turno_atual, Alimento *alimento);

