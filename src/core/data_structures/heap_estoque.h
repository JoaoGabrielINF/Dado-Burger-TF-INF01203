#pragma once
#include "../alimento.h"
#include <stdbool.h>
#define MAX_ALIM 100
typedef struct {
    int tamanhoHeap; /**< Tamanho da heap */
    char alimento; /**< Alimento específico desse estoque */
    Alimento estoquePerecivel[MAX_ALIM]; /**< Vetor da heap, composto por diferentes elementos do mesmo alimento */
} HeapEstoque;

/**
 * @brief Restaura a propriedade de um nó que pode estar maior que um de seus filhos
 * @param a vetor de alimentos
 * @param n numero de elementos do heap
 * @param i nó a descer (posição do vetor a descer)
 */
void heapify(Alimento a[], int n, int i); 

/**
 * @brief Restaura a propriedade de um nó que pode estar menor que um de seus pais
 * @param a vetor de alimentos do heap
 * @param i nó a subir (posição do nó a subir)
 */
void siftUp(Alimento a[], int i);


 /**
  * @brief Insere um alimento no heap
  * @param heap vetor de alimentos do heap
  * @param alimento alimento que será inserido no heap
  * @return true inserção realizada com sucesso
  * @return false erro ao inserir - alimento não sucetivel à inserção
  */
bool inserirHeap(HeapEstoque *heap, const Alimento alimento);

/**
 * @brief Remove o elemento que está no topo do heap
 * @param heap vetor de alimentos do heap   
 * @return true alimento que foi removido do heap
 * @return false erro ao retirar - a lista está vazia 
 */

bool removerHeap(HeapEstoque *heap, Alimento *alimento);

/**
 * @brief Verifica qual é o turno de vencimento do elemento do topo. Se for igual ao turno atual, remove o elemento  do estoque. Realiza essa operação até o elemento do topo da min_heap ser maior que o turno atual
 * @param heap heap que o estoque do alimento específico está armazenado 
 * @param turno_atual inteiro para verificar qual é o turno atual
 * @return true o elemento do topo está no turno de vencimento 
 * @return false o elemento do topo não está no turno de vencimento
 */
bool consultarTopoHeap(HeapEstoque *heap, int turno_atual, Alimento *alimento);

